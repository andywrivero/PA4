library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use ieee.numeric_std.all;

entity ellip_datapath is
port
(
	inp : in std_logic_vector(3 downto 0);
	svin2 : in std_logic_vector(3 downto 0);
	svin13 : in std_logic_vector(3 downto 0);
	svin18 : in std_logic_vector(3 downto 0);
	svin26 : in std_logic_vector(3 downto 0);
	svin33 : in std_logic_vector(3 downto 0);
	svin38 : in std_logic_vector(3 downto 0);
	svin39 : in std_logic_vector(3 downto 0);
	TWO : in std_logic_vector(3 downto 0);
	svout2 : out std_logic_vector(3 downto 0);
	svout13 : out std_logic_vector(3 downto 0);
	svout18 : out std_logic_vector(3 downto 0);
	svout26 : out std_logic_vector(3 downto 0);
	svout33 : out std_logic_vector(3 downto 0);
	svout38 : out std_logic_vector(3 downto 0);
	svout39 : out std_logic_vector(3 downto 0);
	r0_WR : in std_logic;
	r1_WR : in std_logic;
	r2_WR : in std_logic;
	r3_WR : in std_logic;
	r4_WR : in std_logic;
	r5_WR : in std_logic;
	r6_WR : in std_logic;
	r7_WR : in std_logic;
	r8_WR : in std_logic;
	r0_mux_sel : in std_logic_vector(1 downto 0);
	r1_mux_sel : in std_logic_vector(0 downto 0);
	r2_mux_sel : in std_logic_vector(1 downto 0);
	r3_mux_sel : in std_logic_vector(1 downto 0);
	r4_mux_sel : in std_logic_vector(1 downto 0);
	r5_mux_sel : in std_logic_vector(1 downto 0);
	r6_mux_sel : in std_logic_vector(1 downto 0);
	r7_mux_sel : in std_logic_vector(0 downto 0);
	r8_mux_sel : in std_logic_vector(0 downto 0);
	f0_MUX0_sel : in std_logic_vector(2 downto 0);
	f0_MUX1_sel : in std_logic_vector(3 downto 0);
	f1_MUX0_sel : in std_logic_vector(1 downto 0);
	f1_MUX1_sel : in std_logic_vector(2 downto 0);
	f2_MUX0_sel : in std_logic_vector(1 downto 0);
	f3_MUX0_sel : in std_logic_vector(0 downto 0);
	f3_MUX1_sel : in std_logic_vector(1 downto 0);
	f4_MUX0_sel : in std_logic_vector(1 downto 0);
	clear : in std_logic;
	clock : in std_logic);
end ellip_datapath;

architecture ellip_datapath_ar of ellip_datapath is
-- registers units signals
	signal r0_in : std_logic_vector(3 downto 0);
	signal r0_out : std_logic_vector(3 downto 0);
	signal r1_in : std_logic_vector(3 downto 0);
	signal r1_out : std_logic_vector(3 downto 0);
	signal r2_in : std_logic_vector(3 downto 0);
	signal r2_out : std_logic_vector(3 downto 0);
	signal r3_in : std_logic_vector(3 downto 0);
	signal r3_out : std_logic_vector(3 downto 0);
	signal r4_in : std_logic_vector(3 downto 0);
	signal r4_out : std_logic_vector(3 downto 0);
	signal r5_in : std_logic_vector(3 downto 0);
	signal r5_out : std_logic_vector(3 downto 0);
	signal r6_in : std_logic_vector(3 downto 0);
	signal r6_out : std_logic_vector(3 downto 0);
	signal r7_in : std_logic_vector(3 downto 0);
	signal r7_out : std_logic_vector(3 downto 0);
	signal r8_in : std_logic_vector(3 downto 0);
	signal r8_out : std_logic_vector(3 downto 0);
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
	signal fu3_i1 : std_logic_vector(3 downto 0);
	signal fu3_i2 : std_logic_vector(3 downto 0);
	signal fu3_out : std_logic_vector(3 downto 0);
	signal fu4_i1 : std_logic_vector(3 downto 0);
	signal fu4_i2 : std_logic_vector(3 downto 0);
	signal fu4_out : std_logic_vector(3 downto 0);
	signal fu5_i1 : std_logic_vector(3 downto 0);
	signal fu5_i2 : std_logic_vector(3 downto 0);
	signal fu5_out : std_logic_vector(3 downto 0);
	signal fu6_i1 : std_logic_vector(3 downto 0);
	signal fu6_i2 : std_logic_vector(3 downto 0);
	signal fu6_out : std_logic_vector(3 downto 0);

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

