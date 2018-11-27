#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <tuple>
#include <algorithm>
#include "../header/graph.h"
#include "../header/algo.h"
#include "../header/datapath_vhdl.h"
#include "../header/datapath.h"
#include "../header/operation.h"

using std::ifstream;
using std::ofstream;
using std::vector;
using std::string;
using std::cout;
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

void read_graph (graph &g)
{
	cout << "Reading Data Flow Graph...\n";

	//  open input file
	string filename = "inputs/toyexample.aif";
	ifstream fi (filename);

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

	while (s1 != "regs")
	{
		fi >> width;
		g.add_edge(s1, width, OUT);
		fi >> s1;
	}
 
	fi >> s1; // first intermediate register name

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
	graph g;
	read_graph (g);

	#define LIST_R
	#ifdef LIST_R
		int l;
		std::cout << "Enter Lambda: ";
		std::cin >> l;	
		
		if (!g.list_r(l))
		{
			cout << "No Solution\n";
			return 0;
		}
	#else 
		int a[4];
		cout << "Enter the number of resources for ADD, SUB, MULT and DIV : ";
		std::cin >> a[0] >> a[1] >> a[2] >> a[3];
		g.list_l (a[0], a[1], a[2], a[3]); 
	#endif 

	auto op_cliques = allocate_and_bind(g.ops);
	auto reg_cliques = allocate_and_bind(g.edges);

	datapath dp (g, op_cliques, reg_cliques);

	ofstream output ("output.vhd");
	datapath_vhdl gen (g, dp, "my_entity");
	gen.create_vhdl_code(output);

	return 0;
}