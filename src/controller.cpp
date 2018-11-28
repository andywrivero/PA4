#include "../header/controller.h"

controller::controller (const graph &g, const datapath &dp)
{
	generate_control_signals(get_minmax_timesteps(g), g, dp);	
}

pair<int, int> controller::get_minmax_timesteps (const graph &g)
{
	pair<int, int> p (numeric_limits<int>::max(), numeric_limits<int>::min());

	for (auto &o : g.ops) 
	{
		p.first = std::min (p.first, o.ts);
		p.second = std::max (p.second, o.ts);
	}

	max_ts = p.second;

	return p;
}

void controller::generate_control_signals (const pair<int, int> &p, const graph &g, const datapath &dp)
{
	// at time step 0 all registers WR=0 and done = 0
	for (const auto &r : dp.runits)
		if (!r.is_input)
			signal.emplace_back(0, r.WR_name, 0, 1, false);

	signal.emplace_back(0, "done", 0, 1, false);
	// rest of the time steps

	for (int ts = 1; ts <= p.second; ts++)
	{
		for (int i = 0; i < dp.funits.size(); i++)
			for (int o : *(dp.funits[i].ops))
				if (g.ops[o].ts == ts) // there's an operation in this functional unit scheduled at "ts" time step
				{
					// generate signals for the MUXs that are inputs to this functional unit
					for (int m = 0; m < 2; m++)
					{
						const auto &mux = dp.fu_mux[i][m];

						if (mux.in.size() > 1)
							for (int j = 0; j < mux.in.size(); j++)
								if (find(mux.in[j]->edges->begin(), mux.in[j]->edges->end(), m == 0 ? g.ops[o].i1 : g.ops[o].i2) != mux.in[j]->edges->end())
								{
									signal.emplace_back(ts, mux.sel_name, j, mux.w, true);
									break;
								}
					}

					// generate signals for the output MUX and WR for the registers
					for (const auto &mux : dp.reg_mux)
						if (find (mux.out->edges->begin(), mux.out->edges->end(), g.ops[o].out) != mux.out->edges->end())
						{
							auto it = find_if(signal.begin(), signal.end (), 
									  [&] (const control_signal &s) { return s.ts == ts && s.signal_name == mux.out->WR_name; }); 

							if (it != signal.end()) 
							{
								it->val = 1;
								signal.emplace_back(ts + 1, mux.out->WR_name, 0, 1, false);
							}
							else
							{
								signal.emplace_back(ts, mux.out->WR_name, 1, 1, false);
								signal.emplace_back(ts + 1, mux.out->WR_name, 0, 1, false);
							}

							if (mux.in.size() > 1)
								for (int j = 0; j < mux.in.size(); j++)
									if (&dp.funits[i] == mux.in[j])
									{
										signal.emplace_back(ts, mux.sel_name, j, mux.w, true);
										break;
									}

							break;
						}

					break;
				}
	}

	// done signal
	signal.emplace_back(p.second + 1, "done", 1, 1, false);
}