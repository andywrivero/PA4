/****************************************************************************
 * Digital Circuit Synthesis Final Project
 * Controller, Datapath, and Testbench generation using Data Flow Graphs
 * 
 * Authors: Anthony Teresi, Mary Mouro, and Andy Rivero
 * 
 * Header File
 * This is the general information held by a MUX
****************************************************************************/

#ifndef MUX_UNIT_H
#define MUX_UNIT_H

#include <string>
#include <vector>
#include "reg_unit.h"
#include "fu_unit.h"

using std::string;
using std::vector;

template <class I, class O>
struct mux
{
	string mux_name, sel_name;
	int sel_size; 
	int w;
	O *out;
	vector<I *> in; 
}; 

// definitions for register muxes, and functional unit muxes
typedef struct mux<fu_unit, reg_unit> rmux_unit;
typedef struct mux<reg_unit, fu_unit> fmux_unit; 

#endif