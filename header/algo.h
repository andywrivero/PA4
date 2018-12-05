/****************************************************************************
 * Digital Circuit Synthesis Final Project
 * Controller, Datapath, and Testbench generation using Data Flow Graphs
 * 
 * Authors: Anthony Teresi, Mary Mouro, and Andy Rivero
 * 
 * Header File
 * This does the resource allocation and binding for both operations and edges
 * using Dr. Srinivas Katkoori implemetation of the Clique Partitioning
****************************************************************************/
#ifndef ALGO_H
#define ALGO_H

#include <iostream>
#include <vector>
#include "graph.h"

using std::vector;

using vec2d = vector<vector<int>>;

template <class T>
vec2d allocate_and_bind (const vector<T> &); 

#endif