
#include "../header/data_structures.h"

/********************************* Registers (Edges) Implementation *************************************/
bool reg::is_compatible (const reg &r) const
{
	return !in_range(fw, r.fw, r.lr) && !in_range(r.fw, fw, lr);
}

bool reg::in_range (int a, int l, int h) const
{
	return a >= l && a < h;
}
/***************************************************************************************/

/********************************* Operation Implementation *************************************/
bool operation::is_compatible(const operation &op) const
{
	return type == op.type && ts != op.ts;
}
/***************************************************************************************/

/********************************* Data Flow Graph Implementation *************************************/
void graph::add_register (string reg_name, int width, reg_type type)
{
	if (type == TEMP)
		regs.emplace_back(reg_name, type, width, 0, 0);
	else
		regs.emplace_back(reg_name, type, width, 0, numeric_limits<int>::max());
}

void graph::add_operation (string op_name, operation_type type, int width, string reg_in1, string reg_in2, string reg_out)
{
	ops.emplace_back(op_name, type, width, 0, 
		distance(regs.begin(), find_if(regs.begin(), regs.end(), [&] (const reg &r) { return r.reg_name == reg_in1; })),
		distance(regs.begin(), find_if(regs.begin(), regs.end(), [&] (const reg &r) { return r.reg_name == reg_in2; })),
		distance(regs.begin(), find_if(regs.begin(), regs.end(), [&] (const reg &r) { return r.reg_name == reg_out; })));

	operation &op = ops[ops.size() - 1];

	// add the links to this new operation
	for (int i = 0; i < ops.size() - 1; i++)
	{
		if (ops[i].out == op.i1 || ops[i].out == op.i2)
		{
			ops[i].suc.push_back(ops.size() - 1);
			op.pred.push_back(i);
		}

		if (op.out == ops[i].i1 || op.out == ops[i].i2)
		{
			op.suc.push_back(i);
			ops[i].pred.push_back(ops.size() - 1);
		}
	}
}

void graph::set_lifetime()
{
	cout << "\nSetting edges life time\n";

	for (int i = 0; i < ops.size(); i++)
	{
		regs[ops[i].out].fw = ops[i].ts; 

		if (regs[ops[i].i1].lr < ops[i].ts)
			regs[ops[i].i1].lr = ops[i].ts;

		if (regs[ops[i].i2].lr < ops[i].ts)
			regs[ops[i].i2].lr = ops[i].ts;
	}
}

bool graph::alap (int l, vector<int> &tl)
{
	cout << "Running ALAP\n";

	if (l <= 0) return false;

	tl.resize(ops.size(), l + 1); 
	queue<int> q; 

	for (int i = 0; i < ops.size(); i++)
		if (ops[i].suc.size() == 0) 
			tl[i] = l; // schedule terminal operation
		else  
			q.push(i); // push unscheduled operation to queue

	// schedule the rest of the operations
	while (!q.empty())
	{
		int i = q.front ();
		q.pop ();

		for (int j : ops[i].suc) // iterate over operation i successors
		{
			if (tl[j] == l + 1) // successor hasn't been scheduled yet
			{
				tl[i] = l + 1; 
				q.push (i); 
				break;
			}
			
			if ((tl[i] = min(tl[i], tl[j] - 1)) <= 0) return false;
		}
	}

	return true;
}

bool graph::list_r (int l)
{
	vector<int> tl;	

	if (!alap (l, tl)) return false;

	cout << "\nRunning List_R algorithm\n";

	a.fill(0);

	for (auto &o : ops) 
	{
		o.ts = 0;
		a[o.type] = 1;
	}

	int ts = 1, n = 0; // time-step, number of scheduled operations
	array<int, 4> av;

	while (n < ops.size ())
	{
		av = a;

		// schedule operations with 0 slack
		for (int i = 0; i < ops.size(); i++)
			if (ops[i].ts == 0 && tl[i] - ts == 0)
			{
				n++;
				ops[i].ts = ts;
				av[ops[i].type]--;

				if (av[ops[i].type] < 0) 
					a[ops[i].type]++;
			}

		// schedule other operations if resources are still available
		for (int i = 0; i < ops.size(); i++)
			if (ops[i].ts == 0 && av[ops[i].type] > 0)
			{
				auto it = find_if(ops[i].pred.begin(), ops[i].pred.end(), [&] (int &p) 
					{ return ops[p].ts == 0 || ops[p].ts == ts; });

				if (it == ops[i].pred.end())
				{
					n++;
					ops[i].ts = ts;
					av[ops[i].type]--;
				}
			}

		ts++;
	}

	return true;
}

