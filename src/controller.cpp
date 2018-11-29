#include "../header/controller.h"

controller::controller (const datapath &dp)
{
	generate_control_signals (dp);	
}

void controller::generate_control_signals (const datapath &dp)
{
	// at time step 0 all registers WR=0 and done = 0
	for (const auto &r : dp.runits)
		if (!r.is_input)
			signal.emplace_back(0, r.WR_name, 0, 1, false);

	signal.emplace_back(0, "done", 0, 1, false);
	// rest of the time steps

	int mts = max_timestep(dp); // find the maximum time step

	for (int ts = 1; ts <= mts; ts++) // for each time step
		for (int i = 0; i < dp.funits.size(); i++) // for each functional unit
			for (int j = 0; j < dp.funits[i].ts.size(); j++) // for each time-step schedule of this functional unit
				if (dp.funits[i].ts[j] == ts) // if the j's time step is time-step "ts" 
				{
					create_mux_signal(dp.fu_mux[i][0], dp.funits[i].i[0][j], ts);
					create_mux_signal(dp.fu_mux[i][1], dp.funits[i].i[1][j], ts);
					create_mux_signal(dp.reg_mux, dp.funits[i], dp.funits[i].out[j], ts);
					break;
				}

	// done signal
	signal.emplace_back(mts + 1, "done", 1, 1, false);
}

void controller::create_mux_signal (const fmux_unit &mux, int e, int ts)
{
	if (mux.in.size() < 2) return;

	for (int i = 0; i < mux.in.size(); i++)
		if (find(mux.in[i]->edges.begin(), mux.in[i]->edges.end(), e) != mux.in[i]->edges.end())
		{
			signal.emplace_back(ts, mux.sel_name, i, mux.sel_size, true);
			return;
		}
}

void controller::create_mux_signal (const vector<rmux_unit> &reg_mux, const fu_unit &fu, int e, int ts)
{
	for (const auto &mux : reg_mux)
		if (find (mux.out->edges.begin(), mux.out->edges.end(), e) != mux.out->edges.end())
		{
			if (mux.in.size() > 1)
				for (int i = 0; i < mux.in.size (); i++)
					if (mux.in[i] == &fu)
					{
						signal.emplace_back(ts, mux.sel_name, i, mux.sel_size, true);
						break;
					}

			create_WR_signal(*mux.out, ts);
		}
}

void controller::create_WR_signal (const reg_unit &r, int ts)
{
	for (auto &s : signal)
		if (s.signal_name == r.WR_name && s.ts == ts)
		{
			s.val = 1;
			signal.emplace_back(ts + 1, s.signal_name, 0, 1, false);
			return;
		}

	signal.emplace_back(ts, r.WR_name, 1, 1, false);
	signal.emplace_back(ts + 1,r.WR_name, 0, 1, false);
}

int controller::max_timestep (const datapath &dp) const
{
	int mts = numeric_limits<int>::min ();

	for (auto &fu : dp.funits)
		for (int t : fu.ts)
			mts = std::max (mts, t);

	return mts;	
}