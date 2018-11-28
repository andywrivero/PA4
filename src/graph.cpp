#include "../header/graph.h"

/********************************* Data Flow Graph Implementation *************************************/
void graph::add_edge (string edge_name, int width, edge_type type)
{
	cout << "Adding DFG edge " << edge_name << endl;

	if (type == TEMP)
		edges.emplace_back(edge_name, type, width, 0, 0);
	else
		edges.emplace_back(edge_name, type, width, 0, numeric_limits<int>::max());
}

void graph::add_operation (string op_name, operation_type type, int width, string reg_in1, string reg_in2, string reg_out)
{
	cout << "Adding DFG operation "  << op_name << endl;

	ops.emplace_back(op_name, type, width, 0, 
		distance(edges.begin(), find_if(edges.begin(), edges.end(), [&] (const edge &e) { return e.edge_name == reg_in1; })),
		distance(edges.begin(), find_if(edges.begin(), edges.end(), [&] (const edge &e) { return e.edge_name == reg_in2; })),
		distance(edges.begin(), find_if(edges.begin(), edges.end(), [&] (const edge &e) { return e.edge_name == reg_out; })));

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

void graph::set_edges_lifetime()
{
	cout << "Setting edges life time...\n";

	for (int i = 0; i < ops.size(); i++)
	{
		edges[ops[i].out].fw = ops[i].ts; 

		if (edges[ops[i].i1].lr < ops[i].ts)
			edges[ops[i].i1].lr = ops[i].ts;

		if (edges[ops[i].i2].lr < ops[i].ts)
			edges[ops[i].i2].lr = ops[i].ts;
	}
}

bool graph::alap (int l, vector<int> &tl)
{
	cout << "Running ALAP...\n";

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

	cout << "Running List_R algorithm...\n";

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

	set_edges_lifetime();

	return true;
}

void graph::list_l (int adds, int subs, int mults, int divs)
{
	cout << "Running List_L algorithm\n";

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

	set_edges_lifetime();
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

		cout << "Input registers: " << edges[op.i1].edge_name << ", " << edges[op.i2].edge_name << endl;
		cout << "Output register: " << edges[op.out].edge_name << endl << endl;
	}
}
/***************************************************************************************/