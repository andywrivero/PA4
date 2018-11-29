library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use ieee.numeric_std.all;

entity toyexample_controller is
port
(
	r0_WR : out std_logic;
	r1_WR : out std_logic;
	r0_mux_sel : out std_logic_vector(0 downto 0);
	r1_mux_sel : out std_logic_vector(0 downto 0);
	f0_MUX0_sel : out std_logic_vector(1 downto 0);
	f0_MUX1_sel : out std_logic_vector(1 downto 0);
	f1_MUX1_sel : out std_logic_vector(0 downto 0);
	f2_MUX0_sel : out std_logic_vector(0 downto 0);
	f2_MUX1_sel : out std_logic_vector(0 downto 0);
	start : in std_logic;
	done : out std_logic;
	clear : out std_logic;
	clock : in std_logic);
end toyexample_controller;

architecture toyexample_controller_ar of toyexample_controller is
--------------------------- State controller --------------------------------
	signal state : integer range 0 to 5 := 0;

begin
	process (clock)
	begin
		if rising_edge (clock) then
			case state is
				when 0 =>
					r0_WR <= '0';
					r1_WR <= '0';
					done <= '0';

					if start = '1' then
						clear <= '1';
						state <= 1;
					end if;

				when 1 =>
					f0_MUX0_sel <= std_logic_vector(to_unsigned(2, 2));
					f0_MUX1_sel <= std_logic_vector(to_unsigned(2, 2));
					r0_mux_sel <= std_logic_vector(to_unsigned(0, 1));
					r0_WR <= '1';
					f2_MUX0_sel <= std_logic_vector(to_unsigned(1, 1));
					f2_MUX1_sel <= std_logic_vector(to_unsigned(1, 1));
					r1_mux_sel <= std_logic_vector(to_unsigned(1, 1));
					r1_WR <= '1';
					clear <= '0';
					state <= 2;

				when 2 =>
					r0_WR <= '1';
					r1_WR <= '1';
					f0_MUX0_sel <= std_logic_vector(to_unsigned(1, 2));
					f0_MUX1_sel <= std_logic_vector(to_unsigned(1, 2));
					r0_mux_sel <= std_logic_vector(to_unsigned(0, 1));
					f2_MUX0_sel <= std_logic_vector(to_unsigned(0, 1));
					f2_MUX1_sel <= std_logic_vector(to_unsigned(0, 1));
					r1_mux_sel <= std_logic_vector(to_unsigned(1, 1));
					state <= 3;

				when 3 =>
					r0_WR <= '1';
					r1_WR <= '1';
					f0_MUX0_sel <= std_logic_vector(to_unsigned(0, 2));
					f0_MUX1_sel <= std_logic_vector(to_unsigned(0, 2));
					r0_mux_sel <= std_logic_vector(to_unsigned(0, 1));
					f1_MUX1_sel <= std_logic_vector(to_unsigned(1, 1));
					r1_mux_sel <= std_logic_vector(to_unsigned(0, 1));
					state <= 4;

				when 4 =>
					r0_WR <= '1';
					r1_WR <= '0';
					f1_MUX1_sel <= std_logic_vector(to_unsigned(0, 1));
					r0_mux_sel <= std_logic_vector(to_unsigned(1, 1));
					state <= 5;

				when 5 =>
					r0_WR <= '0';
					done <= '1';
					state <= 0;

			end case;
		end if;
	end process;
end toyexample_controller_ar;
