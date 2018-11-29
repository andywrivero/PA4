library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use ieee.numeric_std.all;

entity mult3_testbench is
end mult3_testbench;

architecture mult3_testbench_ar of mult3_testbench is
	--------------------------- input/output signals declaration --------------------------------
	signal x1 : std_logic_vector(7 downto 0);
	signal x2 : std_logic_vector(7 downto 0);
	signal x3 : std_logic_vector(7 downto 0);
	signal x4 : std_logic_vector(7 downto 0);
	signal z : std_logic_vector(7 downto 0);
	---------------------------------------------------------------------------------------------

	--------------------------- other signals declaration --------------------------------------------
	signal r0_WR : std_logic;
	signal r1_WR : std_logic;
	signal f0_MUX0_sel : std_logic_vector(0 downto 0);
	signal f0_MUX1_sel : std_logic_vector(0 downto 0);
	signal clock, clear, start, done : std_logic := '0';
	constant clock_period : time := 10ns;
	---------------------------------------------------------------------------------------------------

begin
DATAPATH : entity work.mult3_datapath (mult3_datapath_ar)
	port map(
		x1 => x1,
		x2 => x2,
		x3 => x3,
		x4 => x4,
		z => z,
		r0_WR => r0_WR,
		r1_WR => r1_WR,
		f0_MUX0_sel => f0_MUX0_sel,
		f0_MUX1_sel => f0_MUX1_sel,
		clear => clear,
		clock => clock
	);

CONTROLLER : entity work.mult3_controller (mult3_controller_ar)
	port map(
		r0_WR => r0_WR,
		r1_WR => r1_WR,
		f0_MUX0_sel => f0_MUX0_sel,
		f0_MUX1_sel => f0_MUX1_sel,
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
		--x1 <= std_logic_vector (to_unsigned (, x1'length));
		--x2 <= std_logic_vector (to_unsigned (, x2'length));
		--x3 <= std_logic_vector (to_unsigned (, x3'length));
		--x4 <= std_logic_vector (to_unsigned (, x4'length));
		----------------------------------------------------------------------------------
		wait until rising_edge(clock);
		start <= '1';
		wait until rising_edge(clock);
		start <= '0';
		wait;
	end process;
end mult3_testbench_ar;