R2 : entity work.c_register
	generic map
	(width => 4)
	port map
	(input => r2_in,
	output => r2_out,
	WR => r2_WR,
	clear => clear,
	clock => clock);

R3 : entity work.c_register
	generic map
	(width => 4)
	port map
	(input => r3_in,
	output => r3_out,
	WR => r3_WR,
	clear => clear,
	clock => clock);

R4 : entity work.c_register
	generic map
	(width => 4)
	port map
	(input => r4_in,
	output => r4_out,
	WR => r4_WR,
	clear => clear,
	clock => clock);

R5 : entity work.c_register
	generic map
	(width => 4)
	port map
	(input => r5_in,
	output => r5_out,
	WR => r5_WR,
	clear => clear,
	clock => clock);

R6 : entity work.c_register
	generic map
	(width => 4)
	port map
	(input => r6_in,
	output => r6_out,
	WR => r6_WR,
	clear => clear,
	clock => clock);

R7 : entity work.c_register
	generic map
	(width => 4)
	port map
	(input => r7_in,
	output => r7_out,
	WR => r7_WR,
	clear => clear,
	clock => clock);

R8 : entity work.c_register
	generic map
	(width => 4)
	port map
	(input => r8_in,
	output => r8_out,
	WR => r8_WR,
	clear => clear,
	clock => clock);

-- Functional units
FU0 : entity work.c_adder
	generic map
	(width => 4)
	port map
	(input1 => fu0_i1,
	input2 => fu0_i2,
	output => fu0_out);

FU1 : entity work.c_adder
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

FU3 : entity work.c_adder
	generic map
	(width => 4)
	port map
	(input1 => fu3_i1,
	input2 => fu3_i2,
	output => fu3_out);

FU4 : entity work.c_multiplier
	generic map
	(width => 4)
	port map
	(input1 => fu4_i1,
	input2 => fu4_i2,
	output => fu4_out);

FU5 : entity work.c_adder
	generic map
	(width => 4)
	port map
	(input1 => fu5_i1,
	input2 => fu5_i2,
	output => fu5_out);

FU6 : entity work.c_multiplier
	generic map
	(width => 4)
	port map
	(input1 => fu6_i1,
	input2 => fu6_i2,
	output => fu6_out);

-- MUX for registers
R0_MUX : entity work.c_multiplexer
	generic map
	(width => 4,
	no_of_inputs => 3,
	select_size => 2)
	port map
	(input(3 downto 0) => fu0_out,
	input(7 downto 4) => fu2_out,
	input(11 downto 8) => fu3_out,
	output => r0_in,
	mux_select => r0_mux_sel);

R1_MUX : entity work.c_multiplexer
	generic map
	(width => 4,
	no_of_inputs => 2,
	select_size => 1)
	port map
	(input(3 downto 0) => fu0_out,
	input(7 downto 4) => fu4_out,
	output => r1_in,
	mux_select => r1_mux_sel);

R2_MUX : entity work.c_multiplexer
	generic map
	(width => 4,
	no_of_inputs => 3,
	select_size => 2)
	port map
	(input(3 downto 0) => fu0_out,
	input(7 downto 4) => fu1_out,
	input(11 downto 8) => fu3_out,
	output => r2_in,
	mux_select => r2_mux_sel);

R3_MUX : entity work.c_multiplexer
	generic map
	(width => 4,
	no_of_inputs => 3,
	select_size => 2)
	port map
	(input(3 downto 0) => fu1_out,
	input(7 downto 4) => fu4_out,
	input(11 downto 8) => fu5_out,
	output => r3_in,
	mux_select => r3_mux_sel);

R4_MUX : entity work.c_multiplexer
	generic map
	(width => 4,
	no_of_inputs => 3,
	select_size => 2)
	port map
	(input(3 downto 0) => fu0_out,
	input(7 downto 4) => fu1_out,
	input(11 downto 8) => fu2_out,
	output => r4_in,
	mux_select => r4_mux_sel);

R5_MUX : entity work.c_multiplexer
	generic map
	(width => 4,
	no_of_inputs => 3,
	select_size => 2)
	port map
	(input(3 downto 0) => fu0_out,
	input(7 downto 4) => fu1_out,
	input(11 downto 8) => fu3_out,
	output => r5_in,
	mux_select => r5_mux_sel);

R6_MUX : entity work.c_multiplexer
	generic map
	(width => 4,
	no_of_inputs => 3,
	select_size => 2)
	port map
	(input(3 downto 0) => fu0_out,
	input(7 downto 4) => fu1_out,
	input(11 downto 8) => fu2_out,
	output => r6_in,
	mux_select => r6_mux_sel);

