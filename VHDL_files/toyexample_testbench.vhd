library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use ieee.numeric_std.all;

entity toyexample_testbench is
end toyexample_testbench;

architecture toyexample_testbench_ar of toyexample_testbench is
	--------------------------- input/output signals declaration --------------------------------
	signal a : std_logic_vector(3 downto 0);
	signal b : std_logic_vector(3 downto 0);
	signal c : std_logic_vector(3 downto 0);
	signal d : std_logic_vector(3 downto 0);
	signal e : std_logic_vector(3 downto 0);
	signal f : std_logic_vector(3 downto 0);
	signal g : std_logic_vector(3 downto 0);
	signal h : std_logic_vector(3 downto 0);
	signal i : std_logic_vector(3 downto 0);
	---------------------------------------------------------------------------------------------

	--------------------------- other signals declaration --------------------------------------------
	signal r0_WR : std_logic;
	signal r1_WR : std_logic;
	signal r0_mux_sel : std_logic_vector(0 downto 0);
	signal r1_mux_sel : std_logic_vector(0 downto 0);
	signal f0_MUX0_sel : std_logic_vector(1 downto 0);
	signal f0_MUX1_sel : std_logic_vector(1 downto 0);
	signal f1_MUX1_sel : std_logic_vector(0 downto 0);
	signal f2_MUX0_sel : std_logic_vector(0 downto 0);
	signal f2_MUX1_sel : std_logic_vector(0 downto 0);
	signal clock, clear, start, done : std_logic := '0';
	constant clock_period : time := 10ns;
	---------------------------------------------------------------------------------------------------

begin
DATAPATH : entity work.toyexample_datapath (toyexample_datapath_ar)
	port map(
		a => a,
		b => b,
		c => c,
		d => d,
		e => e,
		f => f,
		g => g,
		h => h,
		i => i,
		r0_WR => r0_WR,
		r1_WR => r1_WR,
		r0_mux_sel => r0_mux_sel,
		r1_mux_sel => r1_mux_sel,
		f0_MUX0_sel => f0_MUX0_sel,
		f0_MUX1_sel => f0_MUX1_sel,
		f1_MUX1_sel => f1_MUX1_sel,
		f2_MUX0_sel => f2_MUX0_sel,
		f2_MUX1_sel => f2_MUX1_sel,
		clear => clear,
		clock => clock
	);

CONTROLLER : entity work.toyexample_controller (toyexample_controller_ar)
	port map(
		r0_WR => r0_WR,
		r1_WR => r1_WR,
		r0_mux_sel => r0_mux_sel,
		r1_mux_sel => r1_mux_sel,
		f0_MUX0_sel => f0_MUX0_sel,
		f0_MUX1_sel => f0_MUX1_sel,
		f1_MUX1_sel => f1_MUX1_sel,
		f2_MUX0_sel => f2_MUX0_sel,
		f2_MUX1_sel => f2_MUX1_sel,
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
		--c <= std_logic_vector (to_unsigned (, c'length));
		--d <= std_logic_vector (to_unsigned (, d'length));
		--e <= std_logic_vector (to_unsigned (, e'length));
		--f <= std_logic_vector (to_unsigned (, f'length));
		--g <= std_logic_vector (to_unsigned (, g'length));
		--h <= std_logic_vector (to_unsigned (, h'length));
		----------------------------------------------------------------------------------
		wait until rising_edge(clock);
		start <= '1';
		wait until rising_edge(clock);
		start <= '0';
		wait;
	end process;
end toyexample_testbench_ar;
