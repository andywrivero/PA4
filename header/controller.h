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
	void generate_control_signals (const datapath &);
	void create_mux_signal (const fmux_unit &, int, int);
	void create_mux_signal (const vector<rmux_unit> &, const fu_unit &, int, int);
	void create_WR_signal (const reg_unit &, int);
	int max_timestep (const datapath &) const;

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

	controller (const datapath &);
};

#endif