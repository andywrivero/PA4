library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use ieee.numeric_std.all;

entity toyexample_datapath is
port
(
	a : in std_logic_vector(3 downto 0);
	b : in std_logic_vector(3 downto 0);
	c : in std_logic_vector(3 downto 0);
	d : in std_logic_vector(3 downto 0);
	e : in std_logic_vector(3 downto 0);
	f : in std_logic_vector(3 downto 0);
	g : in std_logic_vector(3 downto 0);
	h : in std_logic_vector(3 downto 0);
	i : out std_logic_vector(3 downto 0);
	r0_WR : in std_logic;
	r1_WR : in std_logic;
	r0_mux_sel : in std_logic_vector(0 downto 0);
	r1_mux_sel : in std_logic_vector(0 downto 0);
	f0_MUX0_sel : in std_logic_vector(1 downto 0);
	f0_MUX1_sel : in std_logic_vector(1 downto 0);
	f1_MUX1_sel : in std_logic_vector(0 downto 0);
	f2_MUX0_sel : in std_logic_vector(0 downto 0);
	f2_MUX1_sel : in std_logic_vector(0 downto 0);
	clear : in std_logic;
	clock : in std_logic);
end toyexample_datapath;

architecture toyexample_datapath_ar of toyexample_datapath is
-- registers units signals
	signal r0_in : std_logic_vector(3 downto 0);
	signal r0_out : std_logic_vector(3 downto 0);
	signal r1_in : std_logic_vector(3 downto 0);
	signal r1_out : std_logic_vector(3 downto 0);
-- functional units signals
	signal fu0_i1 : std_logic_vector(3 downto 0);
	signal fu0_i2 : std_logic_vector(3 downto 0);
	signal fu0_out : std_logic_vector(3 downto 0);
	signal fu1_i1 : std_logic_vector(3 downto 0);
	signal fu1_i2 : std_logic_vector(3 downto 0);
	signal fu1_out : std_logic_vector(3 downto 0);
	signal fu2_i1 : std_logic_vector(3 downto 0);
	signal fu2_i2 : std_logic_vector(3 downto 0);
	signal fu2_out : std_logic_vector(3 downto 0);

begin
-- Registers
R0 : entity work.c_register
	generic map
	(width => 4)
	port map
	(input => r0_in,
	output => r0_out,
	WR => r0_WR,
	clear => clear,
	clock => clock);

R1 : entity work.c_register
	generic map
	(width => 4)
	port map
	(input => r1_in,
	output => r1_out,
	WR => r1_WR,
	clear => clear,
	clock => clock);

-- Functional units
FU0 : entity work.c_multiplier
	generic map
	(width => 4)
	port map
	(input1 => fu0_i1,
	input2 => fu0_i2,
	output => fu0_out);

FU1 : entity work.c_subtractor
	generic map
	(width => 4)
	port map
	(input1 => fu1_i1,
	input2 => fu1_i2,
	output => fu1_out);

FU2 : entity work.c_multiplier
	generic map
	(width => 4)
	port map
	(input1 => fu2_i1,
	input2 => fu2_i2,
	output => fu2_out);

-- MUX for registers
R0_MUX : entity work.c_multiplexer
	generic map
	(width => 4,
	no_of_inputs => 2,
	select_size => 1)
	port map
	(input(3 downto 0) => fu0_out,
	input(7 downto 4) => fu1_out,
	output => r0_in,
	mux_select => r0_mux_sel);

R1_MUX : entity work.c_multiplexer
	generic map
	(width => 4,
	no_of_inputs => 2,
	select_size => 1)
	port map
	(input(3 downto 0) => fu1_out,
	input(7 downto 4) => fu2_out,
	output => r1_in,
	mux_select => r1_mux_sel);

-- MUX for functional units
F0_MUX0 : entity work.c_multiplexer
	generic map
	(width => 4,
	no_of_inputs => 3,
	select_size => 2)
	port map
	(input(3 downto 0) => g,
	input(7 downto 4) => e,
	input(11 downto 8) => a,
	output => fu0_i1,
	mux_select => f0_MUX0_sel);

F0_MUX1 : entity work.c_multiplexer
	generic map
	(width => 4,
	no_of_inputs => 3,
	select_size => 2)
	port map
	(input(3 downto 0) => r0_out,
	input(7 downto 4) => f,
	input(11 downto 8) => b,
	output => fu0_i2,
	mux_select => f0_MUX1_sel);

	fu1_i1 <= r1_out;

F1_MUX1 : entity work.c_multiplexer
	generic map
	(width => 4,
	no_of_inputs => 2,
	select_size => 1)
	port map
	(input(3 downto 0) => r0_out,
	input(7 downto 4) => h,
	output => fu1_i2,
	mux_select => f1_MUX1_sel);

F2_MUX0 : entity work.c_multiplexer
	generic map
	(width => 4,
	no_of_inputs => 2,
	select_size => 1)
	port map
	(input(3 downto 0) => r0_out,
	input(7 downto 4) => c,
	output => fu2_i1,
	mux_select => f2_MUX0_sel);

F2_MUX1 : entity work.c_multiplexer
	generic map
	(width => 4,
	no_of_inputs => 2,
	select_size => 1)
	port map
	(input(3 downto 0) => r1_out,
	input(7 downto 4) => d,
	output => fu2_i2,
	mux_select => f2_MUX1_sel);

-- Outputs
	i <= r0_out;
end toyexample_datapath_ar;
