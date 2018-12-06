/****************************************************************************
 * Digital Circuit Synthesis Final Project
 * Controller, Datapath, and Testbench generation using Data Flow Graphs
 * 
 * Authors: Anthony Teresi, Mary Mouro, and Andy Rivero
 * 
 * Source File
 * This generates the VHDL datapath
****************************************************************************/

#include "../header/datapath_vhdl.h"

void datapath_vhdl::create_vhdl_code(ostream &os)
{
	cout << "Creating Datapath Entity\n";
	create_entity(os);
	cout << "Creating Datapath Architecture\n";
	create_architecture(os);
}

void datapath_vhdl::create_entity (ostream &os)
{
	os << "library IEEE;\n";
	os << "use IEEE.STD_LOGIC_1164.ALL;\n";
	os << "use ieee.numeric_std.all;\n\n";

	os << "entity " << entity_name << "_datapath is\n";

	os << "port\n(\n";	

	// generate input/output ports
	for (const auto &r : g.edges)
		if (r.type == IN)
			os << "\t" << r.edge_name << " : in std_logic_vector(" << r.w - 1 << " downto 0);\n";
		else if (r.type == OUT)
			os << "\t" << r.edge_name << " : out std_logic_vector(" << r.w - 1 << " downto 0);\n";

	// generate WR for the different registers
	for (const auto &r : dp.runits)
		if (!r.is_input)
			os << "\t" << r.WR_name << " : in std_logic;\n";

	// register multiplexers control signals
	for (const auto &mux : dp.reg_mux)
		if (mux.in.size() > 1)
			os << "\t" << mux.sel_name << " : in std_logic_vector(" << mux.sel_size - 1 << " downto 0);\n";

	// functional units multiplexers control signals
	for (const auto mux2 : dp.fu_mux)
	{
		if (mux2[0].in.size() > 1)
			os << "\t" << mux2[0].sel_name << " : in std_logic_vector(" << mux2[0].sel_size - 1 << " downto 0);\n";

		if (mux2[1].in.size() > 1)
			os << "\t" << mux2[1].sel_name << " : in std_logic_vector(" << mux2[1].sel_size - 1 << " downto 0);\n";
	}

	// other inputs	
	os << "\tclear : in std_logic;\n";
	os << "\tclock : in std_logic);\n";

	os << "end " << entity_name << "_datapath;\n";
}

void datapath_vhdl::create_architecture (ostream &os)
{
	os << "\narchitecture " << entity_name << "_datapath_ar of " << entity_name << "_datapath is\n";

	create_signals(os);

	os << "\nbegin\n";

	create_registers(os); // registers
	create_funits(os); // functional units
	create_reg_mux (os); // register muxes
	create_fu_mux(os); // functional units muxes
	create_output(os); // links to outputs signals

	os << "end " << entity_name << "_datapath_ar;\n";
}

void datapath_vhdl::create_signals (ostream &os)
{
	// create signals here
	os << "-- registers units signals\n";
	for (const auto &r : dp.runits)
		if (!r.is_input)
		{
			os << "\tsignal " << r.in_name << " : std_logic_vector(" << r.w - 1 << " downto 0);\n";
			os << "\tsignal " << r.out_name << " : std_logic_vector(" << r.w - 1 << " downto 0);\n";
		}

	os << "-- functional units signals\n";	
	for (const auto &fu : dp.funits)
	{
		os << "\tsignal " << fu.i1_name << " : std_logic_vector(" << fu.w - 1 << " downto 0);\n";
		os << "\tsignal " << fu.i2_name << " : std_logic_vector(" << fu.w - 1 << " downto 0);\n";
		os << "\tsignal " << fu.out_name << " : std_logic_vector(" << fu.w - 1 << " downto 0);\n";
	}
}

void datapath_vhdl::create_registers (ostream &os)
{
	os << "-- Registers\n";

	for (const auto &r : dp.runits)
		if (!r.is_input)
		{
			os << r.reg_name << " : entity work." << "c_register\n";
			os << "\tgeneric map\n";
			os << "\t(width => " << r.w << ")\n";
			os << "\t" << "port map\n";
			os << "\t(input => " << r.in_name << ",\n";
			os << "\toutput => " << r.out_name << ",\n";
			os << "\tWR => " << r.WR_name << ",\n";
			os << "\tclear => clear,\n";
			os << "\tclock => clock);\n\n";
		}
}

