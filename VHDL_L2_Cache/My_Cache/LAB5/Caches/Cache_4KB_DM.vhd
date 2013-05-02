----------------------------------------------------------------------------------
-- Gilberto g.
--
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity my_cache is
port(
	rst, clk : in std_logic;
	VALID_IN : in std_logic;
	ADDRESS : in std_logic_vector(31 downto 0);
	ACK : out std_logic;
	VALID_OUT : out std_logic;
	HIT : out std_logic
);
end my_cache;

architecture Behavioral of my_cache is

component control 
	Port ( 
		clk, rst, ENABLE: in STD_LOGIC;	
		VALID_IN : in  STD_LOGIC;
      HIT_IN : in  STD_LOGIC;
      ACK_OUT, UPDATE_OUT , VALID_OUT, EN_addr_buff: out STD_LOGIC
	);
end component;

component SET
	Generic( tagSize: integer:= 8 ;
			   associativity: integer:= 1 --direct map with 1 line by default
			  ); 
	port (clk, rst, enable : in STD_logic;
			control_update : in std_logic;
			address_tag: in std_logic_vector (tagSize -1 downto 0); 
			HIT_out: out std_logic
		   );
end component;

component decoder5
	port(
		Sel : in std_logic_vector( 4 downto 0 );
		y : out std_logic_vector( 31 downto 0 )
	);
end component;

component mux32v1
	port(
	d0: in std_logic;
	d1: in std_logic;
	d2: in std_logic;
	d3: in std_logic;
	d4: in std_logic;
	d5: in std_logic;
	d6: in std_logic;
	d7: in std_logic;
	d8: in std_logic;
	d9: in std_logic;
	d10: in std_logic;
	d11: in std_logic;
	d12: in std_logic;
	d13: in std_logic;
	d14: in std_logic;
	d15: in std_logic;
	d16: in std_logic;
	d17: in std_logic;
	d18: in std_logic;
	d19: in std_logic;
	d20: in std_logic;
	d21: in std_logic;
	d22: in std_logic;
	d23: in std_logic;
	d24: in std_logic;
	d25: in std_logic;
	d26: in std_logic;
	d27: in std_logic;
	d28: in std_logic;
	d29: in std_logic;
	d30: in std_logic;
	d31: in std_logic;
	y : out std_logic;
	s : in std_logic_vector( 4 downto 0 )
);
end component;

component Address_buff
generic(addr_size : integer := 8 );
port(
	clk, enable, rst: in std_logic;
	address_in : in std_logic_vector(addr_size-1 downto 0);
	address_out : out std_logic_vector(addr_size-1 downto 0)
);
end component;

--decoder out
signal decoder_out : std_logic_vector(31 downto 0);
--combined hit status of all the sets
signal hit_status : std_logic_vector(31 downto 0);
--signal mux out, goes back to the control unit and output port of the cache
signal mux_out : std_logic;
--control signal that enables the set update 
signal control_to_set : std_logic;
--signal from control to address buffer
signal addr_buff : std_logic;
--signal from control to valid out
signal valid_bit : std_logic;
--signal addr_buff to decoder
signal addr_temp : std_logic_vector(31 downto 0);

begin

Control_Unit : control 
	port map(
		clk => clk, 
		rst => rst, 
		ENABLE => '1',	
		VALID_IN => VALID_IN ,
		HIT_IN => mux_out, --output from the mux, represents the hit or miss
		ACK_OUT => ACK,
		UPDATE_OUT => control_to_set,
		VALID_OUT => valid_bit,
		EN_addr_buff => addr_buff 
	);

Decoder : decoder5
	port map(
		Sel =>addr_temp( 11 downto 7 ),
		y => decoder_out
	);

mux: mux32v1
	port map(
	d0=> hit_status(0),
	d1=> hit_status(1),
	d2=> hit_status(2),
	d3=> hit_status(3),
	d4=> hit_status(4),
	d5=> hit_status(5),
	d6=> hit_status(6),
	d7=> hit_status(7),
	d8=> hit_status(8),
	d9=> hit_status(9),
	d10=> hit_status(10),
	d11=> hit_status(11),
	d12=> hit_status(12),
	d13=> hit_status(13),
	d14=> hit_status(14),
	d15=> hit_status(15),
	d16=> hit_status(16),
	d17=> hit_status(17),
	d18=> hit_status(18),
	d19=> hit_status(19),
	d20=> hit_status(20),
	d21=> hit_status(21),
	d22=> hit_status(22),
	d23=> hit_status(23),
	d24=> hit_status(24),
	d25=> hit_status(25),
	d26=> hit_status(26),
	d27=> hit_status(27),
	d28=> hit_status(28),
	d29=> hit_status(29),
	d30=> hit_status(30),
	d31=> hit_status(31),
	y => mux_out,
	s => addr_temp(11 downto 7)
	);


