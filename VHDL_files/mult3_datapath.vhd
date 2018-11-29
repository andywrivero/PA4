library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use ieee.numeric_std.all;

entity mult3_datapath is
port
(
	x1 : in std_logic_vector(7 downto 0);
	x2 : in std_logic_vector(7 downto 0);
	x3 : in std_logic_vector(7 downto 0);
	x4 : in std_logic_vector(7 downto 0);
	z : out std_logic_vector(7 downto 0);
	r0_WR : in std_logic;
	r1_WR : in std_logic;
	f0_MUX0_sel : in std_logic_vector(0 downto 0);
	f0_MUX1_sel : in std_logic_vector(0 downto 0);
	clear : in std_logic;
	clock : in std_logic);
end mult3_datapath;

architecture mult3_datapath_ar of mult3_datapath is
-- registers units signals
	signal r0_in : std_logic_vector(7 downto 0);
	signal r0_out : std_logic_vector(7 downto 0);
	signal r1_in : std_logic_vector(7 downto 0);
	signal r1_out : std_logic_vector(7 downto 0);
-- functional units signals
	signal fu0_i1 : std_logic_vector(7 downto 0);
	signal fu0_i2 : std_logic_vector(7 downto 0);
	signal fu0_out : std_logic_vector(7 downto 0);
	signal fu1_i1 : std_logic_vector(7 downto 0);
	signal fu1_i2 : std_logic_vector(7 downto 0);
	signal fu1_out : std_logic_vector(7 downto 0);

begin
-- Registers
R0 : entity work.c_register
	generic map
	(width => 8)
	port map
	(input => r0_in,
	output => r0_out,
	WR => r0_WR,
	clear => clear,
	clock => clock);

R1 : entity work.c_register
	generic map
	(width => 8)
	port map
	(input => r1_in,
	output => r1_out,
	WR => r1_WR,
	clear => clear,
	clock => clock);

-- Functional units
FU0 : entity work.c_adder
	generic map
	(width => 8)
	port map
	(input1 => fu0_i1,
	input2 => fu0_i2,
	output => fu0_out);

FU1 : entity work.c_multiplier
	generic map
	(width => 8)
	port map
	(input1 => fu1_i1,
	input2 => fu1_i2,
	output => fu1_out);

-- MUX for registers
	r0_in <= fu0_out;

	r1_in <= fu1_out;

-- MUX for functional units
F0_MUX0 : entity work.c_multiplexer
	generic map
	(width => 8,
	no_of_inputs => 2,
	select_size => 1)
	port map
	(input(7 downto 0) => r0_out,
	input(15 downto 8) => x1,
	output => fu0_i1,
	mux_select => f0_MUX0_sel);

F0_MUX1 : entity work.c_multiplexer
	generic map
	(width => 8,
	no_of_inputs => 2,
	select_size => 1)
	port map
	(input(7 downto 0) => r1_out,
	input(15 downto 8) => x2,
	output => fu0_i2,
	mux_select => f0_MUX1_sel);

	fu1_i1 <= x3;

	fu1_i2 <= x4;

-- Outputs
	z <= r0_out;
end mult3_datapath_ar;
