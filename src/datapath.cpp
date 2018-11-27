#include "../header/datapath.h"

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

		if (g.edges[reg_cliques[i][0]].type == IN)
			runits.emplace_back("",  "", g.edges[reg_cliques[i][0]].edge_name, "", g.edges[reg_cliques[i][0]].w, true);		
		else
			runits.emplace_back("R" + to_string(i), h + "_in", h + "_out", h + "_WR", g.edges[reg_cliques[i][0]].w, false);
	}
}

void datapath::create_register_mux_units (const graph &g, const vec2d &op_cliques, const vec2d &reg_cliques)
{
	for (int i = 0; i < reg_cliques.size (); i++)
		if (g.edges[reg_cliques[i][0]].type != IN)
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
			if (g.edges[r].type == OUT)
				outl.emplace_back(g.edges[r].edge_name, runits[i].out_name);
}