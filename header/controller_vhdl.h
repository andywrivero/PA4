#ifndef CONTROLLER_VHDL_H
#define CONTROLLER_VHDL_H

#include <fstream>
#include <string>
#include "controller.h"
#include "datapath.h"

using std::ostream;
using std::string;

class controller_vhdl
{
private:
	void create_entity (ostream &);	
	void create_architecture (ostream &);
	void create_signals (ostream &);
	void create_process (ostream &);
	int max_timestep ();

public:
	graph &g;
	datapath &dp;
	controller &contr;
	string entity_name;

	controller_vhdl (graph &g, datapath &dp, controller &contr, string entity_name) 
		: g(g), contr (contr), dp (dp), entity_name(entity_name) {}
	void create_vhdl_code (ostream &);
};

#endif