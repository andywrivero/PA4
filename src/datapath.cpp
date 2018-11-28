#include "../header/datapath.h"

datapath::datapath (const graph &g, const vec2d &op_cliques, const vec2d &edge_cliques)
{
	create_functional_units (g, op_cliques);
	create_register_units (g, edge_cliques);
	create_register_mux_units (g, op_cliques, edge_cliques);
	create_fu_mux_units(g, op_cliques, edge_cliques);
	create_output_links (g, edge_cliques);
}

void datapath::create_functional_units (const graph &g, const vec2d &op_cliques)
{
	for (int i = 0; i < op_cliques.size(); i++)
	{
		string si = to_string(i);

		funits.emplace_back("FU" + si, "fu" + si + "_i1", "fu" + si + "_i2", "fu" + si + "_out", 
							g.ops[op_cliques[i][0]].w, g.ops[op_cliques[i][0]].type, &(op_cliques[i])); 
	}
}

void datapath::create_register_units (const graph &g, const vec2d &edge_cliques)
{
	for (int i = 0; i < edge_cliques.size(); i++)
	{
		string h = "r" + to_string(i);

		if (g.edges[edge_cliques[i][0]].type == IN)
			runits.emplace_back("",  "", g.edges[edge_cliques[i][0]].edge_name, "", g.edges[edge_cliques[i][0]].w, true, &(edge_cliques[i]));		
		else
			runits.emplace_back("R" + to_string(i), h + "_in", h + "_out", h + "_WR", g.edges[edge_cliques[i][0]].w, false, &(edge_cliques[i]));
	}
}

void datapath::create_register_mux_units (const graph &g, const vec2d &op_cliques, const vec2d &edge_cliques)
{
	for (int i = 0; i < runits.size(); i++)
		if (g.edges[runits[i].edges->at(0)].type != IN)
		{
			reg_mux.emplace_back ();

			auto &mux = reg_mux.back();
			mux.mux_name = "R" + to_string(i) + "_MUX";
			mux.sel_name = "r" + to_string(i) + "_mux_sel";
			mux.out = &runits[i];
			mux.w = runits[i].w;

			for (int j = 0; j < funits.size(); j++)
				for (int k : *(funits[j].ops))
					if (find (runits[i].edges->begin (), runits[i].edges->end (), g.ops[k].out) != runits[i].edges->end ())
					{
						mux.in.push_back(&funits[j]);
						break;
					}

			mux.sel_size = std::ceil(std::log2(mux.in.size()));	
		}
}

void datapath::create_fu_mux_units (const graph &g, const vec2d &op_cliques, const vec2d &edge_cliques)
{
	for (int i = 0; i < funits.size(); i++)
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

			for (int o : *(funits[i].ops))
				if (m == 0)
					ins.push_back(g.ops[o].i1);
				else 
					ins.push_back(g.ops[o].i2);

			for (int j = 0; j < runits.size(); j++)
				for (int k : *(runits[j].edges))
					if (find(ins.begin(), ins.end(), k) != ins.end())
					{
						mux.in.push_back(&runits[j]);
						break;
					}

			mux.sel_size = std::ceil(std::log2(mux.in.size()));	
		}
	}
}

void datapath::create_output_links (const graph &g, const vec2d &edge_cliques)
{
	for (int i = 0; i < edge_cliques.size(); i++)
		for (auto r : edge_cliques[i])
			if (g.edges[r].type == OUT)
				outl.emplace_back(g.edges[r].edge_name, runits[i].out_name);
}