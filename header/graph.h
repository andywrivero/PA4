#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <limits>
#include <queue>
#include <array>
#include <cmath>
#include "edge.h"
#include "operation.h"

using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::queue;
using std::array;
using std::find_if;
using std::find;
using std::numeric_limits;
using std::min;
using std::to_string;
using std::pair;

using vec2d = vector<vector<int>>;

class graph
{
	bool alap (int l, vector<int> &tl);	
	void set_edges_lifetime ();
	
public:
	vector<edge> edges;
	vector<operation> ops; 
	array<int, 4> a;

	// constructor
	graph () = default;

	// member methods
	void add_edge (string edge_name, int width, edge_type type);
	void add_operation (string op_name, operation_type type, int width, string reg_in1, string reg_in2, string reg_out);	
	bool list_r (int l);
	void list_l (int adds, int subs, int mults, int divs);
	void print_graph ();
};

#endif