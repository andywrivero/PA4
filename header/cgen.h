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