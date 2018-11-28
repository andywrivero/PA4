#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <vector>
#include <algorithm>
#include "datapath.h"
#include "graph.h"

using std::vector;
using std::pair;
using std::find_if;

class controller
{
	int max_timestep (const graph &);
	void generate_control_signals (const graph &, const datapath &);

public:
	struct control_signal
	{
		int ts, val, w;
		bool is_vector;
		string signal_name; // this name will match the input signal name in the datapath

		control_signal (int ts, string signal_name, int val, int w, bool is_vector) 
			: ts (ts), signal_name (signal_name), val (val), w (w), is_vector (is_vector) {}
	};

	vector<control_signal> signal;

	controller (const graph &, const datapath &);
};

#endif