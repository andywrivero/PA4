/****************************************************************************
 * Digital Circuit Synthesis Final Project
 * Controller, Datapath, and Testbench generation using Data Flow Graphs
 * 
 * Authors: Anthony Teresi, Mary Mouro, and Andy Rivero
 * 
 * Source File: This is the main driver file
****************************************************************************/

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <tuple>
#include <algorithm>
#include "../header/graph.h"
#include "../header/algo.h"
#include "../header/operation.h"
#include "../header/datapath.h"
#include "../header/datapath_vhdl.h"
#include "../header/controller.h"
#include "../header/controller_vhdl.h"
#include "../header/testbench_vhdl.h"
#include "../header/cgen.h"

using std::ifstream;
using std::ofstream;
using std::vector;
using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::to_string;

/*************************** Driver methods **********************/
operation_type to_operation_type (string stype)
{
	if (stype == "ADD")
		return ADD;
	else if (stype == "SUB")
		return SUB;
	else if (stype == "MULT")
		return MULT;
	else 
		return DIV;
}

string to_operation_stype (operation_type type)
{
	if (type == ADD)
		return "ADD";
	else if (type == SUB)
		return "SUB";
	else if (type == MULT)
		return "MULT";
	else 
		return "DIV";
}

void read_graph (graph &g, string &filename)
{
	cout << "Enter .aif filename: "; 
	cin >> filename;

	//  open input file
	string filepath = filename + ".aif";
	ifstream fi (filepath);

	cout << "Reading Data Flow Graph...\n";

	string s1, s2, s3, s4, s5;
	int width;

	fi >> s1; // consume "inputs" keyword from file
	fi >> s1; // first input register name

	while (s1 != "outputs")
	{
		fi >> width;
		g.add_edge(s1, width, IN);
		fi >> s1;
	}

	fi >> s1; // first output register name

	while (s1 != "regs" && s1 != "op1")
	{
		fi >> width;
		g.add_edge(s1, width, OUT);
		fi >> s1;
	}
 
	if (s1 == "regs") fi >> s1; // first intermediate register name

	while (s1 != "op1")
	{
		fi >> width;
		g.add_edge(s1, width, TEMP);
		fi >> s1;
	}

	while (s1 != "end")
	{
		fi >> s2 >> width >> s3 >> s4 >> s5;
		g.add_operation(s1, to_operation_type(s2), width, s3, s4, s5);
		fi >> s1;
	}

	fi.close();

	cout << "Done...\n";
}
/****************************************************************/

int main ()
{	
	string filename;
	graph g;

	read_graph (g, filename);

	char answer;

	do
	{
		cout << "Select LIST_R or LIST_L scheduling (R/L)?";
		cin >> answer;

		if (answer != 'L' && answer != 'l' && answer != 'R' && answer != 'r')
			cout << "Wrong selectiong...\n";	

	} while (answer != 'L' && answer != 'l' && answer != 'R' && answer != 'r');


	if (answer == 'R' || answer == 'r')
	{
		int l;
		std::cout << "Enter Lambda: ";
		std::cin >> l;	
		
		if (!g.list_r(l))
		{
			cout << "No Solution\n";
			return 0;
		}
	}
	else
	{
		int a[4];
		cout << "Enter the number of resources for ADD, SUB, MULT and DIV : ";
		std::cin >> a[0] >> a[1] >> a[2] >> a[3];
		g.list_l (a[0], a[1], a[2], a[3]); 
	}

	cout << "Allocating and binding operations\n";
	auto ops_cliques = allocate_and_bind(g.ops);
	cout << "Done.\n";
	
	cout << "Allocating and binding edges\n";
	auto edge_cliques = allocate_and_bind(g.edges); 
	cout << "Done.\n";

	cout << "All allocation and binding is done.\n";
	cout << "Creating datapath...\n";
	datapath dp (g, ops_cliques, edge_cliques);
	ofstream output ("VHDL_files/" + filename + "_datapath.vhd");
	cout << "Creating datapath's VHDL code\n";
	datapath_vhdl dp_vhdl (g, dp, filename);
	dp_vhdl.create_vhdl_code(output);
	output.close();
	cout << "Done.\n";

	cout << "Creating controller...\n";
	controller contr (dp);
	output.open("VHDL_files/" + filename + "_controller.vhd");
	cout << "Creating controller's VHDL code\n";
	controller_vhdl contr_vhdl (contr, dp, filename);
	contr_vhdl.create_vhdl_code(output);
	output.close ();
	cout << "Done.\n";

	output.open("VHDL_files/" + filename + "_testbench.vhd");
	cout << "Creating testbench VHDL code\n";
	testbench_vhdl testbech (g, contr, dp, filename);
	testbech.create_vhdl_code(output);
	cout << "Done.\n";
	output.close ();

	// This code below can be used to generate a C++.
	// This file represents the circuit. One can compile this file and verify the output
	// with that of the VHDL output
	#define CPP_GENERATION
	#ifdef CPP_GENERATION
		output.open("CPP_test/" + filename + ".cpp");
		generate_C_test (g, output);
		output.close ();
	#endif

	return 0;
}