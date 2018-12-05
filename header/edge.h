/****************************************************************************
 * Digital Circuit Synthesis Final Project
 * Controller, Datapath, and Testbench generation using Data Flow Graphs
 * 
 * Authors: Anthony Teresi, Mary Mouro, and Andy Rivero
 * 
 * Header File
 * This represents an edge in the DFG. It holds all necessary data in the graph
****************************************************************************/

#ifndef EDGE_H
#define EDGE_H

#include <string>

using std::string;

enum edge_type { IN = 0 , OUT = 1, TEMP = 2 };

class edge
{
	bool in_range (int, int, int) const;

public:
	string edge_name;	// the register name
	edge_type type;  	// the register type
	int w; 				// width
	int fw, lr;			// first write, last read

	// constructors
	edge () = default;
	edge (string reg_name, edge_type type, int w, int fw, int lr) 
		: edge_name (reg_name), type (type), w (w), fw (fw), lr (lr) {}

	bool is_compatible (const edge &) const;
};

#endif