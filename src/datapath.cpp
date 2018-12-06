/****************************************************************************
 * Digital Circuit Synthesis Final Project
 * Controller, Datapath, and Testbench generation using Data Flow Graphs
 * 
 * Authors: Anthony Teresi, Mary Mouro, and Andy Rivero
 * 
 * Source File
 * This generates the datapath structures (muxes, funtional units, and registers)
 * This structures then can be used to generate a datapath in any HDL language
****************************************************************************/

#include "../header/datapath.h"

datapath::datapath (const graph &g, const vec2d &op_cliques, const vec2d &edge_cliques)
{
	cout << "Creating functional units\n";
	create_functional_units (g, op_cliques);
	cout << "Done.\n";

	cout << "Creating registers units\n";
	create_register_units (g, edge_cliques);
	cout << "Done.\n";

	cout << "Creating register's MUXES\n";
	create_register_mux_units (g);
	cout << "Done.\n";

	cout << "Creating fucntinal units's MUXES\n";
	create_fu_mux_units(g);
	cout << "Done.\n";

	cout << "Mapping output signals to register's output\n";
	create_output_links (g);
	cout << "Done.\n";
}

void datapath::create_functional_units (const graph &g, const vec2d &op_cliques)
{
	for (int i = 0; i < op_cliques.size(); i++) // a functional unit per clique of operations
	{
		string si = to_string(i);

		funits.emplace_back("FU" + si, "fu" + si + "_i1", "fu" + si + "_i2", "fu" + si + "_out", 
							g.ops[op_cliques[i][0]].w, g.ops[op_cliques[i][0]].type);

		// add time-step, left, right inputs, and output edge dependencies of this functional unit
		for (const int &o : op_cliques[i])
		{
			// these vectors keep the necessary information in parallel
			funits.back().ts.push_back(g.ops[o].ts); // add time at which this functional unit must be scheduled
			funits.back().i[0].push_back (g.ops[o].i1); // push a left input edge 
			funits.back().i[1].push_back (g.ops[o].i2); // push a right input edges
			funits.back().out.push_back (g.ops[o].out); // push an output edge
		}					 
	}
}

void datapath::create_register_units (const graph &g, const vec2d &edge_cliques)
{
	for (int i = 0; i < edge_cliques.size(); i++)
	{
		string h = "r" + to_string(i);

		if (g.edges[edge_cliques[i][0]].type == IN)
			runits.emplace_back("",  "", g.edges[edge_cliques[i][0]].edge_name, "", g.edges[edge_cliques[i][0]].w, true);		
		else
			runits.emplace_back("R" + to_string(i), h + "_in", h + "_out", h + "_WR", g.edges[edge_cliques[i][0]].w, false);

		runits.back().edges = std::move(edge_cliques[i]);
	}
}

void datapath::create_register_mux_units (const graph &g)
{
	for (int i = 0; i < runits.size(); i++)
		if (g.edges[runits[i].edges[0]].type != IN)
		{
			reg_mux.emplace_back ();

			auto &mux = reg_mux.back();
			mux.mux_name = "R" + to_string(i) + "_MUX";
			mux.sel_name = "r" + to_string(i) + "_mux_sel";
			mux.out = &runits[i];
			mux.w = runits[i].w;

			for (auto &fu : funits)
				for (int out : fu.out)
					if (find(mux.out->edges.begin(), mux.out->edges.end(), out) != mux.out->edges.end())
					{
						mux.in.push_back(&fu);
						break;
					}

			mux.sel_size = std::ceil(std::log2(mux.in.size()));	
		}
}

void datapath::create_fu_mux_units (const graph &g)
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

			for (auto &r : runits)
				for (int e : r.edges)
					if (find (funits[i].i[m].begin(), funits[i].i[m].end(), e) != funits[i].i[m].end())
					{
						mux.in.push_back(&r);
						break;
					}

			mux.sel_size = std::ceil(std::log2(mux.in.size()));	
		}
	}
}

void datapath::create_output_links (const graph &g)
{
	for (const auto &r : runits)
		for (int e : r.edges)
			if (g.edges[e].type == OUT)
				outl.emplace_back(g.edges[e].edge_name, r.out_name);
}

int datapath::max_timestep () const
{
	int mts = numeric_limits<int>::min ();

	for (const auto &fu : funits)
		for (const int &t : fu.ts)
			mts = std::max (mts, t);

	return mts;	
}