library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use ieee.numeric_std.all;

entity add2_controller is
port
(
	r0_WR : out std_logic;
	start : in std_logic;
	done : out std_logic;
	clear : out std_logic;
	clock : in std_logic);
end add2_controller;

architecture add2_controller_ar of add2_controller is
--------------------------- State controller --------------------------------
	signal state : integer range 0 to 2 := 0;

begin
	process (clock)
	begin
		if rising_edge (clock) then
			case state is
				when 0 =>
					r0_WR <= '0';
					done <= '0';

					if start = '1' then
						clear <= '1';
						state <= 1;
					end if;

				when 1 =>
					r0_WR <= '1';
					clear <= '0';
					state <= 2;

				when 2 =>
					r0_WR <= '0';
					done <= '1';
					state <= 0;

			end case;
		end if;
	end process;
end add2_controller_ar;
