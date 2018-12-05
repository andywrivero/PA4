/****************************************************************************
 * Digital Circuit Synthesis Final Project
 * Controller, Datapath, and Testbench generation using Data Flow Graphs
 * 
 * Authors: Anthony Teresi, Mary Mouro, and Andy Rivero
 * 
 * Header File
 * Generates the needed datapath data structures. 
 * This datastructure is HDL language independent.
****************************************************************************/

#ifndef DATAPATH_H
#define DATAPATH_H

#include <vector>
#include "graph.h"
#include "reg_unit.h"
#include "fu_unit.h"
#include "mux.h"

using std::vector;

using vec2d = vector<vector<int>>;

class datapath
{
private:
	void create_functional_units (const graph &, const vec2d &);
	void create_register_units (const graph &, const vec2d &);
	void create_register_mux_units (const graph &);
	void create_fu_mux_units (const graph &);
	void create_output_links (const graph &);

public:
	vector<fu_unit> funits;
	vector<reg_unit> runits;
	vector<rmux_unit> reg_mux;
	vector<array<fmux_unit, 2>> fu_mux;
	vector<pair<string, string>> outl;

	datapath (const graph &, const vec2d &, const vec2d &);

	int max_timestep () const;
};

#endif