#ifndef REG_UNIT_H
#define REG_UNIT_H

#include <string>
#include <iostream>
#include <vector>

using std::vector;
using std::string;

struct reg_unit
{
	string reg_name, in_name, out_name, WR_name;
	int w;
	bool is_input;
	vector<int> edges;

	reg_unit () = default;
	reg_unit (string reg_name, string in_name, string out_name, string WR_name, int w, bool is_input) 
		: reg_name (reg_name), in_name(in_name), out_name (out_name), WR_name (WR_name), w(w), is_input (is_input) {}
};

#endif