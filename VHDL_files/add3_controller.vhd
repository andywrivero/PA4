library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use ieee.numeric_std.all;

entity add3_controller is
port
(
	r0_WR : out std_logic;
	r1_WR : out std_logic;
	f0_MUX0_sel : out std_logic_vector(0 downto 0);
	f0_MUX1_sel : out std_logic_vector(0 downto 0);
	start : in std_logic;
	done : out std_logic;
	clear : out std_logic;
	clock : in std_logic);
end add3_controller;

architecture add3_controller_ar of add3_controller is
--------------------------- State controller --------------------------------
	signal state : integer range 0 to 3 := 0;

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
					f0_MUX0_sel <= std_logic_vector(to_unsigned(1, 1));
					f0_MUX1_sel <= std_logic_vector(to_unsigned(1, 1));
					r0_WR <= '1';
					r1_WR <= '1';
					clear <= '0';
					state <= 2;

				when 2 =>
					r0_WR <= '1';
					r1_WR <= '0';
					f0_MUX0_sel <= std_logic_vector(to_unsigned(0, 1));
					f0_MUX1_sel <= std_logic_vector(to_unsigned(0, 1));
					state <= 3;

				when 3 =>
					r0_WR <= '0';
					done <= '1';
					state <= 0;

			end case;
		end if;
	end process;
end add3_controller_ar;
