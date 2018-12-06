/****************************************************************************
 * Digital Circuit Synthesis Final Project
 * Controller, Datapath, and Testbench generation using Data Flow Graphs
 * 
 * Authors: Anthony Teresi, Mary Mouro, and Andy Rivero
 * 
 * Header file: function declaration of the C++ file that can be used to test the outputs of the circuit
****************************************************************************/

#ifndef CGEN_H
#define CGEN_H

#include <fstream>
#include <queue>
#include <vector>
#include "graph.h"

using std::ostream;
using std::queue;
using std::vector;

void generate_C_test (const graph &, ostream &os);

#endif