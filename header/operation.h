/****************************************************************************
 * Digital Circuit Synthesis Final Project
 * Controller, Datapath, and Testbench generation using Data Flow Graphs
 * 
 * Authors: Anthony Teresi, Mary Mouro, and Andy Rivero
 * 
 * Header file: Defines the structure of an operation in  the circuit
****************************************************************************/

#ifndef OPERATION_H
#define OPERATION_H

#include <string>
#include <vector>

using std::string;
using std::vector;

enum operation_type { ADD = 0, SUB = 1, MULT = 2, DIV = 3 };

class operation
{
public:
	string op_name;
	operation_type type; // operation type
	int w, ts,   		 // width and time step
		i1, i2, out; 	 // the two input edges, and the output edge indexes
	vector<int> suc;	 // dependencies
	vector<int> pred;	 // dependencies

	// constructors
	operation () = default;
	operation (string op_name, operation_type type, int w, int ts, int i1, int i2, int out) 
		: op_name (op_name), type (type), w (w), ts (ts), i1 (i1), i2 (i2), out (out) {}

	bool is_compatible (const operation &) const;	
};

#endif