Set_Array:
   for I in 0 to 31 generate
      
		Set_Component: SET 
			--for a 4kb, direct map 
			--setmemsize = 4096, blocksize = 128, associativity = 1
			generic map( tagSize => 20, associativity=>1 )
			port map(
				clk => clk, 
				rst => rst, 
				enable => decoder_out(I),
				control_update => control_to_set ,
				address_tag => addr_temp(31 downto 12), 
				HIT_out => hit_status(I)
			);
         
   end generate;

Address_Buffer : Address_buff
		generic map(addr_size => 32)
		port map(
			clk => clk, 
			enable => addr_buff,
			rst => rst,		
			address_in => ADDRESS,
			address_out => addr_temp
		);

HIT <= mux_out;
VALID_OUT <= valid_bit;			

end Behavioral;

----------------------------------------------------------
----------------------------------------------------------
----------------------------------------------------------
--==================
--CONTROL ENTITY
---------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_unsigned.all;
use IEEE.STD_LOGIC_arith.all;

entity control is
    Port ( 
		clk, rst, ENABLE: in STD_LOGIC;	
		VALID_IN : in  STD_LOGIC;
           HIT_IN : in  STD_LOGIC;
           ACK_OUT, UPDATE_OUT , VALID_OUT, EN_addr_buff: out  STD_LOGIC);
end control;

architecture Behavioral of control is
	type State is (INIT, MATCH, UPDATE);
	signal currentstate, nextstate: State:= INIT;
	signal currentACK,nextACK: std_logic;
