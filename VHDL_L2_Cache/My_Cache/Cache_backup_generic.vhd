--Name: Derrick Ho
-- class: cs161L
--=================
--Generic_cache
-------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_unsigned.all;
use IEEE.STD_LOGIC_arith.all;
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
entity Generic_cache is
	generic (memsSize: integer := 65536; --64KB is 65536 bytes
			blockSize: integer := 128;-- constant 128Bytes 
			associativity: integer:= 1; -- 1 means DirectMap; 32 means full associative
			numofsets: integer := 512;  -- defined above or as a short cut 2^width
			width : integer := 9; -- should be set as log2(numofsets) ceiling
			tagsize: integer := 16); -- should be (32 - width - 7)
	port ( clk, rst, valid_in: in std_logic;
		address : in std_logic_vector(31 downto 0 );
		ack ,hit ,valid_out : out std_logic);
end generic_cache;

architecture Beh of Generic_cache is
	component generic_decoder
		generic (width : integer := 1);
		port ( input : in std_logic_vector( width downto 0);
		 output: out std_logic_vector( (2**width)-1 downto 0));
	end component;
	component generic_mux 
		generic (width : integer := 4);
		port ( input : in std_logic_vector ( (2**width)-1 downto 0);
			sel : in std_logic_vector (width downto 0);
			output: out std_logic);
	end component;
	component SET is
		Generic( tagSize: integer:= 8 ;
			associativity: integer:= 1); --direct map with 1 line by default
		port (clk, rst, enable : in STD_logic;
		control_update : in std_logic;
		address_tag: in std_logic_vector (tagSize -1 downto 0); 
		HIT_out: out std_logic
		);
	end component;
	component control is
     Port ( clk, rst, ENABLE: in STD_LOGIC;	
		VALID_IN : in  STD_LOGIC;
           HIT_IN : in  STD_LOGIC;
           ACK_OUT, UPDATE_OUT , VALID_OUT, EN_addr_buff: out  STD_LOGIC);
	end component;
	-- address_reg saves the incoming address
	signal address_reg,temp_address: std_logic_vector(31 downto 0) := (others => '0');
	signal index_s : std_logic_vector(width downto 0):=(others => '0'); -- holds index portion of address_reg
	signal tagline_s:std_logic_vector(31-width-7 downto 0):=(others => '0'); -- holds tag portion of address_reg
	signal EN_addr_buff_s, update_out_s, hit_in_s:   STD_LOGIC;
	signal decoder_s, mux_s: std_logic_vector( (2**width)-1 downto 0);
	-- what is boff_left? answer below
	--|tag |index | byte offset|
	--| 31  : boff_left + width_i +1 |  boff_left + width_i:boff_left+1| boff_left:0|
	-- e.g. 128 byte blocks and 4 sets
	---- 2^7 = 128 therefore byte offset is 7 bits long
	---- 2^2 = 4 therefore index needs 2 bits
	----  thus |31:9|8:7|6:0|
	constant Boff_left : integer := 6;
