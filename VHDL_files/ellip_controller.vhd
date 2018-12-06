library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use ieee.numeric_std.all;

entity ellip_controller is
port
(
	r0_WR : out std_logic;
	r1_WR : out std_logic;
	r2_WR : out std_logic;
	r3_WR : out std_logic;
	r4_WR : out std_logic;
	r5_WR : out std_logic;
	r6_WR : out std_logic;
	r7_WR : out std_logic;
	r8_WR : out std_logic;
	r0_mux_sel : out std_logic_vector(1 downto 0);
	r1_mux_sel : out std_logic_vector(0 downto 0);
	r2_mux_sel : out std_logic_vector(1 downto 0);
	r3_mux_sel : out std_logic_vector(1 downto 0);
	r4_mux_sel : out std_logic_vector(1 downto 0);
	r5_mux_sel : out std_logic_vector(1 downto 0);
	r6_mux_sel : out std_logic_vector(1 downto 0);
	r7_mux_sel : out std_logic_vector(0 downto 0);
	r8_mux_sel : out std_logic_vector(0 downto 0);
	f0_MUX0_sel : out std_logic_vector(2 downto 0);
	f0_MUX1_sel : out std_logic_vector(3 downto 0);
	f1_MUX0_sel : out std_logic_vector(1 downto 0);
	f1_MUX1_sel : out std_logic_vector(2 downto 0);
	f2_MUX0_sel : out std_logic_vector(1 downto 0);
	f3_MUX0_sel : out std_logic_vector(0 downto 0);
	f3_MUX1_sel : out std_logic_vector(1 downto 0);
	f4_MUX0_sel : out std_logic_vector(1 downto 0);
	start : in std_logic;
	done : out std_logic;
	clear : out std_logic;
	clock : in std_logic);
end ellip_controller;

architecture ellip_controller_ar of ellip_controller is
--------------------------- State controller --------------------------------
	signal state : integer range 0 to 16 := 0;

