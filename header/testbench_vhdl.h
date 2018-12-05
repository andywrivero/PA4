#ifndef TESTBENCH_VHDL_H
#define TESTBENCH_VHDL_H

#include <fstream>
#include <string>
#include "graph.h"
#include "controller.h"
#include "datapath.h"

using std::ostream;
using std::string;

class testbench_vhdl
{
private:
	void create_entity (ostream &);	
	void create_architecture (ostream &);
	void create_datapath_instance (ostream &);
	void create_controller_instance (ostream &);
	void create_signals (ostream &);
	void create_clock_process (ostream &);
	void create_test_process (ostream &);

public:
	graph &g;
	datapath &dp;
	controller &contr;
	string entity_name;

	testbench_vhdl (graph &g, controller &contr, datapath &dp, string entity_name) 
		: g(g), contr (contr), dp (dp), entity_name(entity_name) {}
	void create_vhdl_code (ostream &);
};

#endif