begin
	-- value of ACK_out is determined in the output process
	ACK_OUT <= currentACK;
	
	--update_out conects to an external component called a SET
	--it tells the set to update the value it has in the Tag
	update_out <= '1' when (currentstate = UPDATE) else '0';

	VALID_OUT <= '1' when (currentstate = MATCH) else '0';

	--en_addr_buff is high when it is ready to recieve a new address to play with
	--once the external component is satisfied with the value it has given the address_reg
	--it will make valid_in high and the address_reg will be write enabled.
	EN_addr_buff <= '1' when (currentstate = INIT AND VALID_in = '1') else '0';

	SYNC_DATA: process(clk, rst, ENABLE)
	begin
		if(clk'event AND clk = '1') then
			if(rst = '1' AND (ENABLE = '1' OR ENABLE = '0')) then
			--rst makes state go to INIT and ACK become 0
				currentstate <= INIT; currentACK <= '0';
			elsif(rst= '0' AND enable = '1') then
				currentstate <= nextstate;
				currentACK <= nextACK;
			-- else it doesn't change signals
			end if;
		end if;
	end process;

	TRANS_proc: process(CURRENTSTATE, VALID_IN, HIT_IN)
	begin
		CASE currentstate is
			when INIT=> 
				if( VALID_IN ='1') then 
					nextstate <= match; 
				else 
					nextstate <= INIT; 
				end if;
			when match=> 
				if( HIT_IN ='1') then 
					nextstate <= INIT; 
				else 
				nextstate <= UPDATE; 
				end if;
			when update=> nextstate <= INIT;
			when others=> nextstate <= INIT;
		end case;
	end process;

	OUTPUT_proc: process(CURRENTSTATE)
	begin
		CASE currentstate is
			when INIT=> nextack <= '0';
			when match=> nextack <= '1';
			when update=> nextack <= '0';
			when others=> nextack <= '0';
		end case;
	end process;

end Behavioral;

--===============
--SET entity
-----------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_unsigned.all;
use IEEE.STD_LOGIC_arith.all;

	--associativity indicate the numer of lines a set has
	----if it is a direct map then it has one line
	----if it is 2 way assiciative then it has 2 lines
	----if it is nway associative then it has N lines
	--
	--tagSize is the generic that indicates how many bits 
	----are in the tag of the address.  In the higher level entity
	----the tag size is set and the tag bits of the above entity's
	---- address is used as input for the current level entity AKA SET entity
	--
	--blockSize is the block size given by the high level entity
	--
	--totalNumOfCacheLines = memsize / block size
	--e.g. memsize is 4KB and block size is 128BYTES
	---- then 4096 divide by 128 bytes is 32 cache lines.
	--
	--numOfSets = totalNumOfCacheLines / associativity
	----e.g.  4 way associativity is (32 cache lines)/ 4 equals 8 sets
	----e.g.  fully associative is (32 cache lines) / 32 equals 1
	----e.g. direct map is (32 cache lines) /1 equals 32 sets
entity SET is
	Generic( memsSize: integer := 4096; --4KB is 4069 bytes
			blockSize: integer := 128; -- constant 128Bytes 
			tagSize: integer:= 8 ;
			associativity: integer:= 1); --direct map with 1 line by default
	port (clk, rst, enable : in STD_logic;
		control_update : in std_logic;
		address_tag: in std_logic_vector (tagSize -1 downto 0); 
		HIT_out: out std_logic
		);
end set;

architecture Behavior of SET is
	component tagLine
		generic(tagSize : integer := 8);
		port ( clk, enable, rst: in std_logic;
		newTag : in std_logic_vector(tagSize -1 downto 0);
		word : in std_logic_vector(tagSize -1 downto 0);
		match: out std_logic);
	end component;
	--signals
	--control process toggles enable of tagline
	---- when it is enabled it the word will overwrite the current
	---- tag value.  This should only happen when the control wants
	---- it to happen
		signal controlen: std_logic_vector(associativity-1 downto 0):= (others => '0');
		signal match_s: std_logic_vector (associativity -1 downto 0);
		constant all_low : std_logic_vector( associativity -1 downto 0) := (others => '0');
begin
	
	tagline_array : for I in 0 to (associativity-1) generate
		comp_tag:tagLine generic map(tagSize => tagSize)
			port map ( clk => clk, enable => controlen(I), rst=> rst,
			newTag => address_tag,
			word => address_tag,
			match => match_s(I) );
	end generate;
	hit_out <= '0' when match_s = all_low else '1';
	
	replacement_policy : process (clk, rst, enable, control_update)
		variable dec_index: std_logic_vector(associativity-1 downto 0) := (others => '0');
	begin
		if(rst = '1') then
			controlen <= (others => '0');
			dec_index := (others => '0');
		elsif(clk'event AND clk = '1') then
			if( enable = '1' AND control_update = '1') then
				dec_index := dec_index + dec_index;
				if(conv_integer(dec_index) = 0) then
					dec_index(0) :='1';
				end if;
				controlen <= dec_index;
			else controlen <= (others => '0');
			end if;	
		end if;
	end process;
end behavior; 

--=================================
--tag line entity holds data of valid and tag
-----------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_unsigned.all;
use IEEE.STD_LOGIC_arith.all;
	--
	--This component is a register that holds the tag and valid bits
	--
entity tagLine is
	generic(tagSize : integer := 8);
	port ( clk, enable, rst: in std_logic;
		newTag : in std_logic_vector(tagSize -1 downto 0);
		word : in std_logic_vector(tagSize -1 downto 0);
		match: out std_logic
		);
end tagLine;
architecture beh of tagLine is
	-- tag reg uses left most bit to store valid bit data and
	--uses the rest to store the tag data that is why it is
	--one bit longer then newTag or Tag
	signal tag_reg: std_logic_vector( tagSize downto 0);
begin
	
	tag_proc: process(clk, enable, rst, newTag)
	begin
		if(clk'event AND clk = '0') then
			if(rst = '1' AND (ENABLE = '0' or ENABLE = '1')) then
				tag_reg <= (others => '0');
			elsif( rst = '0' AND ENABLE = '1') then
				tag_reg(tag_reg'left) <= '1';
				tag_reg(tag_reg'left-1 downto 0) <= newTag;
			end if;
		end if;
	end process;
	match <= '1' when '1'&word = tag_reg else '0';
end beh;
----------------------------------------------------------
----------------------------------------------------------
----------------------------------------------------------
library IEEE;
use IEEE.std_logic_1164.all;

entity decoder5 is
port(
	Sel : in std_logic_vector( 4 downto 0 );
	y : out std_logic_vector( 31 downto 0 )
	);
end entity decoder5;

architecture bhv of decoder5 is
begin
y <= "00000000000000000000000000000001" when Sel = "00000" else
     "00000000000000000000000000000010" when Sel = "00001" else
     "00000000000000000000000000000100" when Sel = "00010" else
     "00000000000000000000000000001000" when Sel = "00011" else
     "00000000000000000000000000010000" when Sel = "00100" else
     "00000000000000000000000000100000" when Sel = "00101" else
     "00000000000000000000000001000000" when Sel = "00110" else
     "00000000000000000000000010000000" when Sel = "00111" else
     "00000000000000000000000100000000" when Sel = "01000" else
     "00000000000000000000001000000000" when Sel = "01001" else
     "00000000000000000000010000000000" when Sel = "01010" else
     "00000000000000000000100000000000" when Sel = "01011" else
     "00000000000000000001000000000000" when Sel = "01100" else
     "00000000000000000010000000000000" when Sel = "01101" else
     "00000000000000000100000000000000" when Sel = "01110" else
     "00000000000000001000000000000000" when Sel = "01111" else
     "00000000000000010000000000000000" when Sel = "10000" else
     "00000000000000100000000000000000" when Sel = "10001" else
     "00000000000001000000000000000000" when Sel = "10010" else
     "00000000000010000000000000000000" when Sel = "10011" else
     "00000000000100000000000000000000" when Sel = "10100" else
     "00000000001000000000000000000000" when Sel = "10101" else
     "00000000010000000000000000000000" when Sel = "10110" else
     "00000000100000000000000000000000" when Sel = "10111" else
     "00000001000000000000000000000000" when Sel = "11000" else
     "00000010000000000000000000000000" when Sel = "11001" else
     "00000100000000000000000000000000" when Sel = "11010" else
     "00001000000000000000000000000000" when Sel = "11011" else
     "00010000000000000000000000000000" when Sel = "11100" else
     "00100000000000000000000000000000" when Sel = "11101" else
     "01000000000000000000000000000000" when Sel = "11110" else
     "10000000000000000000000000000000";
end architecture bhv;

----------------------------------------------------------
----------------------------------------------------------
----------------------------------------------------------

library IEEE;
use IEEE.std_logic_1164.all;

entity mux32v1 is
port(
	d0: in std_logic;
	d1: in std_logic;
	d2: in std_logic;
	d3: in std_logic;
	d4: in std_logic;
	d5: in std_logic;
	d6: in std_logic;
	d7: in std_logic;
	d8: in std_logic;
	d9: in std_logic;
	d10: in std_logic;
	d11: in std_logic;
	d12: in std_logic;
	d13: in std_logic;
	d14: in std_logic;
	d15: in std_logic;
	d16: in std_logic;
	d17: in std_logic;
	d18: in std_logic;
	d19: in std_logic;
	d20: in std_logic;
	d21: in std_logic;
	d22: in std_logic;
	d23: in std_logic;
	d24: in std_logic;
	d25: in std_logic;
	d26: in std_logic;
	d27: in std_logic;
	d28: in std_logic;
	d29: in std_logic;
	d30: in std_logic;
	d31: in std_logic;
	y : out std_logic;
	s : in std_logic_vector( 4 downto 0 )
);
end mux32v1;

architecture bhv of mux32v1 is
begin

with s select

y <=    d0 when "00000",
	d1 when "00001",
	d2 when "00010",
	d3 when "00011",
	d4 when "00100",
	d5 when "00101",
	d6 when "00110",
	d7 when "00111",
	d8 when "01000",
	d9 when "01001",
	d10 when "01010",
	d11 when "01011",
	d12 when "01100",
	d13 when "01101",
	d14 when "01110",
	d15 when "01111",
	d16 when "10000",
	d17 when "10001",
	d18 when "10010",
	d19 when "10011",
	d20 when "10100",
	d21 when "10101",
	d22 when "10110",
	d23 when "10111",
	d24 when "11000",
	d25 when "11001",
	d26 when "11010",
	d27 when "11011",
	d28 when "11100",
	d29 when "11101",
	d30 when "11110",
	d31 when "11111",
	'0' when others;

end bhv;

----------------------------------------------------------
----------------------------------------------------------
----------------------------------------------------------

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity Address_buff is
generic(addr_size : integer := 8 );
port(
	clk, enable, rst: in std_logic;
	address_in : in std_logic_vector(addr_size-1 downto 0);
	address_out : out std_logic_vector(addr_size-1 downto 0)
);
end Address_buff;

architecture Behavioral of Address_buff is

signal addr_buffer : std_logic_vector(addr_size-1 downto 0);

begin

	a_b : process(clk,enable,rst,address_in)
	begin
		if(clk'event AND clk = '0') then
			if(rst = '1' AND (ENABLE = '0' or ENABLE = '1')) then
				addr_buffer <= (others => '0');
			elsif( rst = '0' AND ENABLE = '1') then
				addr_buffer <= address_in;
			end if;
		end if;
	end process;
	
	address_out <= addr_buffer;

end Behavioral;