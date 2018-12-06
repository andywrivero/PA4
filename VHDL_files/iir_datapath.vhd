library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use ieee.numeric_std.all;

entity iir_datapath is
port
(
	a1 : in std_logic_vector(7 downto 0);
	y1 : in std_logic_vector(7 downto 0);
	a2 : in std_logic_vector(7 downto 0);
	y2 : in std_logic_vector(7 downto 0);
	b0 : in std_logic_vector(7 downto 0);
	x0 : in std_logic_vector(7 downto 0);
	b1 : in std_logic_vector(7 downto 0);
	x1 : in std_logic_vector(7 downto 0);
	b2 : in std_logic_vector(7 downto 0);
	x2 : in std_logic_vector(7 downto 0);
	yout : out std_logic_vector(7 downto 0);
	r0_WR : in std_logic;
	r1_WR : in std_logic;
	r2_WR : in std_logic;
	r3_WR : in std_logic;
	r0_mux_sel : in std_logic_vector(0 downto 0);
	r1_mux_sel : in std_logic_vector(1 downto 0);
	f1_MUX0_sel : in std_logic_vector(0 downto 0);
	f1_MUX1_sel : in std_logic_vector(0 downto 0);
	f2_MUX0_sel : in std_logic_vector(0 downto 0);
	f2_MUX1_sel : in std_logic_vector(0 downto 0);
	clear : in std_logic;
	clock : in std_logic);
end iir_datapath;

architecture iir_datapath_ar of iir_datapath is
-- registers units signals
	signal r0_in : std_logic_vector(7 downto 0);
	signal r0_out : std_logic_vector(7 downto 0);
	signal r1_in : std_logic_vector(7 downto 0);
	signal r1_out : std_logic_vector(7 downto 0);
	signal r2_in : std_logic_vector(7 downto 0);
	signal r2_out : std_logic_vector(7 downto 0);
	signal r3_in : std_logic_vector(7 downto 0);
	signal r3_out : std_logic_vector(7 downto 0);
-- functional units signals
	signal fu0_i1 : std_logic_vector(7 downto 0);
	signal fu0_i2 : std_logic_vector(7 downto 0);
	signal fu0_out : std_logic_vector(7 downto 0);
	signal fu1_i1 : std_logic_vector(7 downto 0);
	signal fu1_i2 : std_logic_vector(7 downto 0);
	signal fu1_out : std_logic_vector(7 downto 0);
	signal fu2_i1 : std_logic_vector(7 downto 0);
	signal fu2_i2 : std_logic_vector(7 downto 0);
	signal fu2_out : std_logic_vector(7 downto 0);
	signal fu3_i1 : std_logic_vector(7 downto 0);
	signal fu3_i2 : std_logic_vector(7 downto 0);
	signal fu3_out : std_logic_vector(7 downto 0);
	signal fu4_i1 : std_logic_vector(7 downto 0);
	signal fu4_i2 : std_logic_vector(7 downto 0);
	signal fu4_out : std_logic_vector(7 downto 0);

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

R2 : entity work.c_register
	generic map
	(width => 8)
	port map
	(input => r2_in,
	output => r2_out,
	WR => r2_WR,
	clear => clear,
	clock => clock);

R3 : entity work.c_register
	generic map
	(width => 8)
	port map
	(input => r3_in,
	output => r3_out,
	WR => r3_WR,
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

FU2 : entity work.c_multiplier
	generic map
	(width => 8)
	port map
	(input1 => fu2_i1,
	input2 => fu2_i2,
	output => fu2_out);

FU3 : entity work.c_adder
	generic map
	(width => 8)
	port map
	(input1 => fu3_i1,
	input2 => fu3_i2,
	output => fu3_out);

FU4 : entity work.c_multiplier
	generic map
	(width => 8)
	port map
	(input1 => fu4_i1,
	input2 => fu4_i2,
	output => fu4_out);

-- MUX for registers
R0_MUX : entity work.c_multiplexer
	generic map
	(width => 8,
	no_of_inputs => 2,
	select_size => 1)
	port map
	(input(7 downto 0) => fu0_out,
	input(15 downto 8) => fu2_out,
	output => r0_in,
	mux_select => r0_mux_sel);

R1_MUX : entity work.c_multiplexer
	generic map
	(width => 8,
	no_of_inputs => 3,
	select_size => 2)
	port map
	(input(7 downto 0) => fu1_out,
	input(15 downto 8) => fu3_out,
	input(23 downto 16) => fu4_out,
	output => r1_in,
	mux_select => r1_mux_sel);

	r2_in <= fu0_out;

	r3_in <= fu1_out;

-- MUX for functional units
	fu0_i1 <= r0_out;

	fu0_i2 <= r1_out;

F1_MUX0 : entity work.c_multiplexer
	generic map
	(width => 8,
	no_of_inputs => 2,
	select_size => 1)
	port map
	(input(7 downto 0) => b2,
	input(15 downto 8) => b1,
	output => fu1_i1,
	mux_select => f1_MUX0_sel);

F1_MUX1 : entity work.c_multiplexer
	generic map
	(width => 8,
	no_of_inputs => 2,
	select_size => 1)
	port map
	(input(7 downto 0) => x2,
	input(15 downto 8) => x1,
	output => fu1_i2,
	mux_select => f1_MUX1_sel);

F2_MUX0 : entity work.c_multiplexer
	generic map
	(width => 8,
	no_of_inputs => 2,
	select_size => 1)
	port map
	(input(7 downto 0) => b0,
	input(15 downto 8) => a1,
	output => fu2_i1,
	mux_select => f2_MUX0_sel);

F2_MUX1 : entity work.c_multiplexer
	generic map
	(width => 8,
	no_of_inputs => 2,
	select_size => 1)
	port map
	(input(7 downto 0) => x0,
	input(15 downto 8) => y1,
	output => fu2_i2,
	mux_select => f2_MUX1_sel);

	fu3_i1 <= r2_out;

	fu3_i2 <= r3_out;

	fu4_i1 <= a2;

	fu4_i2 <= y2;

-- Outputs
	yout <= r0_out;
end iir_datapath_ar;