void graph::list_l (int adds, int subs, int mults, int divs)
{
	cout << "\nRunning List_L algorithm\n";

	a = { adds, subs, mults, divs };

	for (auto &o : ops) o.ts = 0; // set all operations as unscheduled

	int ts = 1, n = 0; // time step, number of scheduled operations
	array<int, 4> av; // available resources of each type at each time step

	while (n < ops.size())
	{
		av = a;

		for (auto &o : ops)
			if (o.ts == 0 && av[o.type] > 0)
			{
				auto it = find_if(o.pred.begin(), o.pred.end(), [&] (int &p) { return ops[p].ts == 0 || ops[p].ts == ts; });

				if (it == o.pred.end())
				{
					n++;
					o.ts = ts;
					av[o.type]--;
				}
			}

		ts++;
	}
}

void graph::print_graph()
{
	cout << "\n Data Flow Graph\n";

	for (auto op : ops)
	{
		cout << "Name : " << op.op_name << endl << "Succesors: ";

		for (int i = 0; i < op.suc.size(); i++)
			cout << ops[op.suc[i]].op_name << " ";

		cout << endl;

		cout << "Input registers: " << regs[op.i1].reg_name << ", " << regs[op.i2].reg_name << endl;
		cout << "Output register: " << regs[op.out].reg_name << endl << endl;
	}
}
/***************************************************************************************/

/******************************Data Path Implementation*********************************/
datapath::datapath (const graph &g, const vec2d &op_cliques, const vec2d &reg_cliques)
{
	create_functional_units (g, op_cliques);
	create_register_units (g, reg_cliques);
	create_register_mux_units (g, op_cliques, reg_cliques);
	create_fu_mux_units(g, op_cliques, reg_cliques);
	create_output_links (g, reg_cliques);
}

void datapath::create_functional_units (const graph &g, const vec2d &op_cliques)
{
	for (int i = 0; i < op_cliques.size(); i++)
	{
		string si = to_string(i);

		funits.emplace_back("FU" + si, "fu" + si + "_i1", "fu" + si + "_i2", "fu" + si + "_out", 
							g.ops[op_cliques[i][0]].w, g.ops[op_cliques[i][0]].type); 
	}
}

void datapath::create_register_units (const graph &g, const vec2d &reg_cliques)
{
	for (int i = 0; i < reg_cliques.size(); i++)
	{
		string h = "r" + to_string(i);

		if (g.regs[reg_cliques[i][0]].type == IN)
			runits.emplace_back("",  "", g.regs[reg_cliques[i][0]].reg_name, "", g.regs[reg_cliques[i][0]].w, true);		
		else
			runits.emplace_back("R" + to_string(i), h + "_in", h + "_out", h + "_WR", g.regs[reg_cliques[i][0]].w, false);
	}
}

void datapath::create_register_mux_units (const graph &g, const vec2d &op_cliques, const vec2d &reg_cliques)
{
	for (int i = 0; i < reg_cliques.size (); i++)
		if (g.regs[reg_cliques[i][0]].type != IN)
		{
			reg_mux.emplace_back ();
			auto &mux = reg_mux.back();
			mux.mux_name = "R" + to_string(i) + "_MUX";
			mux.sel_name = "r" + to_string(i) + "_mux_sel";
			mux.out = &runits[i];
			mux.w = runits[i].w;

			for (int j = 0; j < op_cliques.size (); j++)
				for (int k : op_cliques[j])
					if (find (reg_cliques[i].begin(), reg_cliques[i].end (), g.ops[k].out) != reg_cliques[i].end ())
					{
						mux.in.push_back(&funits[j]);
						break;
					}

			mux.sel_size = std::ceil(std::log2(mux.in.size()));	
		}
}

void datapath::create_fu_mux_units (const graph &g, const vec2d &op_cliques, const vec2d &reg_cliques)
{
	for (int i = 0; i < op_cliques.size (); i++)
	{
		fu_mux.emplace_back();

		for (int m = 0; m < 2; m++)
		{
			auto &mux  = fu_mux.back()[m];

			mux.mux_name = "F" + to_string(i) + "_MUX" + to_string(m);
			mux.sel_name = "f" + to_string(i) + "_MUX" + to_string(m) + "_sel";
			mux.out = &funits[i];
			mux.w = funits[i].w;

			vector<int> ins;

			for (int o : op_cliques[i])
				if (m == 0)
					ins.push_back(g.ops[o].i1);
				else 
					ins.push_back(g.ops[o].i2);

			for (int j = 0; j < reg_cliques.size(); j++)
				for (int k : reg_cliques[j])
					if (find(ins.begin(), ins.end(), k) != ins.end())
					{
						mux.in.push_back(&runits[j]);
						break;
					}

			mux.sel_size = std::ceil(std::log2(mux.in.size()));	
		}
	}
}

void datapath::create_output_links (const graph &g, const vec2d &reg_cliques)
{
	for (int i = 0; i < reg_cliques.size(); i++)
		for (auto r : reg_cliques[i])
			if (g.regs[r].type == OUT)
				outl.emplace_back(g.regs[r].reg_name, runits[i].out_name);
}
/***************************************************************************************/