void datapath_vhdl::create_funits (ostream &os)
{
	os << "-- Functional units\n";

	for (const auto &fu : dp.funits)   
		switch (fu.type)
		{
			case ADD: 
				os << fu.fu_name << " : entity work." << "c_adder\n";
				os << "\tgeneric map\n";
				os << "\t(width => " << fu.w << ")\n";
				os << "\tport map\n";
				os << "\t(input1 => " << fu.i1_name << ",\n";
				os << "\tinput2 => " << fu.i2_name << ",\n";
				os << "\toutput => " << fu.out_name << ");\n\n";
			break;
			case SUB: 
				os << fu.fu_name << " : entity work." << "c_subtractor\n";
				os << "\tgeneric map\n";
				os << "\t(width => " << fu.w << ")\n";
				os << "\tport map\n";
				os << "\t(input1 => " << fu.i1_name << ",\n";
				os << "\tinput2 => " << fu.i2_name << ",\n";
				os << "\toutput => " << fu.out_name << ");\n\n";
			break;
			case MULT: 
				os << fu.fu_name << " : entity work." << "c_multiplier\n";
				os << "\tgeneric map\n";
				os << "\t(width => " << fu.w << ")\n";
				os << "\tport map\n";
				os << "\t(input1 => " << fu.i1_name << ",\n";
				os << "\tinput2 => " << fu.i2_name << ",\n";
				os << "\toutput => " << fu.out_name << ");\n\n";
			break;
			case DIV:
				os << fu.fu_name << " : entity work." << "c_divider\n";
				os << "\tgeneric map\n";
				os << "\t(width => " << fu.w << ")\n";
				os << "\tport map\n";
				os << "\t(input1 => " << fu.i1_name << ",\n";
				os << "\tinput2 => " << fu.i2_name << ",\n";
				os << "\toutput => " << fu.out_name << ");\n\n";
			default: ;
		}
}

void datapath_vhdl::create_reg_mux (ostream &os)
{
	os << "-- MUX for registers\n";

	for (const auto &mux : dp.reg_mux)
		if (mux.in.size() == 1)
			os << "\t" << mux.out->in_name << " <= " << mux.in[0]->out_name << ";\n\n";
		else
		{
			os << mux.mux_name << " : entity work." << "c_multiplexer\n";
			os << "\tgeneric map\n";
			os << "\t(width => " << mux.w << ",\n";
			os << "\tno_of_inputs => " << mux.in.size() << ",\n";
			os << "\tselect_size => " << mux.sel_size << ")\n";
			os << "\tport map\n";
			os << "\t(";
			
			for (int i = 0, from = mux.w - 1, to = 0; i < mux.in.size(); i++, from += mux.w, to += mux.w)
			{
				if (i > 0) os << "\t";

				os << "input(" << from << " downto " << to << ") => " << mux.in[i]->out_name << ",\n";
			}

			os << "\toutput => " << mux.out->in_name << ",\n";
			os << "\tmux_select => " << mux.sel_name << ");\n\n";
		}
}

void datapath_vhdl::create_fu_mux (ostream &os)
{
	os << "-- MUX for functional units\n";

	for (const auto &mux2 : dp.fu_mux)
		for (int m = 0; m < 2; m++)
		{
			const auto &mux = mux2[m];

			if (mux.in.size() == 1)
			{
				if (m == 0)
					os << "\t" << mux.out->i1_name << " <= " << mux.in[0]->out_name << ";\n\n";
				else
					os << "\t" << mux.out->i2_name << " <= " << mux.in[0]->out_name << ";\n\n";
			}
			else
			{
				os << mux.mux_name << " : entity work." << "c_multiplexer\n";
				os << "\tgeneric map\n";
				os << "\t(width => " << mux.w << ",\n";
				os << "\tno_of_inputs => " << mux.in.size() << ",\n";
				os << "\tselect_size => " << mux.sel_size << ")\n";
				os << "\tport map\n";
				os << "\t(";
			
				for (int i = 0, from = mux.w - 1, to = 0; i < mux.in.size(); i++, from += mux.w, to += mux.w)
				{
					if (i > 0) os << "\t";

					os << "input(" << from << " downto " << to << ") => " << mux.in[i]->out_name << ",\n";			
				}

				if (m == 0)
					os << "\toutput => " << mux.out->i1_name << ",\n";
				else
					os << "\toutput => " << mux.out->i2_name << ",\n";

				os << "\tmux_select => " << mux.sel_name << ");\n\n";
			}
		}
}

void datapath_vhdl::create_output (ostream &os)
{
	os << "-- Outputs\n";

	for (auto p : dp.outl)
		os << "\t" << p.first << " <= " << p.second << ";\n";
}