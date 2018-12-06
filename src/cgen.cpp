/****************************************************************************
 * Digital Circuit Synthesis Final Project
 * Controller, Datapath, and Testbench generation using Data Flow Graphs
 * 
 * Authors: Anthony Teresi, Mary Mouro, and Andy Rivero
 * 
 * Source File
 * This generates a CPP file out of the data flow graph operations specifications
 * Which then can be used to test the output of the generated VHDL circuit
****************************************************************************/

#include "../header/cgen.h"

void genrate_inputs (const graph &g, ostream &os)
{
	os << "\tint ";

	for (int i = 0; i < g.edges.size() - 1; i++)
	{
		os << g.edges[i].edge_name << ", ";

		if (i > 0 && i % 5 == 0) os << "\n\t\t";
	}

	os << g.edges.back().edge_name << ";\n";

	os << "\n";

	for (const auto &e : g.edges)
		if (e.type == IN)
		{
			os << "\tcout << \"Enter input " << e.edge_name << " : \";";
			os << " cin >> " << e.edge_name << ";\n";
		}

	os << "\n";
}

void generate_calculations (const graph &g, ostream &os)
{
	queue<int> Q;
	vector<bool> done (g.edges.size(), false);

	for (int i = 0; i < g.edges.size(); i++)
		if (g.edges[i].type == IN) done[i] = true;

	for (int i = 0; i < g.ops.size (); i++)
		Q.push(i);

	while (!Q.empty())
	{
		int i = Q.front();
		Q.pop ();

		if (done[g.ops[i].i1] && done[g.ops[i].i2])
		{
			const operation &o = g.ops[i];
			string sop;

			if (o.type == ADD) sop = " + ";
			else if (o.type == SUB) sop = " - ";
			else if (o.type == MULT) sop = " * ";
			else sop = " / ";

			os << "\t" << g.edges[o.out].edge_name << " = " 
			   << g.edges[o.i1].edge_name << sop << g.edges[o.i2].edge_name << ";\n";

			done[o.out] = true;
		}
		else
			Q.push(i);
	}

	os << "\n";
}

void generate_outputs (const graph &g, ostream &os)
{
	for (const auto &e : g.edges)
		if (e.type == OUT)
			os << "\tcout << \"" << e.edge_name << " = \" << " << e.edge_name << " << endl;\n"; 

	os << "\n";
}

void generate_C_test (const graph &g, ostream &os)
{
	os <<"#include <iostream>\n\n";
	os << "using std::cin;\n";
	os << "using std::cout;\n\n";
	os << "using std::endl;\n\n";

	os << "int main ()\n";
	os << "{\n";

	genrate_inputs (g, os);
	generate_calculations (g, os);
	generate_outputs(g, os);

	os << "\treturn 0;\n}";
}


