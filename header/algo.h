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