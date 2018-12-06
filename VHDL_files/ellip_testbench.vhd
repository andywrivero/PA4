library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use ieee.numeric_std.all;

entity ellip_testbench is
end ellip_testbench;

architecture ellip_testbench_ar of ellip_testbench is
	--------------------------- input/output signals declaration --------------------------------
	signal inp : std_logic_vector(3 downto 0);
	signal svin2 : std_logic_vector(3 downto 0);
	signal svin13 : std_logic_vector(3 downto 0);
	signal svin18 : std_logic_vector(3 downto 0);
	signal svin26 : std_logic_vector(3 downto 0);
	signal svin33 : std_logic_vector(3 downto 0);
	signal svin38 : std_logic_vector(3 downto 0);
	signal svin39 : std_logic_vector(3 downto 0);
	signal TWO : std_logic_vector(3 downto 0);
	signal svout2 : std_logic_vector(3 downto 0);
	signal svout13 : std_logic_vector(3 downto 0);
	signal svout18 : std_logic_vector(3 downto 0);
	signal svout26 : std_logic_vector(3 downto 0);
	signal svout33 : std_logic_vector(3 downto 0);
	signal svout38 : std_logic_vector(3 downto 0);
	signal svout39 : std_logic_vector(3 downto 0);
	---------------------------------------------------------------------------------------------

	--------------------------- other signals declaration --------------------------------------------
	signal r0_WR : std_logic;
	signal r1_WR : std_logic;
	signal r2_WR : std_logic;
	signal r3_WR : std_logic;
	signal r4_WR : std_logic;
	signal r5_WR : std_logic;
	signal r6_WR : std_logic;
	signal r7_WR : std_logic;
	signal r8_WR : std_logic;
	signal r0_mux_sel : std_logic_vector(1 downto 0);
	signal r1_mux_sel : std_logic_vector(0 downto 0);
	signal r2_mux_sel : std_logic_vector(1 downto 0);
	signal r3_mux_sel : std_logic_vector(1 downto 0);
	signal r4_mux_sel : std_logic_vector(1 downto 0);
	signal r5_mux_sel : std_logic_vector(1 downto 0);
	signal r6_mux_sel : std_logic_vector(1 downto 0);
	signal r7_mux_sel : std_logic_vector(0 downto 0);
	signal r8_mux_sel : std_logic_vector(0 downto 0);
	signal f0_MUX0_sel : std_logic_vector(2 downto 0);
	signal f0_MUX1_sel : std_logic_vector(3 downto 0);
	signal f1_MUX0_sel : std_logic_vector(1 downto 0);
	signal f1_MUX1_sel : std_logic_vector(2 downto 0);
	signal f2_MUX0_sel : std_logic_vector(1 downto 0);
	signal f3_MUX0_sel : std_logic_vector(0 downto 0);
	signal f3_MUX1_sel : std_logic_vector(1 downto 0);
	signal f4_MUX0_sel : std_logic_vector(1 downto 0);
	signal clock, clear, start, done : std_logic := '0';
	constant clock_period : time := 10ns;
	---------------------------------------------------------------------------------------------------

begin
DATAPATH : entity work.ellip_datapath (ellip_datapath_ar)
	port map(
		inp => inp,
		svin2 => svin2,
		svin13 => svin13,
		svin18 => svin18,
		svin26 => svin26,
		svin33 => svin33,
		svin38 => svin38,
		svin39 => svin39,
		TWO => TWO,
		svout2 => svout2,
		svout13 => svout13,
		svout18 => svout18,
		svout26 => svout26,
		svout33 => svout33,
		svout38 => svout38,
		svout39 => svout39,
		r0_WR => r0_WR,
		r1_WR => r1_WR,
		r2_WR => r2_WR,
		r3_WR => r3_WR,
		r4_WR => r4_WR,
		r5_WR => r5_WR,
		r6_WR => r6_WR,
		r7_WR => r7_WR,
		r8_WR => r8_WR,
		r0_mux_sel => r0_mux_sel,
		r1_mux_sel => r1_mux_sel,
		r2_mux_sel => r2_mux_sel,
		r3_mux_sel => r3_mux_sel,
		r4_mux_sel => r4_mux_sel,
		r5_mux_sel => r5_mux_sel,
		r6_mux_sel => r6_mux_sel,
		r7_mux_sel => r7_mux_sel,
		r8_mux_sel => r8_mux_sel,
		f0_MUX0_sel => f0_MUX0_sel,
		f0_MUX1_sel => f0_MUX1_sel,
		f1_MUX0_sel => f1_MUX0_sel,
		f1_MUX1_sel => f1_MUX1_sel,
		f2_MUX0_sel => f2_MUX0_sel,
		f3_MUX0_sel => f3_MUX0_sel,
		f3_MUX1_sel => f3_MUX1_sel,
		f4_MUX0_sel => f4_MUX0_sel,
		clear => clear,
		clock => clock
	);

CONTROLLER : entity work.ellip_controller (ellip_controller_ar)
	port map(
		r0_WR => r0_WR,
		r1_WR => r1_WR,
		r2_WR => r2_WR,
		r3_WR => r3_WR,
		r4_WR => r4_WR,
		r5_WR => r5_WR,
		r6_WR => r6_WR,
		r7_WR => r7_WR,
		r8_WR => r8_WR,
		r0_mux_sel => r0_mux_sel,
		r1_mux_sel => r1_mux_sel,
		r2_mux_sel => r2_mux_sel,
		r3_mux_sel => r3_mux_sel,
		r4_mux_sel => r4_mux_sel,
		r5_mux_sel => r5_mux_sel,
		r6_mux_sel => r6_mux_sel,
		r7_mux_sel => r7_mux_sel,
		r8_mux_sel => r8_mux_sel,
		f0_MUX0_sel => f0_MUX0_sel,
		f0_MUX1_sel => f0_MUX1_sel,
		f1_MUX0_sel => f1_MUX0_sel,
		f1_MUX1_sel => f1_MUX1_sel,
		f2_MUX0_sel => f2_MUX0_sel,
		f3_MUX0_sel => f3_MUX0_sel,
		f3_MUX1_sel => f3_MUX1_sel,
		f4_MUX0_sel => f4_MUX0_sel,
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
		--inp <= std_logic_vector (to_unsigned (, inp'length));
		--svin2 <= std_logic_vector (to_unsigned (, svin2'length));
		--svin13 <= std_logic_vector (to_unsigned (, svin13'length));
		--svin18 <= std_logic_vector (to_unsigned (, svin18'length));
		--svin26 <= std_logic_vector (to_unsigned (, svin26'length));
		--svin33 <= std_logic_vector (to_unsigned (, svin33'length));
		--svin38 <= std_logic_vector (to_unsigned (, svin38'length));
		--svin39 <= std_logic_vector (to_unsigned (, svin39'length));
		--TWO <= std_logic_vector (to_unsigned (, TWO'length));
		----------------------------------------------------------------------------------
		wait until rising_edge(clock);
		start <= '1';
		wait until rising_edge(clock);
		start <= '0';
		wait;
	end process;
end ellip_testbench_ar;
