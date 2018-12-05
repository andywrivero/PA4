/****************************************************************************
 * Digital Circuit Synthesis Final Project
 * Controller, Datapath, and Testbench generation using Data Flow Graphs
 * 
 * Authors: Anthony Teresi, Mary Mouro, and Andy Rivero
 * 
 * Source File
 * This does the resource allocation and binding for both operations and edges
 * using Dr. Srinivas Katkoori implemetation of the Clique Partitioning
****************************************************************************/
#include "../header/algo.h"
#include "clique_partition.c"

template <class T>
vec2d allocate_and_bind (const vector<T> &v)
{	
	cout << "Allocating and binding resources\n";

	int* comp[v.size()];

	for (int i = 0; i < v.size(); i++) comp[i] = new int[v.size()];

	// Generate compatibility matrix
	for (int i = 0; i < v.size(); i++)
		for (int j = i; j < v.size(); j++)
			comp[i][j] = comp[j][i] = v[i].is_compatible (v[j]);
		
	clique_partition(comp, v.size());

	for (int i = 0; i < v.size(); i++) delete [] comp[i];

	// copy clique set into a 2D vector
	vec2d bindings;
	
	for (int i = 0; clique_set[i].size != UNKNOWN; i++)
	{
		bindings.emplace_back();

		for (int j = 0; clique_set[i].members[j] != UNKNOWN; j++)
			bindings[bindings.size() - 1].push_back(clique_set[i].members[j]);
	}

	return bindings;
}

// Template function specializations 
template
vec2d allocate_and_bind (const vector<operation> &);

template
vec2d allocate_and_bind (const vector<edge> &);