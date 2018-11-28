#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <vector>
#include "datapath.h"
#include "graph.h"

using std::vector;
using std::pair;

class controller
{
	pair<int, int> get_minmax_timesteps (const graph &);

	void generate_control_signals (const pair<int, int> &, const graph &, const datapath &);

public:
	struct control_signal
	{
		int ts, val, w;
		bool is_vector;
		string signal_name; // this name will match the input signal name in the datapath

		control_signal (int ts, string signal_name, int val, int w, bool is_vector) 
			: ts (ts), signal_name (signal_name), val (val), w (w), is_vector (is_vector) {}
	};

	int max_ts;
	vector<control_signal> signal;

	controller (const graph &, const datapath &);
};

#endif