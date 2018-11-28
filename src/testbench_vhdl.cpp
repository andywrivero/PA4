#include "../header/testbench_vhdl.h"

void testbench_vhdl::create_vhdl_code (ostream &os)
{
	create_entity (os);
	create_architecture (os);
}

void testbench_vhdl::create_entity (ostream &os)
{
	os << "library IEEE;\n";
	os << "use IEEE.STD_LOGIC_1164.ALL;\n";
	os << "use ieee.numeric_std.all;\n\n";

	os << "entity " << entity_name << "_testbench is\n";
	os << "end " << entity_name << "_testbench;\n";
}

void testbench_vhdl::create_architecture (ostream &os)
{
	os << "\narchitecture " << entity_name << "_testbench_ar of " << entity_name << "_testbench is\n";

	create_signals(os);

	os << "\nbegin\n";

	create_datapath_instance(os);
	create_controller_instance(os);
	create_clock_process (os);
	create_test_process (os);

	os << "end " << entity_name << "_testbench_ar;\n";
}

void testbench_vhdl::create_datapath_instance (ostream &os)
{
	os << "DATAPATH : entity work." << entity_name + "_datapath (" << entity_name << "_datapath_ar)\n";
	os << "\t" << "port map(\n";
	
	for (const auto &r : g.edges)
		if (r.type != TEMP)
			os << "\t\t" << r.edge_name << " => " << r.edge_name << ",\n";
		
	for (const auto &r : dp.runits)
		if (!r.is_input)
			os << "\t\t" << r.WR_name << " => " << r.WR_name << ",\n";

	for (const auto &mux : dp.reg_mux)
		if (mux.in.size() > 1)
			os << "\t\t" << mux.sel_name << " => " << mux.sel_name << ",\n";

	for (const auto mux2 : dp.fu_mux)
	{
		if (mux2[0].in.size() > 1)
			os << "\t\t" << mux2[0].sel_name << " => " << mux2[0].sel_name << ",\n";

		if (mux2[1].in.size() > 1)
			os << "\t\t" << mux2[1].sel_name << " => " << mux2[1].sel_name << ",\n";
	}

	// other inputs	
	os << "\t\tclear => clear,\n";
	os << "\t\tclock => clock\n\t);\n\n";
}

void testbench_vhdl::create_controller_instance (ostream &os)
{
	os << "CONTROLLER : entity work." << entity_name + "_controller (" << entity_name << "_controller_ar)\n";
	os << "\tport map(\n";

	for (const auto &r : dp.runits)
		if (!r.is_input)
			os << "\t\t" << r.WR_name << " => " << r.WR_name << ",\n";

	for (const auto &mux : dp.reg_mux)
		if (mux.in.size() > 1)
			os << "\t\t" << mux.sel_name << " => " << mux.sel_name << ",\n";

	for (const auto mux2 : dp.fu_mux)
	{
		if (mux2[0].in.size() > 1)
			os << "\t\t" << mux2[0].sel_name << " => " << mux2[0].sel_name << ",\n";

		if (mux2[1].in.size() > 1)
			os << "\t\t" << mux2[1].sel_name << " => " << mux2[1].sel_name << ",\n";
	}

	os << "\t\tstart => start,\n"; 
	os << "\t\tdone => done,\n"; 
	os << "\t\tclear => clear,\n";
	os << "\t\tclock => clock\n\t);\n\n";
}

void testbench_vhdl::create_signals (ostream &os)
{
	// generate input/output ports
	os << "\t--------------------------- input/output signals declaration --------------------------------\n";

	for (const auto &r : g.edges)
		if (r.type != TEMP)
			os << "\tsignal " << r.edge_name << " : std_logic_vector(" << r.w - 1 << " downto 0);\n";

	os << "\t---------------------------------------------------------------------------------------------\n\n";

	os << "\t--------------------------- other signals declaration --------------------------------------------\n";

	// generate WR for the different registers
	for (const auto &r : dp.runits)
		if (!r.is_input)
			os << "\tsignal " << r.WR_name << " : std_logic;\n";

	// register multiplexers control signals
	for (const auto &mux : dp.reg_mux)
		if (mux.in.size() > 1)
			os << "\tsignal " << mux.sel_name << " : std_logic_vector(" << mux.sel_size - 1 << " downto 0);\n";

	// functional units multiplexers control signals
	for (const auto mux2 : dp.fu_mux)
	{
		if (mux2[0].in.size() > 1)
			os << "\tsignal " << mux2[0].sel_name << " : std_logic_vector(" << mux2[0].sel_size - 1 << " downto 0);\n";

		if (mux2[1].in.size() > 1)
			os << "\tsignal " << mux2[1].sel_name << " : std_logic_vector(" << mux2[1].sel_size - 1 << " downto 0);\n";
	}

	os << "\tsignal clock, clear, start, done : std_logic := '0';\n";
	os << "\tconstant clock_period : time := 10ns;\n";
	os << "\t---------------------------------------------------------------------------------------------------\n";
}

void testbench_vhdl::create_clock_process (ostream  &os)
{
	os <<"\tCLOCK_PROCESS : process\n";
	os <<"\tbegin\n";
	os << "\t\tclock <= '0';\n";
	os << "\t\twait for clock_period / 2;\n";	
	os << "\t\tclock <= '1';\n";	
	os << "\t\twait for clock_period / 2;\n";
	os <<"\tend process;\n\n";
}

void testbench_vhdl::create_test_process (ostream &os)
{
	os <<"\tTEST_PROCESS : process\n";
	os <<"\tbegin\n";
	os << "\t\tstart <= '0';\n";

	// Put all inputs signals values here
	os << "\t\t--------------------------- All input signals here --------------------------------\n";

	for (const auto &r : g.edges)
		if (r.type == IN)
			os << "\t\t--" << r.edge_name << " <= std_logic_vector (to_unsigned (, " << r.edge_name << "'length));\n";

	os << "\t\t----------------------------------------------------------------------------------\n";
	//

	os << "\t\twait for clock_period;\n";
	os << "\t\tstart <= '1';\n";
	os << "\t\twait for clock_period;\n";
	os << "\t\tstart <= '0';\n";
	os << "\t\twait;\n";
	os <<"\tend process;\n";
}