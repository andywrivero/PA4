library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use ieee.numeric_std.all;

entity iir_testbench is
end iir_testbench;

architecture iir_testbench_ar of iir_testbench is
	--------------------------- input/output signals declaration --------------------------------
	signal a1 : std_logic_vector(7 downto 0);
	signal y1 : std_logic_vector(7 downto 0);
	signal a2 : std_logic_vector(7 downto 0);
	signal y2 : std_logic_vector(7 downto 0);
	signal b0 : std_logic_vector(7 downto 0);
	signal x0 : std_logic_vector(7 downto 0);
	signal b1 : std_logic_vector(7 downto 0);
	signal x1 : std_logic_vector(7 downto 0);
	signal b2 : std_logic_vector(7 downto 0);
	signal x2 : std_logic_vector(7 downto 0);
	signal yout : std_logic_vector(7 downto 0);
	---------------------------------------------------------------------------------------------

	--------------------------- other signals declaration --------------------------------------------
	signal r0_WR : std_logic;
	signal r1_WR : std_logic;
	signal r2_WR : std_logic;
	signal r3_WR : std_logic;
	signal r0_mux_sel : std_logic_vector(0 downto 0);
	signal r1_mux_sel : std_logic_vector(1 downto 0);
	signal f1_MUX0_sel : std_logic_vector(0 downto 0);
	signal f1_MUX1_sel : std_logic_vector(0 downto 0);
	signal f2_MUX0_sel : std_logic_vector(0 downto 0);
	signal f2_MUX1_sel : std_logic_vector(0 downto 0);
	signal clock, clear, start, done : std_logic := '0';
	constant clock_period : time := 10ns;
	---------------------------------------------------------------------------------------------------

begin
DATAPATH : entity work.iir_datapath (iir_datapath_ar)
	port map(
		a1 => a1,
		y1 => y1,
		a2 => a2,
		y2 => y2,
		b0 => b0,
		x0 => x0,
		b1 => b1,
		x1 => x1,
		b2 => b2,
		x2 => x2,
		yout => yout,
		r0_WR => r0_WR,
		r1_WR => r1_WR,
		r2_WR => r2_WR,
		r3_WR => r3_WR,
		r0_mux_sel => r0_mux_sel,
		r1_mux_sel => r1_mux_sel,
		f1_MUX0_sel => f1_MUX0_sel,
		f1_MUX1_sel => f1_MUX1_sel,
		f2_MUX0_sel => f2_MUX0_sel,
		f2_MUX1_sel => f2_MUX1_sel,
		clear => clear,
		clock => clock
	);

CONTROLLER : entity work.iir_controller (iir_controller_ar)
	port map(
		r0_WR => r0_WR,
		r1_WR => r1_WR,
		r2_WR => r2_WR,
		r3_WR => r3_WR,
		r0_mux_sel => r0_mux_sel,
		r1_mux_sel => r1_mux_sel,
		f1_MUX0_sel => f1_MUX0_sel,
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
		--a1 <= std_logic_vector (to_unsigned (, a1'length));
		--y1 <= std_logic_vector (to_unsigned (, y1'length));
		--a2 <= std_logic_vector (to_unsigned (, a2'length));
		--y2 <= std_logic_vector (to_unsigned (, y2'length));
		--b0 <= std_logic_vector (to_unsigned (, b0'length));
		--x0 <= std_logic_vector (to_unsigned (, x0'length));
		--b1 <= std_logic_vector (to_unsigned (, b1'length));
		--x1 <= std_logic_vector (to_unsigned (, x1'length));
		--b2 <= std_logic_vector (to_unsigned (, b2'length));
		--x2 <= std_logic_vector (to_unsigned (, x2'length));
		----------------------------------------------------------------------------------
		wait until rising_edge(clock);
		start <= '1';
		wait until rising_edge(clock);
		start <= '0';
		wait;
	end process;
end iir_testbench_ar;