begin
-----------------------------------
--totalNumOfCacheLines <= memsSize / blocksize;
--numOfSets <= totalNumOfCacheLines / associativity;
-----------------------------------
--	log2_ceiling : process ( numofsets)
--		variable n, count: std_logic_vector(31 downto 0):= (others => '0');
--	begin
--		n := conv_std_logic_vector(numofsets,32);
--		n := n -1; count:= (others => '0');
--		while (conv_integer(n) > 0) loop
--			n := '0' & n(n'left downto 1);
--			count := count + 1;
--		end loop;
--		width_i <= conv_integer(count);
--	end process;
-----------------------------------
	mux_comp: generic_mux generic map (width => width)
		port map ( input => mux_s , sel => index_s, --The input to decoder is that same as select line for mux
				output => hit_in_s);
-----------------------------------
hit <= hit_in_s;
-----------------------------------
tagline_s <= address_reg(31 downto boff_left + width +1);
Gen_Set:
   for I in 0 to numOfsets-1 generate
      
		Set_Comp: SET 
			generic map( tagSize => tagsize, associativity=>associativity)
			port map(
				clk => clk, 
				rst => rst, 
				enable => decoder_s(I),
				control_update => update_out_s,
				address_tag => tagline_s, 
				HIT_out => mux_s(I)
			);
         
   end generate;
-----------------------------------
	index_s <= '0'&(address_reg (boff_left + width downto boff_left +1));
	decoder_comp: generic_decoder generic map (width => width)
		port map (input => index_s, output => decoder_s);
-----------------------------------
	control_comp : control Port map( 
		clk => clk, rst => rst, ENABLE => '1',	
		VALID_IN => valid_in,HIT_IN => hit_in_s,ACK_OUT => ack,
		 UPDATE_OUT => update_out_s, VALID_OUT => valid_out, 
		 EN_addr_buff => en_addr_buff_s);
-----------------------------------
	Addres_reg: process(clk, rst, en_addr_buff_s, address, temp_address)
	begin
		if(rst = '1') then
			temp_address <= (others => '0');
		elsif( clk'event and clk = '1') then
			if(rst = '0' AND en_addr_buff_s ='1') then
				temp_address <= address;
			end if;
		end if;
		address_reg <= temp_address;
	end process;
	
	
end beh;
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
	
entity SET is
	Generic( tagSize: integer:= 8 ;
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
				if(dec_index = conv_std_logic_vector(0,associativity)) then
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

--=================
--Generic Decoder
-------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_unsigned.all;
use IEEE.STD_LOGIC_arith.all;
-- width is how many bits it will be expecting in the  as input
-- the number of output lines the decoder will have is 2^width
-- if the width is 2 then 2^2 is 4 so there will be 4 output lines.
-- But to make it more portable a std_logic_vector will hold
-- the result
-- however, we have to accommodate a 1 to 1 decoder so the input
-- must be one bit larger. keep the MSB free to be used for the 1 to 1
-- situation.  If it is not a 1 to 1 situation then use all the bits except for
-- the MSB.
-- for the 1 to 1 situation to happen, set width to zero
-- ALSo... MAKE sure the signal comping into INPUT
-- has the bits you want and the '0' bit concatenated to the front
-- e.g  input <= x"beef"  -- desired input
-- e.g. input <= '0' & x"beef" -- correct concatenation
entity generic_decoder is
	generic (width : integer := 1);
	port ( input : in std_logic_vector( width  downto 0);
		 output: out std_logic_vector( (2**width)-1 downto 0));
end generic_decoder;

architecture structure of generic_decoder is
	signal output_s: std_logic_vector((2**width)-1 downto 0) ;
	constant all_low : std_logic_vector ((2**width)-2 downto 0) := (others => '0');
begin
	output_s <= (all_low&'1');

			-- First condition happens when it is fully associative
			-- and there is only one set.

output <=(others =>'1') when (width = 0) else to_stdlogicvector(to_bitvector(output_s) sll conv_integer(input(width-1 downto 0)));

end structure;

--=================
--Generic 1 bit mux
-------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_unsigned.all;
use IEEE.STD_LOGIC_arith.all;
-- outputs a 1 bit value 
-- since all inputs are 1 bit then it is a
-- fifty fifty chance and output is either a
-- 1 or a zero
-- there is an internal decoder. the select line of 
--this entity connects to the input of the decoder
-- the output of the decoder will be a power of two
-- meaning it will have only one '1' and the others are zero.
-- the input of mux are bitwise ANDed with the output of the decoder
-- if the '1' of the decoder aligns with a '1' of the muxes input it will 
--develop a number greater then 0.  Otherwise it will end up being zero
-- e.g. "1010" AND "0010" = "0010" which is 2 and that is greater than 0 
-- e.g. "1010" AND "0100" = "0000" which is 0
-- if the result is zero then the mux outputs a '0'
-- otherwise it outputs a '1';
--
-- sel input wil have one extra bit to accomodate a 1 to 1 mux
-- the extra bit is the MSB and is unused when it isn't a 1 to 1 mux
-- ALSo... MAKE sure the signal comping into SEL
-- has the bits you want and the '0' bit concatenated to the front
-- e.g  sel <= x"beef"  -- desired input
-- e.g. sel <= '0' & x"beef" -- correct concatenation
entity generic_mux is
	generic (width : integer := 4);
	port ( input : in std_logic_vector ( (2**width)-1 downto 0);
		sel : in std_logic_vector (width downto 0);
		output: out std_logic);
end generic_mux;

architecture struct of generic_mux is
	component generic_decoder
		generic (width : integer := 1);
		port ( input : in std_logic_vector( width downto 0);
		 output: out std_logic_vector( (2**width)-1 downto 0));
	end component;
	signal reg , andreg: std_logic_vector ((2**width)-1 downto 0);
	--signal sel_temp : std_logic_vector( width downto 0);
begin

		
		gen_dec : generic_decoder generic map (width)
			port map (input => sel(width downto 0), output => reg);
		
	
	andreg <= (reg AND input);
	output <= '1' when ( andreg> conv_std_logic_vector(0, 2**width)) else '0';
end struct;