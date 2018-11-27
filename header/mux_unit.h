#ifndef MUX_UNIT_H
#define MUX_UNIT_H

#include <string>

using std::string;

struct mux_unit
{
	string mux_name, sel_name;
	int sel_size; 
	int w;
};

#endif