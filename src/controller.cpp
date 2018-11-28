#include "../header/controller.h"

controller::controller (const graph &g, const datapath &dp)
{
	generate_control_signals(g, dp);	
}

int controller::max_timestep (const graph &g)
{
	int mts = numeric_limits<int>::min ();

	for (auto &o : g.ops) 
		mts = std::max (mts, o.ts);

	return mts;
}

void controller::generate_control_signals (const graph &g, const datapath &dp)
{
	// at time step 0 all registers WR=0 and done = 0
	for (const auto &r : dp.runits)
		if (!r.is_input)
			signal.emplace_back(0, r.WR_name, 0, 1, false);

	signal.emplace_back(0, "done", 0, 1, false);
	// rest of the time steps

	int mts = max_timestep(g);

	for (int ts = 1; ts <= mts; ts++)
	{
		for (int i = 0; i < dp.funits.size(); i++)
			for (int o : *(dp.funits[i].ops))
				if (g.ops[o].ts == ts) // there's an operation in this functional unit scheduled at "ts" time step
				{
					// generate signals for the MUXs that are inputs to this functional unit
					for (int m = 0; m < 2; m++)
					{
						const auto &mux = dp.fu_mux[i][m]; // get the left, or right mux that is input to this functional unit

						if (mux.in.size() > 1) // if the mux has more than one input
							for (int j = 0; j < mux.in.size(); j++) // mux.in[j] is a register unit. See if one of the binded edges of this register is the input of the mux
								if (find(mux.in[j]->edges->begin(), mux.in[j]->edges->end(), m == 0 ? g.ops[o].i1 : g.ops[o].i2) != mux.in[j]->edges->end())
								{
									signal.emplace_back(ts, mux.sel_name, j, mux.sel_size, true); // add a new control signal
									break;
								}
					}

					// generate signals for the output MUX and WR for the registers
					for (const auto &mux : dp.reg_mux)
						if (find (mux.out->edges->begin(), mux.out->edges->end(), g.ops[o].out) != mux.out->edges->end())
						{
							auto it = find_if(signal.begin(), signal.end (), 
									  [&] (const control_signal &s) { return s.ts == ts && s.signal_name == mux.out->WR_name; }); 

							if (it != signal.end()) // check if we need to override the WR signal 
							{
								it->val = 1; // override WR control signal
								signal.emplace_back(ts + 1, mux.out->WR_name, 0, 1, false); // control signal WR=0 next clock cycle
							}
							else // else generate two WR control signals (one for this clock cycle = 1, and the next = 0)
							{
								signal.emplace_back(ts, mux.out->WR_name, 1, 1, false);
								signal.emplace_back(ts + 1, mux.out->WR_name, 0, 1, false);
							}

							if (mux.in.size() > 1) // if the mux has more than one input
								for (int j = 0; j < mux.in.size(); j++) // find which input of the mux we must select on this time step
									if (&dp.funits[i] == mux.in[j])
									{
										signal.emplace_back(ts, mux.sel_name, j, mux.sel_size, true);
										break;
									}

							break;
						}

					break;
				}
	}

	// done signal
	signal.emplace_back(mts + 1, "done", 1, 1, false);
}