begin
	process (clock)
	begin
		if rising_edge (clock) then
			case state is
				when 0 =>
					r0_WR <= '0';
					r1_WR <= '0';
					r2_WR <= '0';
					r3_WR <= '0';
					r4_WR <= '0';
					r5_WR <= '0';
					r6_WR <= '0';
					r7_WR <= '0';
					r8_WR <= '0';
					done <= '0';

					if start = '1' then
						clear <= '1';
						state <= 1;
					end if;

				when 1 =>
					f0_MUX0_sel <= std_logic_vector(to_unsigned(7, 3));
					f0_MUX1_sel <= std_logic_vector(to_unsigned(9, 4));
					r5_mux_sel <= std_logic_vector(to_unsigned(0, 2));
					r5_WR <= '1';
					clear <= '0';
					state <= 2;

				when 2 =>
					r5_WR <= '0';
					f0_MUX0_sel <= std_logic_vector(to_unsigned(6, 3));
					f0_MUX1_sel <= std_logic_vector(to_unsigned(6, 4));
					r1_mux_sel <= std_logic_vector(to_unsigned(0, 1));
					r1_WR <= '1';
					state <= 3;

				when 3 =>
					r1_WR <= '0';
					f0_MUX0_sel <= std_logic_vector(to_unsigned(3, 3));
					f0_MUX1_sel <= std_logic_vector(to_unsigned(8, 4));
					r2_mux_sel <= std_logic_vector(to_unsigned(0, 2));
					r2_WR <= '1';
					state <= 4;

				when 4 =>
					r2_WR <= '0';
					f0_MUX0_sel <= std_logic_vector(to_unsigned(1, 3));
					f0_MUX1_sel <= std_logic_vector(to_unsigned(7, 4));
					r0_mux_sel <= std_logic_vector(to_unsigned(0, 2));
					r0_WR <= '1';
					state <= 5;

				when 5 =>
					r0_WR <= '1';
					f0_MUX0_sel <= std_logic_vector(to_unsigned(0, 3));
					f0_MUX1_sel <= std_logic_vector(to_unsigned(1, 4));
					r0_mux_sel <= std_logic_vector(to_unsigned(0, 2));
					state <= 6;

				when 6 =>
					r0_WR <= '0';
					f2_MUX0_sel <= std_logic_vector(to_unsigned(0, 2));
					r4_mux_sel <= std_logic_vector(to_unsigned(2, 2));
					r4_WR <= '1';
					f4_MUX0_sel <= std_logic_vector(to_unsigned(0, 2));
					r3_mux_sel <= std_logic_vector(to_unsigned(1, 2));
					r3_WR <= '1';
					state <= 7;

				when 7 =>
					r4_WR <= '1';
					r3_WR <= '0';
					f0_MUX0_sel <= std_logic_vector(to_unsigned(1, 3));
					f0_MUX1_sel <= std_logic_vector(to_unsigned(2, 4));
					r4_mux_sel <= std_logic_vector(to_unsigned(0, 2));
					f1_MUX0_sel <= std_logic_vector(to_unsigned(1, 2));
					f1_MUX1_sel <= std_logic_vector(to_unsigned(0, 3));
					r6_mux_sel <= std_logic_vector(to_unsigned(1, 2));
					r6_WR <= '1';
					state <= 8;

				when 8 =>
					r4_WR <= '0';
					r6_WR <= '0';
					f0_MUX0_sel <= std_logic_vector(to_unsigned(1, 3));
					f0_MUX1_sel <= std_logic_vector(to_unsigned(2, 4));
					r1_mux_sel <= std_logic_vector(to_unsigned(0, 1));
					r1_WR <= '1';
					f1_MUX0_sel <= std_logic_vector(to_unsigned(2, 2));
					f1_MUX1_sel <= std_logic_vector(to_unsigned(0, 3));
					r2_mux_sel <= std_logic_vector(to_unsigned(1, 2));
					r2_WR <= '1';
					state <= 9;

				when 9 =>
					r1_WR <= '1';
					r2_WR <= '1';
					f0_MUX0_sel <= std_logic_vector(to_unsigned(2, 3));
					f0_MUX1_sel <= std_logic_vector(to_unsigned(0, 4));
					r2_mux_sel <= std_logic_vector(to_unsigned(0, 2));
					f2_MUX0_sel <= std_logic_vector(to_unsigned(1, 2));
					r0_mux_sel <= std_logic_vector(to_unsigned(1, 2));
					r0_WR <= '1';
					f4_MUX0_sel <= std_logic_vector(to_unsigned(1, 2));
					r1_mux_sel <= std_logic_vector(to_unsigned(1, 1));
					state <= 10;

				when 10 =>
					r2_WR <= '0';
					r0_WR <= '1';
					r1_WR <= '0';
					f0_MUX0_sel <= std_logic_vector(to_unsigned(3, 3));
					f0_MUX1_sel <= std_logic_vector(to_unsigned(0, 4));
					r0_mux_sel <= std_logic_vector(to_unsigned(0, 2));
					f1_MUX0_sel <= std_logic_vector(to_unsigned(0, 2));
					f1_MUX1_sel <= std_logic_vector(to_unsigned(4, 3));
					r3_mux_sel <= std_logic_vector(to_unsigned(0, 2));
					r3_WR <= '1';
					state <= 11;

				when 11 =>
					r0_WR <= '0';
					r3_WR <= '0';
					f0_MUX0_sel <= std_logic_vector(to_unsigned(0, 3));
					f0_MUX1_sel <= std_logic_vector(to_unsigned(2, 4));
					r1_mux_sel <= std_logic_vector(to_unsigned(0, 1));
					r1_WR <= '1';
					f1_MUX0_sel <= std_logic_vector(to_unsigned(2, 2));
					f1_MUX1_sel <= std_logic_vector(to_unsigned(1, 3));
					r4_mux_sel <= std_logic_vector(to_unsigned(1, 2));
					r4_WR <= '1';
					state <= 12;

				when 12 =>
					r1_WR <= '1';
					r4_WR <= '1';
					f0_MUX0_sel <= std_logic_vector(to_unsigned(3, 3));
					f0_MUX1_sel <= std_logic_vector(to_unsigned(0, 4));
					r1_mux_sel <= std_logic_vector(to_unsigned(0, 1));
					f1_MUX0_sel <= std_logic_vector(to_unsigned(0, 2));
					f1_MUX1_sel <= std_logic_vector(to_unsigned(5, 3));
					r4_mux_sel <= std_logic_vector(to_unsigned(1, 2));
					f3_MUX0_sel <= std_logic_vector(to_unsigned(1, 1));
					f3_MUX1_sel <= std_logic_vector(to_unsigned(1, 2));
					r5_mux_sel <= std_logic_vector(to_unsigned(2, 2));
					r5_WR <= '1';
					state <= 13;

				when 13 =>
					r1_WR <= '1';
					r4_WR <= '0';
					r5_WR <= '0';
					f0_MUX0_sel <= std_logic_vector(to_unsigned(1, 3));
					f0_MUX1_sel <= std_logic_vector(to_unsigned(4, 4));
					r1_mux_sel <= std_logic_vector(to_unsigned(0, 1));
					f1_MUX0_sel <= std_logic_vector(to_unsigned(1, 2));
					f1_MUX1_sel <= std_logic_vector(to_unsigned(4, 3));
					r2_mux_sel <= std_logic_vector(to_unsigned(1, 2));
					r2_WR <= '1';
					f2_MUX0_sel <= std_logic_vector(to_unsigned(1, 2));
					r6_mux_sel <= std_logic_vector(to_unsigned(2, 2));
					r6_WR <= '1';
					f4_MUX0_sel <= std_logic_vector(to_unsigned(2, 2));
					r8_mux_sel <= std_logic_vector(to_unsigned(1, 1));
					r8_WR <= '1';
					r7_mux_sel <= std_logic_vector(to_unsigned(1, 1));
					r7_WR <= '1';
					state <= 14;

				when 14 =>
					r1_WR <= '0';
					r2_WR <= '1';
					r6_WR <= '1';
					r8_WR <= '1';
					r7_WR <= '1';
					f0_MUX0_sel <= std_logic_vector(to_unsigned(5, 3));
					f0_MUX1_sel <= std_logic_vector(to_unsigned(5, 4));
					r6_mux_sel <= std_logic_vector(to_unsigned(0, 2));
					f1_MUX0_sel <= std_logic_vector(to_unsigned(3, 2));
					f1_MUX1_sel <= std_logic_vector(to_unsigned(2, 3));
					r8_mux_sel <= std_logic_vector(to_unsigned(0, 1));
					f2_MUX0_sel <= std_logic_vector(to_unsigned(2, 2));
					r7_mux_sel <= std_logic_vector(to_unsigned(0, 1));
					f3_MUX0_sel <= std_logic_vector(to_unsigned(0, 1));
					f3_MUX1_sel <= std_logic_vector(to_unsigned(2, 2));
					r2_mux_sel <= std_logic_vector(to_unsigned(2, 2));
					state <= 15;

				when 15 =>
					r6_WR <= '0';
					r8_WR <= '0';
					r7_WR <= '0';
					r2_WR <= '0';
					f0_MUX0_sel <= std_logic_vector(to_unsigned(4, 3));
					f0_MUX1_sel <= std_logic_vector(to_unsigned(3, 4));
					r4_mux_sel <= std_logic_vector(to_unsigned(0, 2));
					r4_WR <= '1';
					f1_MUX0_sel <= std_logic_vector(to_unsigned(1, 2));
					f1_MUX1_sel <= std_logic_vector(to_unsigned(3, 3));
					r5_mux_sel <= std_logic_vector(to_unsigned(1, 2));
					r5_WR <= '1';
					f3_MUX0_sel <= std_logic_vector(to_unsigned(0, 1));
					f3_MUX1_sel <= std_logic_vector(to_unsigned(0, 2));
					r0_mux_sel <= std_logic_vector(to_unsigned(2, 2));
					r0_WR <= '1';
					r3_mux_sel <= std_logic_vector(to_unsigned(2, 2));
					r3_WR <= '1';
					state <= 16;

				when 16 =>
					r4_WR <= '0';
					r5_WR <= '0';
					r0_WR <= '0';
					r3_WR <= '0';
					done <= '1';
					state <= 0;

			end case;
		end if;
	end process;
end ellip_controller_ar;
