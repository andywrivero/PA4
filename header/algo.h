#ifndef ALGO_H
#define ALGO_H

#include <vector>
#include "data_structures.h"

using std::vector;
using std::function;

using vec2d = vector<vector<int>>;

template <class T>
vec2d allocate_and_bind (const vector<T> &); 

#endif