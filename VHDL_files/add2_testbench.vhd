library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use ieee.numeric_std.all;

entity add2_testbench is
end add2_testbench;

architecture add2_testbench_ar of add2_testbench is
	--------------------------- input/output signals declaration --------------------------------
	signal a : std_logic_vector(3 downto 0);
	signal b : std_logic_vector(3 downto 0);
	signal c : std_logic_vector(3 downto 0);
	---------------------------------------------------------------------------------------------

	--------------------------- other signals declaration --------------------------------------------
	signal r0_WR : std_logic;
	signal clock, clear, start, done : std_logic := '0';
	constant clock_period : time := 10ns;
	---------------------------------------------------------------------------------------------------

begin
DATAPATH : entity work.add2_datapath (add2_datapath_ar)
	port map(
		a => a,
		b => b,
		c => c,
		r0_WR => r0_WR,
		clear => clear,
		clock => clock
	);

CONTROLLER : entity work.add2_controller (add2_controller_ar)
	port map(
		r0_WR => r0_WR,
		start => start,
		done => done,
		clear => clear,
		clock => clock
	);

	CLOCK_PROCESS : process
	begin
		clock <= '0';
		wait for clock_period / 2;
		clock <= '1';
		wait for clock_period / 2;
	end process;

	TEST_PROCESS : process
	begin
		start <= '0';
		--------------------------- All input signals here --------------------------------
		--a <= std_logic_vector (to_unsigned (, a'length));
		--b <= std_logic_vector (to_unsigned (, b'length));
		----------------------------------------------------------------------------------
		wait until rising_edge(clock);
		start <= '1';
		wait until rising_edge(clock);
		start <= '0';
		wait;
	end process;
end add2_testbench_ar;