R7_MUX : entity work.c_multiplexer
	generic map
	(width => 4,
	no_of_inputs => 2,
	select_size => 1)
	port map
	(input(3 downto 0) => fu2_out,
	input(7 downto 4) => fu6_out,
	output => r7_in,
	mux_select => r7_mux_sel);

R8_MUX : entity work.c_multiplexer
	generic map
	(width => 4,
	no_of_inputs => 2,
	select_size => 1)
	port map
	(input(3 downto 0) => fu1_out,
	input(7 downto 4) => fu4_out,
	output => r8_in,
	mux_select => r8_mux_sel);

-- MUX for functional units
F0_MUX0 : entity work.c_multiplexer
	generic map
	(width => 4,
	no_of_inputs => 8,
	select_size => 3)
	port map
	(input(3 downto 0) => r0_out,
	input(7 downto 4) => r2_out,
	input(11 downto 8) => r4_out,
	input(15 downto 12) => r5_out,
	input(19 downto 16) => r6_out,
	input(23 downto 20) => svin38,
	input(27 downto 24) => svin33,
	input(31 downto 28) => inp,
	output => fu0_i1,
	mux_select => f0_MUX0_sel);

F0_MUX1 : entity work.c_multiplexer
	generic map
	(width => 4,
	no_of_inputs => 10,
	select_size => 4)
	port map
	(input(3 downto 0) => r0_out,
	input(7 downto 4) => r1_out,
	input(11 downto 8) => r4_out,
	input(15 downto 12) => r5_out,
	input(19 downto 16) => r6_out,
	input(23 downto 20) => r7_out,
	input(27 downto 24) => svin39,
	input(31 downto 28) => svin26,
	input(35 downto 32) => svin13,
	input(39 downto 36) => svin2,
	output => fu0_i2,
	mux_select => f0_MUX1_sel);

F1_MUX0 : entity work.c_multiplexer
	generic map
	(width => 4,
	no_of_inputs => 4,
	select_size => 2)
	port map
	(input(3 downto 0) => r1_out,
	input(7 downto 4) => r3_out,
	input(11 downto 8) => r6_out,
	input(15 downto 12) => inp,
	output => fu1_i1,
	mux_select => f1_MUX0_sel);

F1_MUX1 : entity work.c_multiplexer
	generic map
	(width => 4,
	no_of_inputs => 6,
	select_size => 3)
	port map
	(input(3 downto 0) => r1_out,
	input(7 downto 4) => r3_out,
	input(11 downto 8) => r6_out,
	input(15 downto 12) => r7_out,
	input(19 downto 16) => svin39,
	input(23 downto 20) => svin18,
	output => fu1_i2,
	mux_select => f1_MUX1_sel);

F2_MUX0 : entity work.c_multiplexer
	generic map
	(width => 4,
	no_of_inputs => 3,
	select_size => 2)
	port map
	(input(3 downto 0) => r0_out,
	input(7 downto 4) => r1_out,
	input(11 downto 8) => r2_out,
	output => fu2_i1,
	mux_select => f2_MUX0_sel);

	fu2_i2 <= TWO;

F3_MUX0 : entity work.c_multiplexer
	generic map
	(width => 4,
	no_of_inputs => 2,
	select_size => 1)
	port map
	(input(3 downto 0) => r8_out,
	input(7 downto 4) => svin38,
	output => fu3_i1,
	mux_select => f3_MUX0_sel);

F3_MUX1 : entity work.c_multiplexer
	generic map
	(width => 4,
	no_of_inputs => 3,
	select_size => 2)
	port map
	(input(3 downto 0) => r0_out,
	input(7 downto 4) => r4_out,
	input(11 downto 8) => svin18,
	output => fu3_i2,
	mux_select => f3_MUX1_sel);

F4_MUX0 : entity work.c_multiplexer
	generic map
	(width => 4,
	no_of_inputs => 3,
	select_size => 2)
	port map
	(input(3 downto 0) => r0_out,
	input(7 downto 4) => r2_out,
	input(11 downto 8) => r4_out,
	output => fu4_i1,
	mux_select => f4_MUX0_sel);

	fu4_i2 <= TWO;

	fu5_i1 <= r4_out;

	fu5_i2 <= r2_out;

	fu6_i1 <= r5_out;

	fu6_i2 <= TWO;

-- Outputs
	svout2 <= r0_out;
	svout26 <= r1_out;
	svout18 <= r2_out;
	svout13 <= r3_out;
	svout33 <= r4_out;
	svout39 <= r5_out;
	svout38 <= r6_out;
end ellip_datapath_ar;
