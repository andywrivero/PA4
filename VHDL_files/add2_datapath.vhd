library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use ieee.numeric_std.all;

entity add2_datapath is
port
(
	a : in std_logic_vector(3 downto 0);
	b : in std_logic_vector(3 downto 0);
	c : out std_logic_vector(3 downto 0);
	r0_WR : in std_logic;
	clear : in std_logic;
	clock : in std_logic);
end add2_datapath;

architecture add2_datapath_ar of add2_datapath is
-- registers units signals
	signal r0_in : std_logic_vector(3 downto 0);
	signal r0_out : std_logic_vector(3 downto 0);
-- functional units signals
	signal fu0_i1 : std_logic_vector(3 downto 0);
	signal fu0_i2 : std_logic_vector(3 downto 0);
	signal fu0_out : std_logic_vector(3 downto 0);

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

-- Functional units
FU0 : entity work.c_adder
	generic map
	(width => 4)
	port map
	(input1 => fu0_i1,
	input2 => fu0_i2,
	output => fu0_out);

-- MUX for registers
	r0_in <= fu0_out;

-- MUX for functional units
	fu0_i1 <= a;

	fu0_i2 <= b;

-- Outputs
	c <= r0_out;
end add2_datapath_ar;
