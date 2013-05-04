/*
 * A portion of the code that reads the data from the nodes and edges
 * was borrowed from Generator.cs
 * The rest of the code deals with converting the C syntax to VHDL and
 * all of that is original.
 * 
 * Name: Derrick Ho
 * login: dho006
 * email: dho006@ucr.edu
 * class: CS 179j 
 * Professor: Phillip Brisk.
 * 
 */

using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;

namespace RIBS_V2
{
	class GeneratorVHDL
	{
		private String output;
		private List<Graph> canvas;
		private bool enableTimer;
		private int bitWidth;
		private String entityName;
		private String global_variables;
		private String processName;
		private String fpgaClockRate;
		private HashSet<threePiece> threePieceSet;//used to organize local variables
		private int current_graph;
		private cStringInput_to_vhdlStringInput cvar2vhdlvar;
		private bool Error_MSG_flag;
        private bool WARNING_MSG_FLAG;
		private HashSet<string> unknownStrings= new HashSet<string>();//The lines of code that don't have supported code gets placed in here.  it gets printed in printhashsetwithformatting, then gets cleared.

		public GeneratorVHDL(List<Graph> canvas_, string entityName_, string global_variables_)
		{
			Error_MSG_flag = false;
			//set boolean for vhdl FSM or C FSM
			//   wantVHDL_FSM_toVHDL_code = 0;
			current_graph = 0;
			output = "";
			canvas = canvas_;
			enableTimer = false;
			entityName = removeWhiteSpace(entityName_);
			global_variables = global_variables_;
			processName = "";//gets the first occurance 
			bitWidth = 8;
			fpgaClockRate = "50000000";// default 50Mhz
			threePieceSet = new HashSet<threePiece>();

			//creating a new cStringInput_to_vhdlStringInput() object
			cvar2vhdlvar = new cStringInput_to_vhdlStringInput();
		}
		void setFpgaClockRate(string newClockRate)
		{
			fpgaClockRate = newClockRate;
		}
		string getFpgaClockRate()
		{
			return fpgaClockRate;
		}
		string getPeriod()
		{
			string tempstr = removeWhiteSpace(canvas[current_graph].GetPeriod());
			return tempstr;
		}
		public string GenerateVHDLcode(bool enabletimer_)
		{
			if (!AllFSMInputsValid())
			{ //varify that all input is valid else return an empty string
				//MessageBox.Show("Error: Please fix Input", "Error");
				return "";
			}
			enableTimer = enabletimer_;
			output += (printLib());
			output += (printEntity());
			//if (wantVHDL_FSM_toVHDL_code)
			//	output += (printArchVHDL());
			//else
			output += (printArch());
			//output += printPES_Clock_Entity();
			/*remove any brackets {} from string since VHDL doesn't use them*/
			output.Replace("{", "");
			output.Replace("}", "");

			return output;
		}
		private String printLib()
		{
			String tempStr = "";//declare an empty string
			/*hardcode string with commonly used libraries*/
            tempStr +="library IEEE;" + "\r\n"
                    + "use IEEE.STD_LOGIC_1164.ALL;" + "\r\n"
                    + "use IEEE.STD_LOGIC_ARITH.ALL;" + "\r\n"
                    + "use IEEE.STD_LOGIC_UNSIGNED.ALL;" + "\r\n"
                    + "package tools is" + "\r\n"
                    + "		--shape_i is the signal that is about to be converted to fit;" + "\r\n"
                    + "		--fit_i is the signal that shape_i will conform to" + "\r\n"
					+ "		--i.e. if shape is a std_logic_vector of 4 bits, it will get changed" + "\r\n"
					+ "		--to an integer and then converted into an std_logic vector of the same" + "\r\n"
					+ "		--size as fit." + "\r\n"
					+ "		function CSLV (shape_i: std_logic_vector; fit_i:std_logic_vector)return std_logic_vector is" + "\r\n"
					+ "			begin return conv_std_logic_vector(conv_integer(shape_i),fit_i'length);" + "\r\n"
					+ "		end function CSLV;" + "\r\n"
					+ "		function CSLV (shape_i: std_logic; fit_i:std_logic)return std_logic is" + "\r\n"
					+ "			begin return shape_i;" + "\r\n"
					+ "		end function CSLV;" + "\r\n"
					+ "		function CSLV (shape_i: std_logic; fit_i:std_logic_vector)return std_logic_vector is" + "\r\n"
					+ "			begin return conv_std_logic_vector(conv_integer(shape_i),fit_i'length);" + "\r\n"
					+ "		end function CSLV;" + "\r\n"
					+ "		function CSLV (shape_i: integer; fit_i:std_logic_vector)	return std_logic_vector is" + "\r\n"
					+ "			begin return conv_std_logic_vector((shape_i),fit_i'length);" + "\r\n"
					+ "		end function CSLV;" + "\r\n"
					+ "		function CSLV (shape_i: integer; fit_i:std_logic)return std_logic is" + "\r\n"
					+ "			begin" + "\r\n"
					+ "			if shape_i = 0 then return '0';" + "\r\n"
					+ "			else return '1';" + "\r\n"
					+ "			end if;" + "\r\n"
					+ "		end function CSLV;" + "\r\n"
					+ "		function CSLV (shape_i: std_logic_vector; fit_i:std_logic)return std_logic is" + "\r\n"
					+ "			begin" + "\r\n"
					+ "			if shape_i = CSLV(0,shape_i) then return '0';" + "\r\n"
					+ "			else	return '1';" + "\r\n"
					+ "			end if;" + "\r\n"
					+ "		end function CSLV;" + "\r\n"
					+ "		function \"not\" (s:integer) return std_logic_vector is" + "\r\n"
					+ "			begin return not ( conv_std_logic_vector(s,64));" + "\r\n"
					+ "		end;" + "\r\n"
					+ "		function \"=\" (s:integer;f:std_logic) return boolean is" + "\r\n"
					+ "			begin return CSLV(s,f) = f;" + "\r\n"
					+ "		end;" + "\r\n"
					+ "		function \"=\" (f:std_logic;s:integer) return boolean is" + "\r\n"
					+ "			begin return CSLV(s,f) = f;" + "\r\n"
					+ "		end;" + "\r\n"
					+ "		function \"=\" (s:integer;f:std_logic_vector) return boolean is" + "\r\n"
					+ "			begin return CSLV(s,f) = f;" + "\r\n"
					+ "		end;" + "\r\n"
					+ "		function \"=\" (f:std_logic_vector;s:integer) return boolean is" + "\r\n"
					+ "			begin return CSLV(s,f) = f;" + "\r\n"
					+ "		end;" + "\r\n"
					+ "		function \"=\" (s:std_logic;f:std_logic_vector) return boolean is" + "\r\n"
					+ "			begin return CSLV(s,f) = f;" + "\r\n"
					+ "		end;" + "\r\n"
					+ "		function \"=\" (f:std_logic_vector;s:std_logic) return boolean is" + "\r\n"
					+ "			begin return CSLV(s,f) = f;" + "\r\n"
					+ "		end;" + "\r\n"
					+ "		function \"/=\" (f:std_logic;s:integer) return boolean is" + "\r\n"
					+ "			begin return CSLV(s,f) /= f;" + "\r\n"
					+ "		end;" + "\r\n"
					+ "		function \"/=\" (s:integer;f:std_logic) return boolean is" + "\r\n"
					+ "			begin return CSLV(s,f) /= f;" + "\r\n"
					+ "		end;" + "\r\n"
					+ "		function \"/=\" (s:integer;f:std_logic_vector) return boolean is" + "\r\n"
					+ "			begin return CSLV(s,f) /= f;" + "\r\n"
					+ "		end;" + "\r\n"
					+ "		function \"/=\" (f:std_logic_vector;s:integer) return boolean is" + "\r\n"
					+ "			begin return CSLV(s,f) /= f;" + "\r\n"
					+ "		end;" + "\r\n"
					+ "		function \"/=\" (s:std_logic;f:std_logic_vector) return boolean is" + "\r\n"
					+ "			begin return CSLV(s,f) /= f;" + "\r\n"
					+ "		end;" + "\r\n"
					+ "		function \"/=\" (f:std_logic_vector;s:std_logic) return boolean is" + "\r\n"
					+ "			begin return CSLV(s,f) /= f;" + "\r\n"
					+ "		end;" + "\r\n"
                    //+ "		function \"<\" (s:std_logic;f:std_logic) return boolean is" + "\r\n"
                    //+ "			begin return ((not s) and f) = '1' ;" + "\r\n"
                    //+ "		end;		" + "\r\n"
                    //+ "		function \">\" (s:std_logic;f:std_logic) return boolean is" + "\r\n"
                    //+ "			begin return (s and (not f)) = '1' ;" + "\r\n"
                    //+ "		end;" + "\r\n"
                    //+ "		function \"<=\" (s:std_logic;f:std_logic) return boolean is" + "\r\n"
                    //+ "			begin" + "\r\n"
                    //+ "				if s = f then return true;" + "\r\n"
                    //+ "				elsif s < f then return true;" + "\r\n"
                    //+ "				else return false;" + "\r\n"
                    //+ "				end if;" + "\r\n"
                    //+ "		end;" + "\r\n"
                    //+ "		function \">=\" (s:std_logic;f:std_logic) return boolean is" + "\r\n"
                    //+ "			begin" + "\r\n"
                    //+ "				if s = f then return true;" + "\r\n"
                    //+ "				elsif s > f then return true;" + "\r\n"
                    //+ "				else return false;" + "\r\n"
                    //+ "				end if;" + "\r\n"
                    //+ "		end;		" + "\r\n"
                    //+ "		function \"<\" (s:std_logic_vector;f:std_logic_vector) return boolean is" + "\r\n"
                    //+ "			begin " + "\r\n"
                    //+ "					for I in s'left to 0 loop" + "\r\n"
                    //+ "						if (s(I) xnor f(I)) = '1'then next;" + "\r\n"
                    //+ "						else return s(I) < f(I);" + "\r\n"
                    //+ "						end if;" + "\r\n"
                    //+ "					end loop;" + "\r\n"
                    //+ "				return false;" + "\r\n"
                    //+ "		end;		" + "\r\n"
                    //+ "		function \">\" (s:std_logic_vector;f:std_logic_vector) return boolean is" + "\r\n"
                    //+ "			begin " + "\r\n"
                    //+ "					for I in s'left-1 to 0 loop" + "\r\n"
                    //+ "						if (s(I) xnor f(I)) = '1'then next;" + "\r\n"
                    //+ "						else return s(I) > f(I);" + "\r\n"
                    //+ "						end if;" + "\r\n"
                    //+ "					end loop;" + "\r\n"
                    //+ "				return false;" + "\r\n"
                    //+ "		end;" + "\r\n"
                    //+ "		function \"<=\" (s:std_logic_vector;f:std_logic_vector) return boolean is" + "\r\n"
                    //+ "			begin" + "\r\n"
                    //+ "				if s = f then return true;" + "\r\n"
                    //+ "				elsif s < f then return true;" + "\r\n"
                    //+ "				else return false;" + "\r\n"
                    //+ "				end if;" + "\r\n"
                    //+ "		end;" + "\r\n"
                    //+ "		function \">=\" (s:std_logic_vector;f:std_logic_vector) return boolean is" + "\r\n"
                    //+ "			begin" + "\r\n"
                    //+ "				if s = f then return true;" + "\r\n"
                    //+ "				elsif s > f then return true;" + "\r\n"
                    //+ "				else return false;" + "\r\n"
                    //+ "				end if;" + "\r\n"
                    //+ "		end;" + "\r\n"
                    //+ "		function \"<\" (s:integer;f:integer) return boolean is" + "\r\n"
                    //+ "			begin return conv_std_logic_vector(s,64) < conv_std_logic_vector(f,64);" + "\r\n"
                    //+ "		end;		" + "\r\n"
                    //+ "		function \">\" (s:integer;f:integer) return boolean is" + "\r\n"
                    //+ "			begin return conv_std_logic_vector(s,64) > conv_std_logic_vector(f,64);" + "\r\n"
                    //+ "		end;" + "\r\n"
                    //+ "		function \"<=\" (s:integer;f:integer) return boolean is" + "\r\n"
                    //+ "			begin" + "\r\n"
                    //+ "				if s = f then return true;" + "\r\n"
                    //+ "				elsif s < f then return true;" + "\r\n"
                    //+ "				else return false;" + "\r\n"
                    //+ "				end if;" + "\r\n"
                    //+ "		end;" + "\r\n"
                    //+ "		function \">=\" (s:integer;f:integer) return boolean is" + "\r\n"
                    //+ "			begin" + "\r\n"
                    //+ "				if s = f then return true;" + "\r\n"
                    //+ "				elsif s > f then return true;" + "\r\n"
                    //+ "				else return false;" + "\r\n"
                    //+ "				end if;" + "\r\n"
                    //+ "		end;" + "\r\n"
					+ "		function \">=\" (f:std_logic;s:integer) return boolean is" + "\r\n"
					+ "			begin return CSLV(s,f) >= f;" + "\r\n"
					+ "		end;" + "\r\n"
					+ "		function \">=\" (s:integer;f:std_logic) return boolean is" + "\r\n"
					+ "			begin return CSLV(s,f) >= f;" + "\r\n"
					+ "		end;" + "\r\n"
					+ "		function \">=\" (s:integer;f:std_logic_vector) return boolean is" + "\r\n"
					+ "			begin return CSLV(s,f) >= f;" + "\r\n"
					+ "		end;" + "\r\n"
					+ "		function \">=\" (f:std_logic_vector;s:integer) return boolean is" + "\r\n"
					+ "			begin return CSLV(s,f) >= f;" + "\r\n"
					+ "		end;" + "\r\n"
					+ "		function \">=\" (s:std_logic;f:std_logic_vector) return boolean is" + "\r\n"
					+ "			begin return CSLV(s,f) >= f;" + "\r\n"
					+ "		end;" + "\r\n"
					+ "		function \">=\" (f:std_logic_vector;s:std_logic) return boolean is" + "\r\n"
					+ "			begin return CSLV(s,f) >= f;" + "\r\n"
					+ "		end;" + "\r\n"
					+ "		function \"<=\" (f:std_logic;s:integer) return boolean is" + "\r\n"
					+ "			begin return CSLV(s,f) <= f;" + "\r\n"
					+ "		end;" + "\r\n"
					+ "		function \"<=\" (s:integer;f:std_logic) return boolean is" + "\r\n"
					+ "			begin return CSLV(s,f) <= f;" + "\r\n"
					+ "		end;" + "\r\n"
					+ "		function \"<=\" (s:integer;f:std_logic_vector) return boolean is" + "\r\n"
					+ "			begin return CSLV(s,f) <= f;" + "\r\n"
					+ "		end;" + "\r\n"
					+ "		function \"<=\" (f:std_logic_vector;s:integer) return boolean is" + "\r\n"
					+ "			begin return CSLV(s,f) <= f;" + "\r\n"
					+ "		end;" + "\r\n"
					+ "		function \"<=\" (s:std_logic;f:std_logic_vector) return boolean is" + "\r\n"
					+ "			begin return CSLV(s,f) <= f;" + "\r\n"
					+ "		end;" + "\r\n"
					+ "		function \"<=\" (f:std_logic_vector;s:std_logic) return boolean is" + "\r\n"
					+ "			begin return CSLV(s,f) <= f;" + "\r\n"
					+ "		end;" + "\r\n"
					+ "		function \">\" (s:integer;f:std_logic) return boolean is" + "\r\n"
					+ "			begin return CSLV(s,f) > f;" + "\r\n"
					+ "		end;" + "\r\n"
					+ "		function \">\" (f:std_logic;s:integer) return boolean is" + "\r\n"
					+ "			begin return CSLV(s,f) > f;" + "\r\n"
					+ "		end;" + "\r\n"
					+ "		function \">\" (s:integer;f:std_logic_vector) return boolean is" + "\r\n"
					+ "			begin return CSLV(s,f) > f;" + "\r\n"
					+ "		end;" + "\r\n"
					+ "		function \">\" (f:std_logic_vector;s:integer) return boolean is" + "\r\n"
					+ "			begin return CSLV(s,f) > f;" + "\r\n"
					+ "		end;" + "\r\n"
					+ "		function \">\" (s:std_logic;f:std_logic_vector) return boolean is" + "\r\n"
					+ "			begin return CSLV(s,f) > f;" + "\r\n"
					+ "		end;" + "\r\n"
					+ "		function \">\" (f:std_logic_vector;s:std_logic) return boolean is" + "\r\n"
					+ "			begin return CSLV(s,f) > f;" + "\r\n"
					+ "		end;" + "\r\n"
					+ "		function \"<\" (s:integer;f:std_logic) return boolean is" + "\r\n"
					+ "			begin return CSLV(s,f) < f;" + "\r\n"
					+ "		end;" + "\r\n"
					+ "		function \"<\" (f:std_logic;s:integer) return boolean is" + "\r\n"
					+ "			begin return CSLV(s,f) < f;" + "\r\n"
					+ "		end;" + "\r\n"
					+ "		function \"<\" (s:integer;f:std_logic_vector) return boolean is" + "\r\n"
					+ "			begin return CSLV(s,f) < f;" + "\r\n"
					+ "		end;" + "\r\n"
					+ "		function \"<\" (f:std_logic_vector;s:integer) return boolean is" + "\r\n"
					+ "			begin return CSLV(s,f) < f;" + "\r\n"
					+ "		end;" + "\r\n"
					+ "		function \"<\" (s:std_logic;f:std_logic_vector) return boolean is" + "\r\n"
					+ "			begin return CSLV(s,f) < f;" + "\r\n"
					+ "		end;" + "\r\n"
					+ "		function \"<\" (f:std_logic_vector;s:std_logic) return boolean is" + "\r\n"
					+ "			begin return CSLV(s,f) < f;" + "\r\n"
					+ "		end;" + "\r\n"
                    + "		function CSLV (shape_i:std_logic) return boolean is" + "\r\n"
                    + "			begin return shape_i = '1';" + "\r\n"
                    + "		end function CSLV;" + "\r\n"
                    + "		function CSLV (shape_i:std_logic_vector) return boolean is" + "\r\n"
                    + "				constant zeros: std_logic_vector(shape_i'left downto 0):= (others => '0');" + "\r\n"
                    + "			begin return not(shape_i = zeros );			" + "\r\n"
                    + "		end function CSLV;" + "\r\n"
                    + "		function CSLV (shape_i:integer) return boolean is" + "\r\n"
                    + "			begin return CSLV(conv_std_logic_vector(shape_i,64));" + "\r\n"
                    + "		end function CSLV;" + "\r\n"
                    + "		function CSLV (shape_i:boolean) return boolean is" + "\r\n"
                    + "			begin return shape_i;" + "\r\n"
                    + "		end function CSLV;" + "\r\n"
					+ "		function \"SLL\" (s:std_logic_vector;f:integer) return std_logic_vector is" + "\r\n"
					+ "			variable s_v: std_logic_vector(s'left downto 0);" + "\r\n"
			        + "            begin" + "\r\n"
                    + "			s_v := s;" + "\r\n"
                    + "			if(f > 0) then --left shift" + "\r\n"
                    + "				for I in 0 to (f-1) loop" + "\r\n"
                    + "					 s_v := s_v(s_v'left-1 downto 0)&'0';" + "\r\n"
                    + "				end loop;" + "\r\n"
                    + "			elsif(f <0) then --right shift" + "\r\n"
                    + "				for I in (f+1) to 0 loop		" + "\r\n"
                    + "					s_v := '0'&s_v(s_v'left downto 1);" + "\r\n"
                    + "				end loop;" + "\r\n"
                    + "			end if;" + "\r\n"
                    + "			return s_v; " + "\r\n"
					+ "		end;" + "\r\n"
					+ "		function \"SLL\" (s:integer;f:integer) return std_logic_vector is" + "\r\n"
					+ "			variable s_v: std_logic_vector(32 downto 0);" + "\r\n"
					+ "			begin " + "\r\n"
					+ "			s_v := (conv_std_logic_vector(s,64));" + "\r\n"
					+ "			return 	s_v SLL f;" + "\r\n"
					+ "		end;" + "\r\n"
					+ "		function \"SRL\" (s:std_logic_vector;f:integer) return std_logic_vector is" + "\r\n"
                    + "			variable s_v: std_logic_vector(s'left downto 0);" + "\r\n"
                    + "            begin" + "\r\n"
                    + "			s_v := s;" + "\r\n"
                    + "			if(f < 0) then --left shift" + "\r\n"
                    + "				for I in 0 to (f-1) loop" + "\r\n"
                    + "					 s_v := s_v(s_v'left-1 downto 0)&'0';" + "\r\n"
                    + "				end loop;" + "\r\n"
                    + "			elsif(f > 0) then --right shift" + "\r\n"
                    + "				for I in (f+1) to 0 loop		" + "\r\n"
                    + "					s_v := '0'&s_v(s_v'left downto 1);" + "\r\n"
                    + "				end loop;" + "\r\n"
                    + "			end if;" + "\r\n"
                    + "			return s_v; " + "\r\n"
					+ "		end;" + "\r\n"
					+ "		function \"SRL\" (s:integer;f:integer) return std_logic_vector is" + "\r\n"
					+ "			variable s_v: std_logic_vector(32 downto 0);" + "\r\n"
					+ "			begin " + "\r\n"
					+ "			s_v := (conv_std_logic_vector(s,64));" + "\r\n"
					+ "			return 	s_v SRL f;" + "\r\n"
					+ "		end;" + "\r\n"
					+ "		function mod_1(s,f:integer)return std_logic_vector is" + "\r\n"
					+ "			begin return conv_std_logic_vector(s mod f,32);" + "\r\n"
					+ "		end mod_1;" + "\r\n"
					+ "		function \"mod\" (s:std_logic_vector;f:std_logic_vector) return std_logic_vector is" + "\r\n"
					+ "			begin return mod_1(conv_integer(s),conv_integer(f));" + "\r\n"
					+ "		end;" + "\r\n"
					+ "		function \"mod\" (s:std_logic_vector;f:integer) return std_logic_vector is" + "\r\n"
					+ "			begin return mod_1(conv_integer(s),f);" + "\r\n"
					+ "		end;" + "\r\n"
					+ "		function \"mod\" (s:integer;f:std_logic_vector) return std_logic_vector is" + "\r\n"
					+ "			begin return mod_1(s,conv_integer(f));" + "\r\n"
					+ "		end;		" + "\r\n"
					+ "		function \"mod\" (s:integer;f:integer) return std_logic_vector is" + "\r\n"
					+ "			begin return mod_1(s,f);" + "\r\n"
					+ "		end;" + "\r\n"
					+ "		function \"+\" (s:std_logic;f:integer) return integer is" + "\r\n"
					+ "			begin return conv_integer(s)+f;" + "\r\n"
					+ "		end;" + "\r\n"
					+ "		function \"+\" (f:integer;s:std_logic) return integer is" + "\r\n"
					+ "			begin return conv_integer(s)+f;" + "\r\n"
					+ "		end;		" + "\r\n"
					+ "		function \"-\" (s:std_logic;f:integer) return integer is" + "\r\n"
					+ "			begin return conv_integer(s)-f;" + "\r\n"
					+ "		end;" + "\r\n"
					+ "		function \"-\" (f:integer;s:std_logic) return integer is" + "\r\n"
					+ "			begin return conv_integer(s)-f;" + "\r\n"
					+ "		end;		" + "\r\n"
					+ "		function \"*\" (s:integer;f:std_logic_vector) return integer is" + "\r\n"
					+ "			begin return s * conv_integer(f);" + "\r\n"
					+ "		end;" + "\r\n"
					+ "		function \"*\" (f:std_logic_vector;s:integer) return integer is" + "\r\n"
					+ "			begin return s * conv_integer(f);" + "\r\n"
					+ "		end;		" + "\r\n"
					+ "		function \"*\" (s:integer;f:std_logic) return integer is" + "\r\n"
					+ "			begin return s* conv_integer(f);" + "\r\n"
					+ "		end;" + "\r\n"
					+ "		function \"*\" (s:std_logic_vector;f:std_logic) return integer is" + "\r\n"
					+ "			begin return conv_integer(s) * conv_integer(f);" + "\r\n"
					+ "		end;" + "\r\n"
					+ "		function \"*\" (f:std_logic;s:integer) return integer is" + "\r\n"
					+ "			begin return s* conv_integer(f);" + "\r\n"
					+ "		end;" + "\r\n"
					+ "		function \"*\" (f:std_logic;s:std_logic_vector) return integer is" + "\r\n"
					+ "			begin return conv_integer(s) * conv_integer(f);" + "\r\n"
					+ "		end;		" + "\r\n"
					+ "		function \"/\" (s:integer;f:std_logic_vector) return integer is" + "\r\n"
					+ "			begin return s / conv_integer(f);" + "\r\n"
					+ "		end;" + "\r\n"
					+ "		function \"/\" (f:std_logic_vector;s:integer) return integer is" + "\r\n"
					+ "			begin return s / conv_integer(f);" + "\r\n"
					+ "		end;			" + "\r\n"
					+ "		function \"/\" (s:integer;f:std_logic) return integer is" + "\r\n"
					+ "			begin return s/ conv_integer(f);" + "\r\n"
					+ "		end;" + "\r\n"
					+ "		function \"/\" (s:std_logic_vector;f:std_logic) return integer is" + "\r\n"
					+ "			begin return conv_integer(s) / conv_integer(f);" + "\r\n"
					+ "		end;" + "\r\n"
					+ "		function \"/\" (f:std_logic;s:integer) return integer is" + "\r\n"
					+ "			begin return s/ conv_integer(f);" + "\r\n"
					+ "		end;" + "\r\n"
					+ "		function \"/\" (f:std_logic;s:std_logic_vector) return integer is" + "\r\n"
					+ "			begin return conv_integer(s) / conv_integer(f);" + "\r\n"
					+ "		end;	" + "\r\n"
					+ "		function \"and\" (shape_i: std_logic; fit_i: std_logic_vector) return std_logic_vector is" + "\r\n"
					+ "			constant zeros : std_logic_vector(fit_i'left downto 0) := (others=>'0');" + "\r\n"
					+ "			constant ones : std_logic_vector(fit_i'left downto 0) := (others => '1');" + "\r\n"
					+ "			begin" + "\r\n"
					+ "			if shape_i = '1' then return ones AND fit_i;" + "\r\n"
					+ "			else return zeros AND fit_i;" + "\r\n"
					+ "			end if;" + "\r\n"
					+ "		end ;" + "\r\n"
					+ "		function \"and\" (fit_i: std_logic_vector;shape_i: std_logic) return std_logic_vector is" + "\r\n"
					+ "			constant zeros : std_logic_vector(fit_i'left downto 0) := (others=>'0');" + "\r\n"
					+ "			constant ones : std_logic_vector(fit_i'left downto 0) := (others => '1');" + "\r\n"
					+ "			begin" + "\r\n"
					+ "			if shape_i = '1' then return ones AND fit_i;" + "\r\n"
					+ "			else return zeros AND fit_i;" + "\r\n"
					+ "			end if;" + "\r\n"
					+ "		end ;" + "\r\n"
					+ "		function \"and\" (shape_i: integer; fit_i: std_logic_vector) return std_logic_vector is" + "\r\n"
					+ "			begin return CSLV(shape_i, fit_i) AND fit_i;" + "\r\n"
					+ "		end ;" + "\r\n"
					+ "		function \"and\" (fit_i: std_logic_vector;shape_i: integer) return std_logic_vector is" + "\r\n"
					+ "			begin return CSLV(shape_i, fit_i) AND fit_i;" + "\r\n"
					+ "		end ;		" + "\r\n"
					+ "		function \"and\" (shape_i: integer; fit_i: std_logic) return std_logic is" + "\r\n"
					+ "			begin return CSLV(shape_i, fit_i) AND fit_i;" + "\r\n"
					+ "		end ;" + "\r\n"
					+ "		function \"and\" (fit_i: std_logic;shape_i: integer) return std_logic is" + "\r\n"
					+ "			begin return CSLV(shape_i, fit_i) AND fit_i;" + "\r\n"
					+ "		end ;" + "\r\n"
					+ "		function \"or\" (shape_i: std_logic; fit_i: std_logic_vector) return std_logic_vector is" + "\r\n"
					+ "			constant zeros : std_logic_vector(fit_i'left downto 0) := (others=>'0');" + "\r\n"
					+ "			constant ones : std_logic_vector(fit_i'left downto 0) := (others => '1');" + "\r\n"
					+ "			begin" + "\r\n"
					+ "			if shape_i = '1' then return ones or fit_i;" + "\r\n"
					+ "			else return zeros or fit_i;" + "\r\n"
					+ "			end if;" + "\r\n"
					+ "		end ;" + "\r\n"
					+ "		function \"or\" (fit_i: std_logic_vector;shape_i: std_logic) return std_logic_vector is" + "\r\n"
					+ "			constant zeros : std_logic_vector(fit_i'left downto 0) := (others=>'0');" + "\r\n"
					+ "			constant ones : std_logic_vector(fit_i'left downto 0) := (others => '1');" + "\r\n"
					+ "			begin" + "\r\n"
					+ "			if shape_i = '1' then return ones or fit_i;" + "\r\n"
					+ "			else return zeros or fit_i;" + "\r\n"
					+ "			end if;" + "\r\n"
					+ "		end ;" + "\r\n"
					+ "		function \"or\" (shape_i: integer; fit_i: std_logic_vector) return std_logic_vector is" + "\r\n"
					+ "			begin return CSLV(shape_i, fit_i) or fit_i;" + "\r\n"
					+ "		end ;" + "\r\n"
					+ "		function \"or\" (fit_i: std_logic_vector;shape_i: integer) return std_logic_vector is" + "\r\n"
					+ "			begin return CSLV(shape_i, fit_i) or fit_i;" + "\r\n"
					+ "		end ;		" + "\r\n"
					+ "		function \"or\" (shape_i: integer; fit_i: std_logic) return std_logic is" + "\r\n"
					+ "			begin return CSLV(shape_i, fit_i) or fit_i;" + "\r\n"
					+ "		end ;" + "\r\n"
					+ "		function \"or\" (fit_i: std_logic;shape_i: integer) return std_logic is" + "\r\n"
					+ "			begin return CSLV(shape_i, fit_i) or fit_i;" + "\r\n"
					+ "		end ;" + "\r\n"
					+ "		function \"xnor\" (shape_i: std_logic; fit_i: std_logic_vector) return std_logic_vector is" + "\r\n"
					+ "			constant zeros : std_logic_vector(fit_i'left downto 0) := (others=>'0');" + "\r\n"
					+ "			constant ones : std_logic_vector(fit_i'left downto 0) := (others => '1');" + "\r\n"
					+ "			begin" + "\r\n"
					+ "			if shape_i = '1' then return ones xnor fit_i;" + "\r\n"
					+ "			else return zeros xnor fit_i;" + "\r\n"
					+ "			end if;" + "\r\n"
					+ "		end ;" + "\r\n"
					+ "		function \"xnor\" (fit_i: std_logic_vector;shape_i: std_logic) return std_logic_vector is" + "\r\n"
					+ "			constant zeros : std_logic_vector(fit_i'left downto 0) := (others=>'0');" + "\r\n"
					+ "			constant ones : std_logic_vector(fit_i'left downto 0) := (others => '1');" + "\r\n"
					+ "			begin" + "\r\n"
					+ "			if shape_i = '1' then return ones xnor fit_i;" + "\r\n"
					+ "			else return zeros xnor fit_i;" + "\r\n"
					+ "			end if;" + "\r\n"
					+ "		end ;" + "\r\n"
					+ "		function \"xnor\" (shape_i: integer; fit_i: std_logic_vector) return std_logic_vector is" + "\r\n"
					+ "			begin return CSLV(shape_i, fit_i) xnor fit_i;" + "\r\n"
					+ "		end ;" + "\r\n"
					+ "		function \"xnor\" (fit_i: std_logic_vector;shape_i: integer) return std_logic_vector is" + "\r\n"
					+ "			begin return CSLV(shape_i, fit_i) xnor fit_i;" + "\r\n"
					+ "		end ;		" + "\r\n"
					+ "		function \"xnor\" (shape_i: integer; fit_i: std_logic) return std_logic is" + "\r\n"
					+ "			begin return CSLV(shape_i, fit_i) xnor fit_i;" + "\r\n"
					+ "		end ;" + "\r\n"
					+ "		function \"xnor\" (fit_i: std_logic;shape_i: integer) return std_logic is" + "\r\n"
					+ "			begin return CSLV(shape_i, fit_i) xnor fit_i;" + "\r\n"
					+ "		end ;" + "\r\n"
					+ "		function \"nand\" (shape_i: std_logic; fit_i: std_logic_vector) return std_logic_vector is" + "\r\n"
					+ "			constant zeros : std_logic_vector(fit_i'left downto 0) := (others=>'0');" + "\r\n"
					+ "			constant ones : std_logic_vector(fit_i'left downto 0) := (others => '1');" + "\r\n"
					+ "			begin" + "\r\n"
					+ "			if shape_i = '1' then return ones nand fit_i;" + "\r\n"
					+ "			else return zeros nand fit_i;" + "\r\n"
					+ "			end if;" + "\r\n"
					+ "		end ;" + "\r\n"
					+ "		function \"nand\" (fit_i: std_logic_vector;shape_i: std_logic) return std_logic_vector is" + "\r\n"
					+ "			constant zeros : std_logic_vector(fit_i'left downto 0) := (others=>'0');" + "\r\n"
					+ "			constant ones : std_logic_vector(fit_i'left downto 0) := (others => '1');" + "\r\n"
					+ "			begin" + "\r\n"
					+ "			if shape_i = '1' then return ones nand fit_i;" + "\r\n"
					+ "			else return zeros nand fit_i;" + "\r\n"
					+ "			end if;" + "\r\n"
					+ "		end ;" + "\r\n"
					+ "		function \"nand\" (shape_i: integer; fit_i: std_logic_vector) return std_logic_vector is" + "\r\n"
					+ "			begin return CSLV(shape_i, fit_i) nand fit_i;" + "\r\n"
					+ "		end ;" + "\r\n"
					+ "		function \"nand\" (fit_i: std_logic_vector;shape_i: integer) return std_logic_vector is" + "\r\n"
					+ "			begin return CSLV(shape_i, fit_i) nand fit_i;" + "\r\n"
					+ "		end ;		" + "\r\n"
					+ "		function \"nand\" (shape_i: integer; fit_i: std_logic) return std_logic is" + "\r\n"
					+ "			begin return CSLV(shape_i, fit_i) nand fit_i;" + "\r\n"
					+ "		end ;" + "\r\n"
					+ "		function \"nand\" (fit_i: std_logic;shape_i: integer) return std_logic is" + "\r\n"
					+ "			begin return CSLV(shape_i, fit_i) nand fit_i;" + "\r\n"
					+ "		end ;	" + "\r\n"
					+ "		function \"nor\" (shape_i: std_logic; fit_i: std_logic_vector) return std_logic_vector is" + "\r\n"
					+ "			constant zeros : std_logic_vector(fit_i'left downto 0) := (others=>'0');" + "\r\n"
					+ "			constant ones : std_logic_vector(fit_i'left downto 0) := (others => '1');" + "\r\n"
					+ "			begin" + "\r\n"
					+ "			if shape_i = '1' then return ones nor fit_i;" + "\r\n"
					+ "			else return zeros nor fit_i;" + "\r\n"
					+ "			end if;" + "\r\n"
					+ "		end ;" + "\r\n"
					+ "		function \"nor\" (fit_i: std_logic_vector;shape_i: std_logic) return std_logic_vector is" + "\r\n"
					+ "			constant zeros : std_logic_vector(fit_i'left downto 0) := (others=>'0');" + "\r\n"
					+ "			constant ones : std_logic_vector(fit_i'left downto 0) := (others => '1');" + "\r\n"
					+ "			begin" + "\r\n"
					+ "			if shape_i = '1' then return ones nor fit_i;" + "\r\n"
					+ "			else return zeros nor fit_i;" + "\r\n"
					+ "			end if;" + "\r\n"
					+ "		end ;" + "\r\n"
					+ "		function \"nor\" (shape_i: integer; fit_i: std_logic_vector) return std_logic_vector is" + "\r\n"
					+ "			begin return CSLV(shape_i, fit_i) nor fit_i;" + "\r\n"
					+ "		end ;" + "\r\n"
					+ "		function \"nor\" (fit_i: std_logic_vector;shape_i: integer) return std_logic_vector is" + "\r\n"
					+ "			begin return CSLV(shape_i, fit_i) nor fit_i;" + "\r\n"
					+ "		end ;		" + "\r\n"
					+ "		function \"nor\" (shape_i: integer; fit_i: std_logic) return std_logic is" + "\r\n"
					+ "			begin return CSLV(shape_i, fit_i) nor fit_i;" + "\r\n"
					+ "		end ;" + "\r\n"
					+ "		function \"nor\" (fit_i: std_logic;shape_i: integer) return std_logic is" + "\r\n"
					+ "			begin return CSLV(shape_i, fit_i) nor fit_i;" + "\r\n"
					+ "		end ;	" + "\r\n"
					+ "		function \"xor\" (shape_i: std_logic; fit_i: std_logic_vector) return std_logic_vector is" + "\r\n"
					+ "			constant zeros : std_logic_vector(fit_i'left downto 0) := (others=>'0');" + "\r\n"
					+ "			constant ones : std_logic_vector(fit_i'left downto 0) := (others => '1');" + "\r\n"
					+ "			begin" + "\r\n"
					+ "			if shape_i = '1' then return ones xor fit_i;" + "\r\n"
					+ "			else return zeros xor fit_i;" + "\r\n"
					+ "			end if;" + "\r\n"
					+ "		end ;" + "\r\n"
					+ "		function \"xor\" (fit_i: std_logic_vector;shape_i: std_logic) return std_logic_vector is" + "\r\n"
					+ "			constant zeros : std_logic_vector(fit_i'left downto 0) := (others=>'0');" + "\r\n"
					+ "			constant ones : std_logic_vector(fit_i'left downto 0) := (others => '1');" + "\r\n"
					+ "			begin" + "\r\n"
					+ "			if shape_i = '1' then return ones xor fit_i;" + "\r\n"
					+ "			else return zeros xor fit_i;" + "\r\n"
					+ "			end if;" + "\r\n"
					+ "		end ;" + "\r\n"
					+ "		function \"xor\" (shape_i: integer; fit_i: std_logic_vector) return std_logic_vector is" + "\r\n"
					+ "			begin return CSLV(shape_i, fit_i) xor fit_i;" + "\r\n"
					+ "		end ;" + "\r\n"
					+ "		function \"xor\" (fit_i: std_logic_vector;shape_i: integer) return std_logic_vector is" + "\r\n"
					+ "			begin return CSLV(shape_i, fit_i) xor fit_i;" + "\r\n"
					+ "		end ;		" + "\r\n"
					+ "		function \"xor\" (shape_i: integer; fit_i: std_logic) return std_logic is" + "\r\n"
					+ "			begin return CSLV(shape_i, fit_i) xor fit_i;" + "\r\n"
					+ "		end ;" + "\r\n"
					+ "		function \"xor\" (fit_i: std_logic;shape_i: integer) return std_logic is" + "\r\n"
					+ "			begin return CSLV(shape_i, fit_i) xor fit_i;" + "\r\n"
					+ "		end ;		" + "\r\n"
					+ "		function \"and\" (s: boolean;f:std_logic) return std_logic is" + "\r\n"
					+ "			begin " + "\r\n"
					+ "				if s then return '1' AND f; " + "\r\n"
					+ "				else return '0' AND f; " + "\r\n"
					+ "				end if;" + "\r\n"
					+ "		end;" + "\r\n"
					+ "		function \"and\" (s: boolean;f:std_logic_vector) return std_logic_vector is" + "\r\n"
					+ "			begin " + "\r\n"
					+ "				if s then return '1' AND f;" + "\r\n"
					+ "				else return '0' AND f;" + "\r\n"
					+ "				end if;" + "\r\n"
					+ "		end;" + "\r\n"
					+ "		function \"and\" (f:integer;s: boolean) return std_logic is" + "\r\n"
					+ "			begin" + "\r\n"
					+ "				if s then return '1' and f;" + "\r\n"
					+ "				else return  '0' and f; " + "\r\n"
					+ "				end if;" + "\r\n"
					+ "		end;" + "\r\n"
					+ "		function \"and\" (s: boolean;f:integer) return std_logic is" + "\r\n"
					+ "			begin" + "\r\n"
					+ "				if s then return '1' and f;" + "\r\n"
					+ "				else return '0' and f; " + "\r\n"
					+ "				end if;" + "\r\n"
					+ "		end;		" + "\r\n"
					+ "		function \"and\" (f:std_logic;s: boolean) return std_logic is" + "\r\n"
					+ "			begin " + "\r\n"
					+ "				if s then return '1' AND f; " + "\r\n"
					+ "				else return '0' and f; " + "\r\n"
					+ "				end if;" + "\r\n"
					+ "		end;" + "\r\n"
					+ "		function \"and\" (f:std_logic_vector;s: boolean) return std_logic_vector is" + "\r\n"
					+ "			begin " + "\r\n"
					+ "				if s then return '1' AND f;" + "\r\n"
					+ "				else return '0' AND f;" + "\r\n"
					+ "				end if;" + "\r\n"
					+ "		end;" + "\r\n"
                    //+ "		function \"and\" (s: boolean;f:boolean) return std_logic is" + "\r\n"
                    //+ "			begin " + "\r\n"
                    //+ "				if s then return '1' AND f ;" + "\r\n"
                    //+ "				else return '0' AND f;" + "\r\n"
                    //+ "				end if;" + "\r\n"
                    //+ "		end;" + "\r\n"
                    //+ "----" + "\r\n"
					+ "		function \"xnor\" (s: boolean;f:std_logic) return std_logic is" + "\r\n"
					+ "			begin " + "\r\n"
					+ "				if s then return '1' xnor f; " + "\r\n"
					+ "				else return '0' xnor f; " + "\r\n"
					+ "				end if;" + "\r\n"
					+ "		end;" + "\r\n"
					+ "		function \"xnor\" (s: boolean;f:std_logic_vector) return std_logic_vector is" + "\r\n"
					+ "			begin " + "\r\n"
					+ "				if s then return '1' xnor f;" + "\r\n"
					+ "				else return '0' xnor f;" + "\r\n"
					+ "				end if;" + "\r\n"
					+ "		end;" + "\r\n"
					+ "		function \"xnor\" (f:integer;s: boolean) return std_logic is" + "\r\n"
					+ "			begin" + "\r\n"
					+ "				if s then return '1' xnor f;" + "\r\n"
					+ "				else return  '0' xnor f; " + "\r\n"
					+ "				end if;" + "\r\n"
					+ "		end;" + "\r\n"
					+ "		function \"xnor\" (s: boolean;f:integer) return std_logic is" + "\r\n"
					+ "			begin" + "\r\n"
					+ "				if s then return '1' xnor f;" + "\r\n"
					+ "				else return '0' xnor f; " + "\r\n"
					+ "				end if;" + "\r\n"
					+ "		end;		" + "\r\n"
					+ "		function \"xnor\" (f:std_logic;s: boolean) return std_logic is" + "\r\n"
					+ "			begin " + "\r\n"
					+ "				if s then return '1' xnor f; " + "\r\n"
					+ "				else return '0' xnor f; " + "\r\n"
					+ "				end if;" + "\r\n"
					+ "		end;" + "\r\n"
					+ "		function \"xnor\" (f:std_logic_vector;s: boolean) return std_logic_vector is" + "\r\n"
					+ "			begin " + "\r\n"
					+ "				if s then return '1' xnor f;" + "\r\n"
					+ "				else return '0' xnor f;" + "\r\n"
					+ "				end if;" + "\r\n"
					+ "		end;" + "\r\n"
                    //+ "		function \"xnor\" (s: boolean;f:boolean) return std_logic is" + "\r\n"
                    //+ "			begin " + "\r\n"
                    //+ "				if s then return '1' xnor f ;" + "\r\n"
                    //+ "				else return '0' xnor f;" + "\r\n"
                    //+ "				end if;" + "\r\n"
                    //+ "		end;" + "\r\n"
                    //+ "----" + "\r\n"
					+ "		function \"or\" (s: boolean;f:std_logic) return std_logic is" + "\r\n"
					+ "			begin " + "\r\n"
					+ "				if s then return '1' or f; " + "\r\n"
					+ "				else return '0' or f; " + "\r\n"
					+ "				end if;" + "\r\n"
					+ "		end;" + "\r\n"
					+ "		function \"or\" (s: boolean;f:std_logic_vector) return std_logic_vector is" + "\r\n"
					+ "			begin " + "\r\n"
					+ "				if s then return '1' or f;" + "\r\n"
					+ "				else return '0' or f;" + "\r\n"
					+ "				end if;" + "\r\n"
					+ "		end;" + "\r\n"
					+ "		function \"or\" (f:integer;s: boolean) return std_logic is" + "\r\n"
					+ "			begin" + "\r\n"
					+ "				if s then return '1' or f;" + "\r\n"
					+ "				else return  '0' or f; " + "\r\n"
					+ "				end if;" + "\r\n"
					+ "		end;" + "\r\n"
					+ "		function \"or\" (s: boolean;f:integer) return std_logic is" + "\r\n"
					+ "			begin" + "\r\n"
					+ "				if s then return '1' or f;" + "\r\n"
					+ "				else return '0' or f; " + "\r\n"
					+ "				end if;" + "\r\n"
					+ "		end;		" + "\r\n"
					+ "		function \"or\" (f:std_logic;s: boolean) return std_logic is" + "\r\n"
					+ "			begin " + "\r\n"
					+ "				if s then return '1' or f; " + "\r\n"
					+ "				else return '0' or f; " + "\r\n"
					+ "				end if;" + "\r\n"
					+ "		end;" + "\r\n"
					+ "		function \"or\" (f:std_logic_vector;s: boolean) return std_logic_vector is" + "\r\n"
					+ "			begin " + "\r\n"
					+ "				if s then return '1' or f;" + "\r\n"
					+ "				else return '0' or f;" + "\r\n"
					+ "				end if;" + "\r\n"
					+ "		end;" + "\r\n"
                    //+ "		function \"or\" (s: boolean;f:boolean) return std_logic is" + "\r\n"
                    //+ "			begin " + "\r\n"
                    //+ "				if s then return '1' or f ;" + "\r\n"
                    //+ "				else return '0' or f;" + "\r\n"
                    //+ "				end if;" + "\r\n"
                    //+ "		end;" + "\r\n"
                    //+ "----" + "\r\n"
					+ "		function \"nand\" (s: boolean;f:std_logic) return std_logic is" + "\r\n"
					+ "			begin " + "\r\n"
					+ "				if s then return '1' nand f; " + "\r\n"
					+ "				else return '0' nand f; " + "\r\n"
					+ "				end if;" + "\r\n"
					+ "		end;" + "\r\n"
					+ "		function \"nand\" (s: boolean;f:std_logic_vector) return std_logic_vector is" + "\r\n"
					+ "			begin " + "\r\n"
					+ "				if s then return '1' nand f;" + "\r\n"
					+ "				else return '0' nand f;" + "\r\n"
					+ "				end if;" + "\r\n"
					+ "		end;" + "\r\n"
					+ "		function \"nand\" (f:integer;s: boolean) return std_logic is" + "\r\n"
					+ "			begin" + "\r\n"
					+ "				if s then return '1' nand f;" + "\r\n"
					+ "				else return  '0' nand f; " + "\r\n"
					+ "				end if;" + "\r\n"
					+ "		end;" + "\r\n"
					+ "		function \"nand\" (s: boolean;f:integer) return std_logic is" + "\r\n"
					+ "			begin" + "\r\n"
					+ "				if s then return '1' nand f;" + "\r\n"
					+ "				else return '0' nand f; " + "\r\n"
					+ "				end if;" + "\r\n"
					+ "		end;		" + "\r\n"
					+ "		function \"nand\" (f:std_logic;s: boolean) return std_logic is" + "\r\n"
					+ "			begin " + "\r\n"
					+ "				if s then return '1' nand f; " + "\r\n"
					+ "				else return '0' nand f; " + "\r\n"
					+ "				end if;" + "\r\n"
					+ "		end;" + "\r\n"
					+ "		function \"nand\" (f:std_logic_vector;s: boolean) return std_logic_vector is" + "\r\n"
					+ "			begin " + "\r\n"
					+ "				if s then return '1' nand f;" + "\r\n"
					+ "				else return '0' nand f;" + "\r\n"
					+ "				end if;" + "\r\n"
					+ "		end;" + "\r\n"
                    //+ "		function \"nand\" (s: boolean;f:boolean) return std_logic is" + "\r\n"
                    //+ "			begin " + "\r\n"
                    //+ "				if s then return '1' nand f ;" + "\r\n"
                    //+ "				else return '0' nand f;" + "\r\n"
                    //+ "				end if;" + "\r\n"
                    //+ "		end;" + "\r\n"
                    //+ "----" + "\r\n"
					+ "		function \"NOR\" (s: boolean;f:std_logic) return std_logic is" + "\r\n"
					+ "			begin " + "\r\n"
					+ "				if s then return '1' NOR f; " + "\r\n"
					+ "				else return '0' NOR f; " + "\r\n"
					+ "				end if;" + "\r\n"
					+ "		end;" + "\r\n"
					+ "		function \"NOR\" (s: boolean;f:std_logic_vector) return std_logic_vector is" + "\r\n"
					+ "			begin " + "\r\n"
					+ "				if s then return '1' NOR f;" + "\r\n"
					+ "				else return '0' NOR f;" + "\r\n"
					+ "				end if;" + "\r\n"
					+ "		end;" + "\r\n"
					+ "		function \"NOR\" (f:integer;s: boolean) return std_logic is" + "\r\n"
					+ "			begin" + "\r\n"
					+ "				if s then return '1' NOR f;" + "\r\n"
					+ "				else return  '0' NOR f; " + "\r\n"
					+ "				end if;" + "\r\n"
					+ "		end;" + "\r\n"
					+ "		function \"NOR\" (s: boolean;f:integer) return std_logic is" + "\r\n"
					+ "			begin" + "\r\n"
					+ "				if s then return '1' NOR f;" + "\r\n"
					+ "				else return '0' NOR f; " + "\r\n"
					+ "				end if;" + "\r\n"
					+ "		end;		" + "\r\n"
					+ "		function \"NOR\" (f:std_logic;s: boolean) return std_logic is" + "\r\n"
					+ "			begin " + "\r\n"
					+ "				if s then return '1' NOR f; " + "\r\n"
					+ "				else return '0' NOR f; " + "\r\n"
					+ "				end if;" + "\r\n"
					+ "		end;" + "\r\n"
					+ "		function \"NOR\" (f:std_logic_vector;s: boolean) return std_logic_vector is" + "\r\n"
					+ "			begin " + "\r\n"
					+ "				if s then return '1' NOR f;" + "\r\n"
					+ "				else return '0' NOR f;" + "\r\n"
					+ "				end if;" + "\r\n"
					+ "		end;" + "\r\n"
                    //+ "		function \"NOR\" (s: boolean;f:boolean) return std_logic is" + "\r\n"
                    //+ "			begin " + "\r\n"
                    //+ "				if s then return '1' NOR f ;" + "\r\n"
                    //+ "				else return '0' NOR f;" + "\r\n"
                    //+ "				end if;" + "\r\n"
                    //+ "		end;" + "\r\n"
                    //+ "----" + "\r\n"
					+ "		function \"XOR\" (s: boolean;f:std_logic) return std_logic is" + "\r\n"
					+ "			begin " + "\r\n"
					+ "				if s then return '1' XOR f; " + "\r\n"
					+ "				else return '0' XOR f; " + "\r\n"
					+ "				end if;" + "\r\n"
					+ "		end;" + "\r\n"
					+ "		function \"XOR\" (s: boolean;f:std_logic_vector) return std_logic_vector is" + "\r\n"
					+ "			begin " + "\r\n"
					+ "				if s then return '1' XOR f;" + "\r\n"
					+ "				else return '0' XOR f;" + "\r\n"
					+ "				end if;" + "\r\n"
					+ "		end;" + "\r\n"
					+ "		function \"XOR\" (f:integer;s: boolean) return std_logic is" + "\r\n"
					+ "			begin" + "\r\n"
					+ "				if s then return '1' XOR f;" + "\r\n"
					+ "				else return  '0' XOR f; " + "\r\n"
					+ "				end if;" + "\r\n"
					+ "		end;" + "\r\n"
					+ "		function \"XOR\" (s: boolean;f:integer) return std_logic is" + "\r\n"
					+ "			begin" + "\r\n"
					+ "				if s then return '1' XOR f;" + "\r\n"
					+ "				else return '0' XOR f; " + "\r\n"
					+ "				end if;" + "\r\n"
					+ "		end;		" + "\r\n"
					+ "		function \"XOR\" (f:std_logic;s: boolean) return std_logic is" + "\r\n"
					+ "			begin " + "\r\n"
					+ "				if s then return '1' XOR f; " + "\r\n"
					+ "				else return '0' XOR f; " + "\r\n"
					+ "				end if;" + "\r\n"
					+ "		end;" + "\r\n"
					+ "		function \"XOR\" (f:std_logic_vector;s: boolean) return std_logic_vector is" + "\r\n"
					+ "			begin " + "\r\n"
					+ "				if s then return '1' XOR f;" + "\r\n"
					+ "				else return '0' XOR f;" + "\r\n"
					+ "				end if;" + "\r\n"
					+ "		end;" + "\r\n"
                    //+ "		function \"XOR\" (s: boolean;f:boolean) return std_logic is" + "\r\n"
                    //+ "			begin " + "\r\n"
                    //+ "				if s then return '1' XOR f ;" + "\r\n"
                    //+ "				else return '0' XOR f;" + "\r\n"
                    //+ "				end if;" + "\r\n"
                    //+ "		end;" + "\r\n"
					+ "end tools;" + "\r\n\r\n"
				                   ;
			tempStr += "library IEEE;" + "\r\n"
					+ "use IEEE.STD_LOGIC_1164.ALL;" + "\r\n"
					+ "use IEEE.STD_LOGIC_ARITH.ALL;" + "\r\n"
					+ "use IEEE.STD_LOGIC_UNSIGNED.ALL;" + "\r\n"
                    + "use work.tools.ALL;" + "\r\n"
					+ "\r\n"
					;
			return tempStr;
		}
		string removeWhiteSpace(string str)
		{
			return str.Replace(" ", "").Replace("\r\n", "").Replace("\t", "").Replace("\r", "").Replace("\n", "");
		}
		private String printEntity()
		{
			String tempStr = "";//declare an empty string
			tempStr += String.Format("entity {0} is", entityName) + "\r\n"
					+ String.Format("\t port (") + "\r\n";
			/*hardcode portInname, portInleft, and portInright etc*/
			String portInName, portInLeft, portInRight, portOutName, portOutLeft, portOutRight;
			tempStr += "\t\t" + String.Format("A_i :in std_logic_vector({0} downto 0);", bitWidth - 1) + "\r\n";
			tempStr += "\t\t" + String.Format("B_o :out std_logic_vector({0} downto 0);", bitWidth - 1) + "\r\n";
			tempStr += "\t\t" + "clock, reset, enable : in std_logic" + "\r\n";
			tempStr += "\t" + ");" + "\r\n"; //closing parentheses for port
			tempStr += String.Format("end {0};", entityName) + "\r\n";//end the entity
			tempStr += "\r\n";
			return tempStr;
		}
		private String printArch()//for C-Style
		{//should probably make a function to determine if its vhdl code or C code either here or in the makeHashSet part
			threePieceSet = makeHashSet(global_variables);//generate hash table for global variabls
			String tempStr = "";
			tempStr += String.Format("architecture beh of {0} is", entityName) + "\r\n";
			/*insert global variables*/
			tempStr += "\t" + "shared variable A, B: std_logic_vector(" + (bitWidth-1) + " downto 0) := (others => '0');" + "\r\n";
			//extra ports can be added here in the future
			//foreach (string str in VHDL_variables)
			//	tempStr += "\t" + str + "\r\n";
			//VHDL_variables.Clear();//clears table for the next time "makeHashSet()" is called
			//tempStr += printGlobalHashSetWithFormating();
			tempStr += "\t" + printHashSetWithFormating(true).Replace("\r\n","\r\n\t") ;
			//add pes clock component
            //tempStr += "\t" + "component PES_clock" + "\r\n"
            //                + "\t" + "\t" + "generic (max_cnt: natural:= 500000); -- max_cnt = (period * clock_in_speed)/2" + "\r\n"
            //                + "\t" + "\t" + "Port ( clock_in : in  STD_LOGIC;" + "\r\n"
            //                + "\t" + "\t" + "\t" + "clock_out : out  STD_LOGIC);" + "\r\n"
            //                + "\t" + "end component;" + "\r\n";
			//add clock signals for every process.
			foreach (Graph f in canvas)
			{
				tempStr += "\t" + string.Format("signal {0}_clock : STD_LOGIC := '0'; ", f.GetAbbrv()) + "\r\n";
			}
			tempStr += "begin" + "\r\n";
			// set io ports with shared variables
			tempStr += "\t" + "shared_variable_process: process (clock, A_i)" + "\r\n"
							+ "\t" + "begin" + "\r\n"
							+ "\t" + "\t" + "A := A_i;" + "\r\n"
							+ "\t" + "\t" + "B_o <= B;" + "\r\n"
							+ "\t" + "end process;" + "\r\n";
			tempStr += "----" + "\r\n";
			//calles printProcess()
			current_graph = 0;
			foreach (Graph g in canvas)
			{//There may be multiple graphs so you must create a process for each of them.
				tempStr += printProcessC_FSM();
				++current_graph;
			}
			tempStr += "end beh;" + "\r\n";
			//end
			return tempStr;
		}

		//print process cs120b Style AKA PES e-book style with slight modifications to make it general enough for RIBS
		private String printProcessC_FSM()
		{
			threePieceSet = makeHashSet(canvas[current_graph].GetGlobalCode());//generate hash table for local variables
			processName = removeWhiteSpace(canvas[current_graph].GetAbbrv());//gets process name of current canvas
			String tempStr = "";
			/*create clock divider for current component*/
            tempStr += printPES_Clock_Entity(get_isr_OVF_VHDL());
            //tempStr += "\t" + processName + "_clock_div_process: PES_clock" + "\r\n"
            //                + "\t" + "\t" + "GENERIC MAP(max_cnt => " + get_isr_OVF_VHDL() + " ) -- max_cnt = (period * clock_in_speed)/2" + "\r\n"
            //                + "\t" + "\t" + "PORT MAP( clock_in => clock, clock_out => " + processName + "_clock );" + "\r\n";

			/*print sensitivity list*/
			tempStr += "\t" + String.Format("{0}_process : process({0}_clock, reset, enable) ", processName) + "\r\n";
            /*print alias's for shared variable.  Shared variables are buffers bwtn ports and process*/
            /*hard coded until further notice*/
            tempStr += "\t\t";
            for (int i = 0; i < bitWidth; ++i)
                tempStr += string.Format("ALIAS A{0} is A({0});",i);
            tempStr += "\r\n";
            tempStr += "\t\t";
            for (int i = 0; i < bitWidth; ++i)
                tempStr += string.Format("ALIAS B{0} is B({0});", i);
            tempStr += "\r\n";
          
			/*print state names*/
			tempStr += "\t\t" + "type " + processName + "_States is (" + listStateNames() + ");\r\n";
			tempStr += "\t\t" + "VARIABLE " + processName + "_state : " + processName + "_States := " + getInitState() + "; \r\n";
			/*print sm variables by Derrick*/
			tempStr += "\t\t" + printHashSetWithFormating(false).Replace("\r\n", "\r\n\t\t");//
			/*interface to Serajs 
			string localVariables = removeComment0(canvas.GetGlobalCode()).Replace("\r", "");
			localVariables = cvar2vhdlvar.get_cvar2vhdlvarInput(localVariables);
			localVariables = localVariables.Trim().Replace("\r", "").Replace("\n", "").Replace("\t", "");
			tempStr += "\t" + localVariables.Replace(";", ";\r\n\t");
            */
			tempStr += "\r\n";
			tempStr += "\t" + "begin" + "\r\n";
			/*print states*/
			//tempStr += GenerateStateMachineExternal();
            tempStr += "\t" + string.Format("IF( {0} = '1' and {0}'event )THEN", processName + "_clock") + "\r\n"
                          + "\t" + "\t" + "IF(reset = '1')then--STATE machine begin" + "\r\n"
                          + "\t" + "\t" + "\t" + processName + "_state := " + getInitState() + ";" + "\r\n"
                          + "\t" + "\t" + "ELSIF(enable = '1') then" + "\r\n";
            //              
            string toReturn = "";
            ////// state actions
            //toReturn += "\t" + "\t" + "\t" + "case " + processName + "_state is -- State actions\r\n";
            //foreach (Node n in canvas[current_graph].nodes)
            //{
            //    toReturn += "\t" + "\t" + "\t" + "\t" + "when  " + processName + "_" + removeWhiteSpace(n.GetName()) + " =>" + "\r\n";
            //    string temp = removeComment0(n.GetActions().Replace("\n", "\r\n")).Trim();
            //    toReturn += convert_complete_C_action2VHDL_by_translating_it_line_by_line(temp);
            //    toReturn += "\r\n";
            //}
            //toReturn += "\t" + "\t" + "\t" + "end case;  -- end State actions\r\n\r\n";
			//------------------------------------------------
			//write toReturn for second switch statement - STATE TRANSITIONS
			bool first_flag = false;
			toReturn += "\t" + "\t" + "\t" + "case " + processName + "_state  is  -- Transitions\r\n";
			foreach (Node n in canvas[current_graph].nodes)
			{
				{
					toReturn += "\t" + "\t" + "\t" + "\t" + "when " + processName + "_" + removeWhiteSpace(n.GetName()) + " => " + "\r\n";
					bool other_exists = false;
					bool outgoingEdgesExist = false;
					int other_index = -1;
					int k = 0;
					foreach (Edge e in canvas[current_graph].edges)
					{
						if (e.GetCondition().Length == 0)
						{
							MessageBox.Show("Error: Empty condition in transition from state " + removeWhiteSpace(e.GetT().GetName()), "Error");
							return "";
						}
						if (e.GetT() == n)
						{
							if (e.GetCondition().ToLower() != "other")
							{
								if (!first_flag)
								{
									string temp = e.GetCondition();
									temp = handle_C_Condition(temp);
									toReturn += "\t" + "\t" + "\t" + "\t" + "\t" + "if (" + temp + ") then" + "\r\n";
									toReturn += "\t" + "\t" + "\t" + "\t" + "\t" + "\t" + processName + "_state := " + processName + "_" + removeWhiteSpace(e.GetH().GetName()) + ";" + "\r\n";
									first_flag = true;
									outgoingEdgesExist = true;
								}
								else
								{
									string temp = e.GetCondition();
									temp = handle_C_Condition(temp);
									toReturn += "\t" + "\t" + "\t" + "\t" + "\t" + "elsif (" + temp + ") then" + "\r\n";
									toReturn += "\t" + "\t" + "\t" + "\t" + "\t" + "\t" + processName + "_state := " + processName + "_" + removeWhiteSpace(e.GetH().GetName()) + ";" + "\r\n";
								}
								if (e.GetActions().Length > 0)
								{
									string temp = removeComment0(e.GetActions().Replace("\n", "\r\n")).Trim();
									toReturn += convert_complete_C_action2VHDL_by_translating_it_line_by_line(temp);
								}
								else
								{
									toReturn += "\r\n";
								}
							}
							else
							{
								if (other_exists == true)
								{
									MessageBox.Show("Error: Multiple 'other' transitions exist for state " + removeWhiteSpace(n.GetName()), "Error");
									return "";
								}
								else
								{
									other_exists = true;
									other_index = k;
								}
							}
						}
						++k;
					}
					if (outgoingEdgesExist == true)// first_flag is set true if it entered the If condition for the transition.  Only print if it printed an if condition
					{
						toReturn += "\t\t\t\t\t" + "else" + "\r\n"
										+ "\t\t\t\t\t\t" + processName + "_state := " + processName + "_" + removeWhiteSpace(n.GetName()) + ";" + "\r\n"
										;
						toReturn += "\t\t\t\t\t" + "end if; \r\n";
					}
					first_flag = false;

				}
			}
			toReturn += "\t\t\t\t" + "when others =>" + "\r\n";
			toReturn += "\t\t\t\t\t" + processName + "_state := " + processName + "_" + canvas[current_graph].GetInitialStateName() + ";\r\n";
			toReturn += "\t\t\t" + " end case; -- endTransitions\r\n\r\n";
            //// state actions
            toReturn += "\t" + "\t" + "\t" + "case " + processName + "_state is -- State actions\r\n";
            foreach (Node n in canvas[current_graph].nodes)
            {
                toReturn += "\t" + "\t" + "\t" + "\t" + "when  " + processName + "_" + removeWhiteSpace(n.GetName()) + " =>" + "\r\n";
                string temp = removeComment0(n.GetActions().Replace("\n", "\r\n")).Trim();
                toReturn += convert_complete_C_action2VHDL_by_translating_it_line_by_line(temp);
                toReturn += "\r\n";
            }
            toReturn += "\t" + "\t" + "\t" + "end case;  -- end State actions\r\n\r\n";
			toReturn += "\t\t" + " end if;--STATE machine end" + "\r\n";
			toReturn += "\t" + "END IF;--end clock events \r\n";
			////
			tempStr += toReturn;
			tempStr += "\t" + "end process;" + "\r\n";
			tempStr += "---- \r\n";
			return tempStr;
		}

		////print process Jtarango style 
		//private String printProcessVHDL_FSM()
		//{
		//    String tempStr = "";
		//    HashSet<String> syncSensitivityList = new HashSet<String>();
		//    HashSet<String> outputSensitivityList = new HashSet<String>();
		//    HashSet<String> transitionSensitivityList = new HashSet<String>();

		//    syncSensitivityList.Add("clock2");
		//    syncSensitivityList.Add("reset");
		//    syncSensitivityList.Add("enable");
		//    //syncSensitivityList.Add("A");
		//    //syncSensitivityList.Add("NextB");
		//    //changes the sensitivity list to have the current/Next style
		//    List<string> var = getVariableNameVHDL();
		//    foreach (string str in var)
		//    {
		//        if (str.Trim() == "") continue;
		//        if (str.Trim().ToLower() == "a") continue;
		//        if (str.Trim().ToLower() == "enable") continue;
		//        if (str.Trim().ToLower() == "reset") continue;
		//        syncSensitivityList.Add("Next" + str.Trim());
		//    }

		//    //syncSensitivityList.Add("B");
		//    outputSensitivityList.Add(string.Format("{0}_stCurrent", processName));
		//    //outputSensitivityList.Add("enable");
		//    //outputSensitivityList.Add("A");
		//    // outputSensitivityList.Add("B");//Should never put an out port in sensitivity list
		//    transitionSensitivityList.Add(string.Format("{0}_stCurrent", processName));
		//    //transitionSensitivityList.Add("enable");
		//    //transitionSensitivityList.Add("A");
		//    // transitionSensitivityList.Add("B");//should never put an outport in sensitivity list
		//    /*print sync data process*/
		//    {
		//        /*clock divider*/
		//        tempStr += "\t" + "period_Process: process(clock)" + "\r\n"
		//                        + "\t" + "variable isr_counter: std_logic_vector(31 downto 0) := (others =>'0');" + "\r\n"
		//                        + "\t" + "begin" + "\r\n"
		//                        + "\t" + "\t" + "if(clock'event and clock = '1') then" + "\r\n"

		//                        + "\t" + "\t" + "\t" + "if(isr_counter +1 >= isr_OVF) then" + "\r\n"
		//                        + "\t" + "\t" + "\t" + "\t" + "clock2 <= not clock2;" + "\r\n"
		//                        + "\t" + "\t" + "\t" + "\t" + "isr_counter := (others => '0');" + "\r\n"
		//                        + "\t" + "\t" + "\t" + "else" + "\r\n"
		//                        + "\t" + "\t" + "\t" + "\t" + "isr_counter := isr_counter +1;" + "\r\n"
		//                        + "\t" + "\t" + "\t" + "end if;" + "\r\n"

		//                        + "\t" + "\t" + "end if;" + "\r\n"
		//                        + "\t" + "end process;" + "\r\n"
		//            ;
		//        /*temporary start*/
		//        tempStr += "\t" + "B_o <= NextB;" + "\r\n";
		//        /*temporary end*/
		//        /*end clock divider*/
		//        tempStr += "\t" + processName + "Syncdata: process(";
		//        tempStr += getSyncDataSensitivityList(syncSensitivityList);
		//        tempStr += ")" + "\r\n";
		//        tempStr += "\t" + "begin" + "\r\n";

		//        tempStr += "\t" + "\t" + "if (clock2'event and clock2 = '1') then" + "\r\n";
		//        tempStr += "\t" + "\t" + "\t" + "if (reset = '1' AND (enable = '1' OR enable = '0')) then" + "\r\n";
		//        tempStr += "\t" + "\t" + "\t" + "\t" + processName + "_stCurrent <= " + processName + "_" + canvas.GetInitialStateName() + ";\r\n";
		//        //tempStr += "\t" + "\t" + "\t" + "\t" + "B_o <= (others => '0');" + "\r\n";
		//        tempStr += "\t" + "\t" + "\t" + "\t" + "--Assign other outputs to internal signals" + "\r\n";
		//        tempStr += "\t" + "\t" + "\t" + "elsif(reset = '0' AND enable = '1')then" + "\r\n";
		//        tempStr += "\t" + "\t" + "\t" + "\t" + processName + "_stCurrent <= " + processName + "_stNext" + ";\r\n";
		//        //tempStr += "\t" + "\t" + "\t" + "\t" + "B_o <= NextB;" + "\r\n";
		//        // tempStr +="\t" + "\t" + "\t" + "\t" + 		"<output> <= <output>_i;"+ "\r\n";
		//        foreach (String str in var)
		//        {
		//            if (str.Trim() == "") continue;
		//            if (str.Trim().ToLower() == "a") continue;
		//            if (str.Trim().ToLower() == "enable") continue;
		//            if (str.Trim().ToLower() == "reset") continue;
		//            tempStr += "\t" + "\t" + "\t" + "\t" + str + " <= " + "Next" + str.Trim() + ";\r\n";
		//        }
		//        tempStr += "\t" + "\t" + "\t" + "\t" + "--Assign other outputs to internal signals" + "\r\n";
		//        tempStr += "\t" + "\t" + "\t" + "end if;" + "\r\n";
		//        tempStr += "\t" + "\t" + "end if;" + "\r\n";
		//        tempStr += "\t" + "end process;" + "\r\n";
		//    }
		//    /*print output data process*/
		//    {
		//        tempStr += "\t" + processName + "OutputProcess : Process (";

		//        outputSensitivityList = getOutputSensitivityList(outputSensitivityList);
		//        int K = 0;
		//        foreach (string s in outputSensitivityList) //put stuff in sensitivity list
		//        {
		//            tempStr += s;
		//            if (++K < outputSensitivityList.Count)
		//            {
		//                tempStr += ", ";
		//            }
		//        }
		//        tempStr += ")" + "\r\n";

		//        tempStr += "\t" + "begin" + "\r\n";
		//        //actions switch statement
		//        tempStr += "\t" + "case " + processName + "_stCurrent is -- State actions\r\n";
		//        foreach (Node n in canvas.nodes)
		//        {
		//            tempStr += "\t\t" + "when  " + processName + "_" + removeWhiteSpace(n.GetName()) + " =>" + "\r\n";
		//            tempStr += "\t\t\t" + handle_VHDL_Actions(n.GetActions()).Replace("\r\n", "\r\n \t\t\t") + "\r\n ";
		//        }
		//        //the when others clause should set all signals to zero
		//        //tempStr += "\t\t" + "when others => NextB <= (others => '0'); -- ADD default behaviour below" + "\r\n";
		//        tempStr += "\t" + "end case;  -- end State actions\r\n\r\n";

		//        tempStr += "\t" + "end process;" + "\r\n";
		//    }
		//    /*print transitions data process*/
		//    {
		//        //write toReturn for second switch statement - STATE TRANSITIONS
		//        bool first_flag = false;
		//        String toReturn = "";//put the actions into this string.  this string will contain all the items needed in the sensitivity list

		//        toReturn += "\t" + "case " + processName + "_stCurrent  is  -- Transitions\r\n";

		//        foreach (Node n in canvas.nodes)
		//        {
		//            {
		//                toReturn += "\t\t" + "when " + processName + "_" + removeWhiteSpace(n.GetName()) + " => " + "\r\n";
		//                bool other_exists = false;
		//                bool outGoingEdgesExist = false;
		//                int other_index = -1;
		//                int k = 0;
		//                foreach (Edge e in canvas.edges)
		//                {
		//                    if (e.GetCondition().Length == 0)
		//                    {
		//                        MessageBox.Show("Error: Empty condition in transition from state " + removeWhiteSpace(e.GetT().GetName()), "Error");
		//                        return "";
		//                    }
		//                    if (e.GetT() == n)
		//                    {
		//                        if (e.GetCondition().ToLower() != "other")
		//                        {
		//                            if (!first_flag)
		//                            {
		//                                string temp = handle_VHDL_Conditions(e.GetCondition());
		//                                toReturn += "\t\t\t" + "if (" + temp + ") then" + "\r\n";
		//                                toReturn += "\t\t\t\t" + processName + "_stNext <= " + processName + "_" + removeWhiteSpace(e.GetH().GetName()) + ";" + "\r\n";
		//                                first_flag = true;
		//                                outGoingEdgesExist = true;
		//                            }
		//                            else
		//                            {
		//                                string temp = handle_VHDL_Conditions(e.GetCondition());
		//                                toReturn += "\t\t\t" + "elsif (" + temp + ") then" + "\r\n";
		//                                toReturn += "\t\t\t\t" + processName + "_stNext <= " + processName + "_" + removeWhiteSpace(e.GetH().GetName()) + ";" + "\r\n";
		//                            }
		//                            if (e.GetActions().Length > 0)
		//                            {
		//                                toReturn += "\t\t\t" + handle_VHDL_Actions(e.GetActions()).Replace("\r\n", "\r\n \t\t\t") + "\r\n ";
		//                            }
		//                            else
		//                            {
		//                                toReturn += "\r\n";
		//                            }
		//                        }
		//                        else
		//                        {
		//                            if (other_exists == true)
		//                            {
		//                                MessageBox.Show("Error: Multiple 'other' transitions exist for state " + removeWhiteSpace(n.GetName()), "Error");
		//                                return "";
		//                            }
		//                            else
		//                            {
		//                                other_exists = true;
		//                                other_index = k;
		//                            }
		//                        }
		//                    }
		//                    ++k;
		//                }
		//                //end of transitions for current node, append other special case
		//                if (other_exists == true)
		//                {
		//                    toReturn += "\r\n         else \r\n            " + processName + "_stNext  <= " + processName
		//                        + "_" + removeWhiteSpace(canvas.edges[other_index].GetH().GetName()) + ";";

		//                    if (canvas.edges[other_index].GetActions().Length > 0)
		//                    {
		//                        toReturn += "\r\n            " + canvas.edges[other_index].GetActions().Replace("\n", "\r\n            ") + "\r\n         ";
		//                    }
		//                    else
		//                    {
		//                        toReturn += "\r\n         ";
		//                    }
		//                }
		//                first_flag = false;
		//                if (outGoingEdgesExist == true)
		//                {
		//                    toReturn += "\t\t\t" + "else " + processName + "_stNext <= " + processName + "_" + removeWhiteSpace(n.GetName()) + "; \r\n";
		//                    toReturn += "\t\t\t" + "end if; \r\n";
		//                }
		//                else //since there are no edges it should transition to itself without a conditional statement
		//                {
		//                    toReturn += "\t\t\t" + processName + "_stNext <= " + processName + "_" + removeWhiteSpace(n.GetName()) + "; \r\n";
		//                }
		//            }
		//        }
		//        toReturn += "\t\t" + "when others =>" + "\r\n";
		//        toReturn += "\t\t\t" + processName + "_stNext <= " + processName + "_" + canvas.GetInitialStateName() + ";\r\n";
		//        toReturn += "\t end case; -- endTransitions\r\n\r\n";

		//        //fill the transitionSensitivityList with stuff that SHOULD be in the sensitivity list
		//        // future function goes here
		//        tempStr += "\t" + processName + "TransitionProcess : Process (";
		//        transitionSensitivityList = getTransitionSensitivityList(transitionSensitivityList);
		//        int K = 0;
		//        foreach (string s in transitionSensitivityList) //put stuff in sensitivity list
		//        {
		//            tempStr += s;
		//            if (++K < transitionSensitivityList.Count)
		//            {
		//                tempStr += ", ";
		//            }
		//        }
		//        tempStr += ")" + "\r\n";
		//        //append tempstr with toReturn


		//        tempStr += "\t" + "begin" + "\r\n";
		//        tempStr += toReturn;

		//        tempStr += "\t" + "end process;" + "\r\n";
		//    }

		//    return tempStr;
		//}

		private String getInitState()
		{
			//String temp = processName + "_" + removeWhiteSpace(canvas.nodes[0].GetName());
			String temp = processName + "_" + removeWhiteSpace(canvas[current_graph].GetInitialStateName());
			return temp;
		}

		private String getSyncDataSensitivityList(HashSet<string> hset)
		{
			String temp = "";
			int i = 0;
			foreach (string str in hset)
			{
				i++;
				if (str.Trim() == "") continue;

				temp += str.Trim();
				if (i < hset.Count)
					temp += " , ";
			}
			return temp;
		}

		/*prints the list of state names separated by commas. 
		 */
		private String listStateNames()
		{
			//go through each state on the canvas and fetch the name
			int nums = 0;
			String tempstr = "";
			foreach (Node n in canvas[current_graph].nodes)
			{
				nums++;
				if (removeWhiteSpace(n.GetName()).Length == 0)
				{
					if (Error_MSG_flag == false)
					{
						Error_MSG_flag = true;
						MessageBox.Show("Error: All states must be named.", "Error");
					}
					output = "";
					return "";
				}
				tempstr += processName + "_" + removeWhiteSpace(n.GetName());
				if (nums < canvas[current_graph].GetNumStates())
				{
					tempstr += ", ";
				}
			}
			return removeWhiteSpace(tempstr);
		}

		/*generates the contents between "begin" and "end process"
		 Used for C-Style FSM
		 */
		//private string GenerateStateMachineExternal()
		//{
		//    string toReturn = "";
		//    toReturn += "\t" + "--clock_div begins" + "\r\n"
		//                    + "\t" + "IF(reset = '1')then" + "\r\n"
		//                    + "\t" + "\t" + "process_ISR := \"00\";" + "\r\n"
		//                    + "\t" + "\t" + "process_CNT := (others => '0');" + "\r\n"
		//                    + "\t" + "ELSIF (reset ='0' AND clock = '1' AND clock'EVENT) then" + "\r\n"
		//        //+ "\t" + "\t" + "process_ISR := process_ISR(0) & process_ISR_helper;" + "\r\n"
		//        //+ "\t" + "\t" + "process_CNT := process_CNT + 1; " + "\r\n"
		//                    + "\t" + "\t" + "if(process_CNT >= process_OVF) then" + "\r\n"
		//                    + "\t" + "\t" + "\t" + "process_ISR_helper := not process_ISR_helper;" + "\r\n"
		//                    + "\t" + "\t" + "\t" + "process_CNT := (others => '0');" + "\r\n"
		//                    + "\t" + "\t" + "else" + "\r\n"
		//                    + "\t" + "\t" + "--STATE machine begin" + "\r\n"
		//                    ;
		//    toReturn += "\t" + "\t" + "\t" + "--SYNC DATA begin" + "\r\n"
		//                    + "\t" + "\t" + "\t" + "if(reset = '1') then" + "\r\n"
		//                    + "\t" + "\t" + "\t" + "\t" + processName + "_stCurrent := " + getInitState() + ";" + "\r\n"
		//                    + "\t" + "\t" + "\t" + "\t" + processName + "_st := " + getInitState() + ";" + "\r\n"
		//                    + "\t" + "\t" + "\t" + "elsif(enable = '1' and process_ISR = \"01\") then" + "\r\n"
		//                    + "\t" + "\t" + "\t" + "\t" + processName + "_stCurrent := " + processName + "_st; --the next_state sets the current_state" + "\r\n"
		//                    + "\t" + "\t" + "\t" + "--SYNC DATA end" + "\r\n\r\n"
		//                    ;
		//    //-------------------------------------------
		//    //actions switch statement
		//    toReturn += "\t" + "\t" + "\t" + "\t" + "case " + processName + "_stCurrent is -- State actions\r\n";
		//    foreach (Node n in canvas[current_graph].nodes)
		//    {
		//        toReturn += "\t" + "\t" + "\t" + "\t" + "\t" + "when  " + processName + "_" + removeWhiteSpace(n.GetName()) + " =>" + "\r\n";
		//        string temp = n.GetActions().Replace("\n", "\r\n");
		//        string fullAction = "";
		//        temp = removeComment0(temp);
		//        temp = temp.Trim();
		//        temp = temp.Replace(";", ";$");//adding dollar sign for easy splitting.
		//        string[] tempArr = temp.Split('$');
		//        foreach (string semiAction in tempArr)
		//        {
		//            if (removeWhiteSpace(semiAction) == "")
		//                continue;
		//            fullAction += "\t\t\t\t\t\t" + handle_C_Actions(semiAction) + "\r\n";
		//        }

		//        toReturn += fullAction;
		//        toReturn += "\r\n";
		//    }
		//    toReturn += "\t" + "\t" + "\t" + "\t" + "\t" + "when others => B := (others => '0'); -- ADD default behaviour below" + "\r\n";//most likely don't need this
		//    toReturn += "\t" + "\t" + "\t" + "\t" + "end case;  -- end State actions\r\n\r\n";
		//    //------------------------------------------------
		//    //write toReturn for second switch statement - STATE TRANSITIONS
		//    bool first_flag = false;
		//    toReturn += "\t" + "\t" + "\t" + "\t" + "case " + processName + "_stCurrent  is  -- Transitions\r\n";

		//    foreach (Node n in canvas[current_graph].nodes)
		//    {
		//        {
		//            toReturn += "\t" + "\t" + "\t" + "\t" + "\t" + "when " + processName + "_" + removeWhiteSpace(n.GetName()) + " => " + "\r\n";
		//            bool other_exists = false;
		//            bool outgoingEdgesExist = false;
		//            int other_index = -1;
		//            int k = 0;
		//            foreach (Edge e in canvas[current_graph].edges)
		//            {

		//                if (e.GetCondition().Length == 0)
		//                {
		//                    MessageBox.Show("Error: Empty condition in transition from state " + removeWhiteSpace(e.GetT().GetName()), "Error");
		//                    return "";
		//                }
		//                if (e.GetT() == n)
		//                {
		//                    if (e.GetCondition().ToLower() != "other")
		//                    {
		//                        if (!first_flag)
		//                        {
		//                            string temp = e.GetCondition();
		//                            temp = handle_C_Condition(temp);
		//                            toReturn += "\t" + "\t" + "\t" + "\t" + "\t" + "\t" + "if (" + temp + ") then" + "\r\n";
		//                            toReturn += "\t" + "\t" + "\t" + "\t" + "\t" + "\t" + "\t" + processName + "_st := " + processName + "_" + removeWhiteSpace(e.GetH().GetName()) + ";" + "\r\n";
		//                            first_flag = true;
		//                            outgoingEdgesExist = true;
		//                        }
		//                        else
		//                        {
		//                            string temp = e.GetCondition();
		//                            temp = handle_C_Condition(temp);
		//                            toReturn += "\t" + "\t" + "\t" + "\t" + "\t" + "\t" + "elsif (" + temp + ") then" + "\r\n";
		//                            toReturn += "\t" + "\t" + "\t" + "\t" + "\t" + "\t" + "\t" + processName + "_st := " + processName + "_" + removeWhiteSpace(e.GetH().GetName()) + ";" + "\r\n";
		//                        }
		//                        if (e.GetActions().Length > 0)
		//                        {
		//                            string temp = e.GetActions().Replace("\n", "\r\n");
		//                            string fullAction = "";
		//                            temp = removeComment0(temp);
		//                            temp = temp.Trim();
		//                            temp = temp.Replace(";", ";$");//adding dollar sign for easy splitting.
		//                            string[] tempArr = temp.Split('$');
		//                            foreach (string semiAction in tempArr)
		//                            {
		//                                if (removeWhiteSpace(semiAction) == "")
		//                                    continue;
		//                                fullAction += "\t\t\t\t\t\t\t" + handle_C_Actions(semiAction) + "\r\n";
		//                            }

		//                            toReturn += fullAction;
		//                        }
		//                        else
		//                        {
		//                            toReturn += "\r\n";
		//                        }
		//                    }
		//                    else
		//                    {
		//                        if (other_exists == true)
		//                        {
		//                            MessageBox.Show("Error: Multiple 'other' transitions exist for state " + removeWhiteSpace(n.GetName()), "Error");
		//                            return "";
		//                        }
		//                        else
		//                        {
		//                            other_exists = true;
		//                            other_index = k;
		//                        }
		//                    }
		//                }
		//                ++k;
		//            }
		//            if (outgoingEdgesExist == true)// first_flag is set true if it entered the If condition for the transition.  Only print if it printed an if condition
		//            {
		//                toReturn += "\t\t\t\t\t\t" + "else" + "\r\n"
		//                                + "\t\t\t\t\t\t\t" + processName + "_st := " + processName + "_" + removeWhiteSpace(n.GetName()) + ";" + "\r\n"
		//                                ;
		//                toReturn += "\t\t\t\t\t\t" + "end if; \r\n";
		//            }
		//            first_flag = false;

		//        }
		//    }
		//    toReturn += "\t\t\t\t\t" + "when others =>" + "\r\n";
		//    toReturn += "\t\t\t\t\t\t" + processName + "_st := " + processName + "_" + canvas[current_graph].GetInitialStateName() + ";\r\n";
		//    toReturn += "\t\t\t\t end case; -- endTransitions\r\n\r\n";
		//    toReturn += "\t\t\t end if;" + "\r\n";
		//    toReturn += "\t\t" + "--STATE machine end" + "\r\n";
		//    toReturn += "\t\t" + "END IF; \r\n"
		//                    + "\t\t" + "process_ISR := process_ISR(0) & process_ISR_helper;" + "\r\n"
		//                    + "\t\t" + "process_CNT := process_CNT + 1; " + "\r\n";
		//    toReturn += "\t" + "END IF; \r\n";
		//    toReturn += "\t" + "--clock_div end" + "\r\n";

		//    toReturn += "\t" + "B_o <= B; " + "\r\n";//should change this to be outside the process.  plan to remove B_o
		//    return toReturn;
		//}

		//string printArchVHDL()
		//{
		//    String tempStr = "";
		//    tempStr += String.Format("architecture beh of {0} is", entityName) + "\r\n";
		//    /*insert variables used by architechture*/
		//    //generate list of states
		//    tempStr += "\t" + "type " + processName + "_States is (" + listStateNames() + ");\r\n";
		//    tempStr += "\t" + "signal " + processName + "_stCurrent" + "," + processName + "_stNext" + ": " + processName + "_States := " + getInitState() + "; \r\n";
		//    //code code code
		//    tempStr += "\t" + handleLocalVariables(canvas.GetGlobalCode()).Replace("\r\n", "\r\n \t");
		//    tempStr += "\r\n\t" + "signal NextB : std_logic_vector(7 downto 0) := (others=>'0');" + "\r\n";
		//    tempStr += "\t" + "signal clock2: std_logic:= '0';" + "\r\n";
		//    tempStr += "\t" + "constant isr_OVF: std_logic_vector(31 downto 0) := conv_std_logic_vector(" + get_isr_OVF_VHDL() + ", 32);";

		//    tempStr += "\r\n" + "begin" + "\r\n";
		//    //calles printProcess()
		//    tempStr += printProcessVHDL_FSM();
		//    tempStr += "end beh;" + "\r\n";
		//    //end
		//    return tempStr;
		//}

		/*getVariableNameVHDL() reads the string with the local variable information 
		 * and picks out the variable name
		 * 
		 * @param: none;
		 * @return list<String> - each element is a variable name;
		 */
		//List<String> getVariableNameVHDL()
		//{
		//    //string with local variable information
		//    String tempStr = canvas.GetGlobalCode();
		//    //remove comments.  remove between /* and */      
		//    //remove comments remove between // and new line 
		//    //trim whitespace
		//    tempStr = removeComment0(tempStr);
		//    String[] spl = tempStr.Split(';');//splits based off semi colon
		//    /*get the variable names.  They are between signal/variable/constant and the colon*/
		//    List<String> ls = new List<String>();
		//    foreach (String ss in spl)
		//    {
		//        string s = ss.ToLower().Trim();
		//        if (s == "") continue;
		//        if (s.IndexOf(":") != -1)
		//        {
		//            int left, right;
		//            right = s.IndexOf(":");
		//            if (s.LastIndexOf("signal", right) != -1)
		//            {
		//                left = s.LastIndexOf("signal", right);
		//                left += "signal".Length;
		//                ls.Add(s.Substring(left, right - left).Trim().ToLower());
		//            }
		//            else if (s.LastIndexOf("variable", right) != -1)
		//            {
		//                left = s.LastIndexOf("variable", right);
		//                left += "variable".Length;
		//                ls.Add(s.Substring(left, right - left).Trim().ToLower());
		//            }
		//            else if (s.LastIndexOf("constant", right) != -1)
		//            {
		//                left = s.LastIndexOf("constant", right);
		//                left += "constant".Length;
		//                ls.Add(s.Substring(left, right - left).Trim().ToLower());
		//            }
		//            else
		//            {
		//                left = s.IndexOf(" ");
		//                ls.Add(s.Substring(left, right - left).Trim().ToLower());
		//            }
		//            // Console.WriteLine(right);
		//            //Console.WriteLine(left);
		//            //Console.WriteLine(right - left);
		//            // ls.Add(s.Substring(left, right - left).Trim());
		//        }
		//    }
		//    //add port entries by hard coding it
		//    ls.Add("A".ToLower());
		//    //  ls.Add("clock");
		//      ls.Add("reset".ToLower());
		//      ls.Add("enable".ToLower());
		//    return ls;
		//}

		/*Removes SLASH STAR type comments */
		String removeComment1(String tempStr)
		{
			while (tempStr.IndexOf("/*") != -1 && tempStr.IndexOf("*/") != -1)
			{
				int left, right;
				left = tempStr.IndexOf("/*");
				right = tempStr.IndexOf("*/", left) + 2;

				tempStr = tempStr.Replace(tempStr.Substring(left, right - left), "");
			}
			return tempStr;
		}
		/*Removes SLASH SLASH type comments*/
		String removeComment2(String tempStr)
		{
			int left, right;

			while (tempStr.IndexOf("//") != -1)
			{
				left = tempStr.IndexOf("//");
				if (tempStr.IndexOf("\n", left) != -1)
				{
					right = tempStr.IndexOf("\n", left) + 1;
					tempStr = tempStr.Replace(tempStr.Substring(left, right - left), "");
				}
				else if (tempStr.IndexOf("\n", left) == -1)
				{
					tempStr = tempStr.Remove(tempStr.IndexOf("//"));
				}
			}
			return tempStr;
		}
		String removeComment0(String tempStr)
		{
			tempStr = removeComment1(tempStr);
			tempStr = removeComment2(tempStr);
			tempStr = tempStr.Trim();
			return tempStr;
		}

		//HashSet<String> getTransitionSensitivityList(HashSet<String> SLIST)
		//{
		//    List<String> varStr = getVariableNameVHDL();
		//    // parse RHS to decide what to add to sensitivity list

		//    foreach (Edge e in canvas.edges)// go through actions to figure out sensitivity list //for "<="
		//    {
		//        //get RHS from string
		//        String tempAction = e.GetActions().ToLower();
		//        int curr, left, right;
		//        curr = left = right = 0;
		//        string[] splitAction = tempAction.Split(';');//break up in order to handle one instruction at a time
		//        foreach (string semiAction in splitAction)
		//        {
		//            if (semiAction.Trim() == "") continue;//empty you should skip
		//            if (semiAction.IndexOf("=") == -1) continue;//not valid instruction so don't add to sensitivity list
		//            else if (semiAction.IndexOf("=") != -1)//RHS exists. 
		//            {//if elements of RHS exist in var Str then add it to sensitivity list.
		//                left = semiAction.IndexOf("=");
		//                string subRHS = semiAction.Substring(left);
		//                SLIST = AddRHS2_SensitivityList(subRHS, SLIST);
		//            }
		//        }

		//        //handle condition--each condition will be pretty much one line.
		//        String tempCondition = e.GetCondition().ToLower();
		//        SLIST = AddRHS2_SensitivityList(tempCondition, SLIST);
		//    }
		//    return SLIST;
		//}
		//HashSet<String> getOutputSensitivityList(HashSet<String> SLIST)
		//{
		//    List<String> varStr = getVariableNameVHDL();
		//    // parse RHS to decide what to add to sensitivity list

		//    foreach (Node n in canvas.nodes)// go through actions to figure out sensitivity list //for "<="
		//    {
		//        //get RHS from string
		//        String tempAction = n.GetActions().ToLower();
		//        int curr, left, right;
		//        curr = left = right = 0;
		//        string[] splitAction = tempAction.Split(';');//break up in order to handle one instruction at a time
		//        foreach (string semiAction in splitAction)
		//        {
		//            if (semiAction.Trim() == "") continue;//empty you should skip
		//            if (semiAction.IndexOf("=") == -1) continue;//not valid instruction so don't add to sensitivity list
		//            else if (semiAction.IndexOf("=") != -1)//RHS exists. 
		//            {//if elements of RHS exist in var Str then add it to sensitivity list.
		//                left = semiAction.IndexOf("=");
		//                string subRHS = semiAction.Substring(left);
		//                SLIST = AddRHS2_SensitivityList(subRHS, SLIST);
		//            }
		//        }
		//    }
		//    return SLIST;
		//}


		/*A reimplementation on how to handle C conditions for VHDL
		 * Since everything will be std logic vectors, you will not have to worry about
		 * converting the vars into something types.
		 * 
		 * This function will convert the condition to have the right operands but if 
		 * the relational operands are absent, then this function will output a message
		 * to suggest seting it to a relational opperator.  
		 * Conditional statements in VHDL need a relational operator.  
		 * 
		 */
		string handle_C_Condition(String s)
		{

			if (s.IndexOf("++") != -1 || s.IndexOf("--") != -1) //check if ++/-- exists in action
			{
				//send message indicating that "++" and "--" are not supported in this version
				if (Error_MSG_flag == false)
				{
					Error_MSG_flag = true;
					MessageBox.Show(@"Error: Incremental ( ""++"" ) and Decremental ( ""--"" ) operators are not supported in this version. " + "\r\n"
						+ @"We suggest use of ""var + 1"" or ""var - 1"" as an alternative", "Error");
				}
				return " TRUE ";
			}
            if (s.Trim() == "1")
                s = s.Replace("1", " TRUE ");
            //NOR all the relational operators including " true ".
            if (!(s.Contains(" TRUE ") || s.Contains("=") || s.Contains(">") || s.Contains("<")))
            {
                if (Error_MSG_flag == false)
                {
                    Error_MSG_flag = true;
                    //it will get in here if none of the above are present in the  condition
                    MessageBox.Show("Use relational operators in order to produce a boolean value" + "\r\n"
                        + "Relational operators include: ==, != , >= , <= , > , <    " + "\r\n"
                            + "i.e var != 0xAA ", "Error");
                }
            }
			s = s.Replace("\t", "").Replace("\r\n", "").Replace("\n", "");
			//replace modifiers
			s = s.Replace("==", " = ");
			s = s.Replace("!=", " /= ");
			s = s.Replace("&&", " AND ");
			s = s.Replace("&", " AND ");
			s = s.Replace("||", " OR ");
			s = s.Replace("|", " OR ");
			s = s.Replace("%", " MOD ");
			s = s.Replace("^", " XOR ");
			s = s.Replace("!", " NOT ");
			s = s.Replace("~", " NOT ");
            s = s.Replace(">>", " SRL ");
            s = s.Replace("<<", " SLL ");


			s = handlehex(s);
			return s;
		}

		/*  This function will convert boolean operations of C into VHDL
		 * At this time there is no support for "++" or "--" 
		 * because it is difficult to do in one line in VHDL
		 */
		/* 
		 * string handle_C_Condition(String ss)
		{
			string s = ss;
			if (s.IndexOf("++") != -1 || s.IndexOf("--") != -1) //check if ++/-- exists in action
			{
				//send message indicating that "++" and "--" are not supported in this version
				//
				MessageBox.Show(@"Error: Incremental ( ""++"" ) and Decremental ( ""--"" ) operators are not supported in this version. " + "\r\n"
					+ @"We suggest use of ""var + 1"" or ""var - 1"" as an alternative", "Error");
				return " TRUE ";
			}
			s = s.Replace("\t", "").Replace("\r\n", "").Replace("\n", "");
			//replace modifiers
			s = s.Replace("==", " = ");
			s = s.Replace("!=", " /= ");
			s = s.Replace("&&", " AND ");
			s = s.Replace("&", " AND ");
			s = s.Replace("||", " OR ");
			s = s.Replace("|", " OR ");
			s = s.Replace("%", " MOD ");
			s = s.Replace("^", " XOR ");
			s = s.Replace("!", " NOT ");
			s = s.Replace("~", " NOT ");

			if (s.Trim() == "1")
				s = s.Replace("1", " TRUE ");

			s = handlehex(s);
			 //go through the list of local variables and check to see if the variable is located inside the condition statement.
			 //if it contains it then you may surround it with a std_logic_vector
			foreach (threePiece tp in threePieceSet)
			{
				string varName = tp.varName;
				if (s.Contains(varName))
				{
					//Replace it with a dummy variable like "$" then check the condition again.  when instances of this are no longer there.
					//Turning the multi-letter into a single char makes it easier to manipulate.
					s=s.Replace(varName, "$");
					//----
				while(s.Contains("$"))	//begin loop
				{
					//verify that this is a complete varName by checking if has white space or parenthesise or brackets to the left and right
					int left, right, cursor;
					left = right = cursor = 0;
					cursor = s.IndexOf("$");
					left = cursor - 1;
					right = cursor + 1;

					bool isLeftClear = false;
					bool isRightClear = false;
				
					//check if left is whitespace
					if (left < 0) //assume var is ok to the left since nothing to its left
					{ isLeftClear = true; }
						//if it gets to this condition, left is considered in range
					else if(s[left] == ' ' || s[left] == '('
						|| s[left] == ')' || s[left] == '['
						|| s[left] == ']'|| s[left] == '\t'|| s[left] == '\n')
					{ isLeftClear = true; }
					//check if right is whitespace
					if (right >= s.Length)//assume var is ok to the right since nothing to its right
					{ isRightClear = true; }
						//if it gets to this condition, right is considered in range
					else if (s[right] == ' ' || s[right] == '('
						|| s[left] == ')' || s[left] == '['
						|| s[left] == ']' || s[left] == '\t' || s[left] == '\n')
					{ isRightClear = true; }

					
					if (isRightClear && isLeftClear)//completely correct--this means that the keyword is not a subset
					{
						//replace $ with # to indicate that this is ready to be converted into stdlogic.
						// i.e.  conv_std_logic_vector(# ,32) -- but replace # with the real varName
						//This replace prevents additionaly blips in the other loops.
						//s[cursor] = '#';
						s = s.Remove(cursor,1);
						s = s.Insert(cursor, "#");
					}
					else //partially correct--this means that this keyword is a subset of a larger keyword.
					{ 
						//repalce $ with @ to indicate that this is a subset and that you should replaces this
						//with the original varname in the end.
					//s[cursor] = '@';
						s = s.Remove(cursor, 1);
						s = s.Insert(cursor, "@");
					}
				}	//end loop

					//replaces all "#" with the varname surounded by the conversion
				s = s.Replace("#", "conv_std_logic_vector( "+ varName + " , 32)");
					//replace all "@" with the original varname
					s = s.Replace("@", varName);

				}
			}
			//s = "conv_integer(" + s + ")";


			return s;
		}
*/
		/* helps replaces the short hand with the long hand
		 * "op" should be * or / or + or -
		 */
		String handleShortOperator(String s, String op)
		{
			s = s.Replace(op + "=", "=");
			string[] expander = s.Split('=');//divides it into an array of LHS and RHS
			if (expander.Length == 2)
			{
                //int numbits = 8;
                //foreach (threePiece tp in threePieceSet)
                //{//check if the LHS is in the threepieceset.  if it is then get the numbits. else assume its going to port "B"
                //    if (tp.varName == expander[0].Trim())//expander[0] should be a variable name
                //    {
                //        numbits = tp.numbits;
                //        break;
                //    }
                //}
                ////Should probably handle these conversions outside of this function
                //if (op == "*" || op == "/")
                //    s = string.Format("{0} := conv_std_logic_vector(conv_integer({0}) {2} conv_integer({1}),{3});", expander[0], expander[1].Replace(";", ""), op, numbits);
                //else if (op == "+" || op == "-")
					s = string.Format("{0} = {0} {2} {1}", expander[0], expander[1], op);
			}
			else
			{
				if (Error_MSG_flag == false)
				{
					Error_MSG_flag = true;
					//problem
					MessageBox.Show("Error:  Complex assignment could not be resolved.\r\n Only one assignment operator is allowed per line ", "Error");
					return "";
				}
			}
			return s;
		}

		/*This will change the action statements to be suitable for
		 * a VHDL environment.  It does not support ++ or -- since it
		 * is difficult to convert.
		 */
		String handle_C_Actions(String s)
		{
			s = s.Replace("\t", "").Replace("\r", "").Replace("\n", "");
			//expand shorcut operators
			if (s.IndexOf("+=") != -1)
				s = handleShortOperator(s, "+");
			else if (s.IndexOf("-=") != -1)
				s = handleShortOperator(s, "-");
			else if (s.IndexOf("*=") != -1)
				s = handleShortOperator(s, "*");
			else if (s.IndexOf("/=") != -1)
				s = handleShortOperator(s, "/");
            else if (s.IndexOf("%=") != -1)
                s = handleShortOperator(s, "%");
            else if (s.IndexOf("&=") != -1)
                s = handleShortOperator(s, "&");
            else if (s.IndexOf("^=") != -1)
                s = handleShortOperator(s, "^");
            else if (s.IndexOf("|=") != -1)
                s = handleShortOperator(s, "|");
            else if (s.IndexOf("<<=") != -1)
                s = handleShortOperator(s, "<<");
            else if (s.IndexOf(">>=") != -1)
                s = handleShortOperator(s, ">>");

			//replace modifiers
			if (s.IndexOf("=") != -1)
			{
				string[] expander = s.Split('=');//divide into lhs and RHS
				if (expander.Length > 2)
				{
					if (Error_MSG_flag == false)
					{
						Error_MSG_flag = true;
						//problem
						MessageBox.Show("Error:  Complex assignment could not be resolved.\r\n Only one assignment operator is allowed per line ", "Error");
						return "";
					}
				}
	
				s = s.Replace("=", ":=");
				
			}
			s = s.Replace("&&", " AND ");
			s = s.Replace("&", " AND ");
			s = s.Replace("||", " OR ");
			s = s.Replace("|", " OR ");
			s = s.Replace("%", " MOD ");
			s = s.Replace("^", " XOR ");
			s = s.Replace("!", " NOT ");
			s = s.Replace("~", " NOT ");
            s = s.Replace(">>"," SRL ");
            s = s.Replace("<<"," SLL ");

			if (s.IndexOf("++") != -1 || s.IndexOf("--") != -1) //check if ++/-- exists in action
			{
				if (Error_MSG_flag == false)
				{
					Error_MSG_flag = true;
					//send message indicating that "++" and "--" are not supported in this version
					//suggest that they use x+1
					MessageBox.Show(@"Error: Incremental ( ""++"" ) and Decremental ( ""--"" ) operators are not supported in this version. " + "\r\n"
						+ @"We suggest use of ""var += 1"" or ""var -= 1"" as an alternative", "Error");
					return "";
				}
			}

			s = handlehex(s);
            s = s.Replace(":=","$");//temporarily swap assignment operator with $ for easy splitting;
            s = s.Replace(";", "");//remove semi colon so it will fit in CSLV.  don't worry...it will be back like the terminator.  look below;
            String[] split_line = s.Split('$');
            if (split_line.Length <= 1) //no dollar sign found.  no need to do anything else since no assignment is taking place;
    			return s+";";//the semi colon has returned....
            else
                return string.Format("{0} := CSLV( {1}, {0});", split_line[0], split_line[1]);//place LHS and RHS in the CSLV format
		}
		String handlehex(String s)
		{
			s = s.Replace("0X", "0x");
			//check to see if they are useing hex and replace it appropriately
			if (s.IndexOf("0x") != -1)
			{
				int lefthex, righthex;
				lefthex = righthex = 0;
				s = s.Replace("0x", "$");//replace 0x with a single char to make it easy to parse
				while (s.IndexOf("$") != -1)//loop until all dollarsigns gone so that hex values are set right
				{
					lefthex = s.IndexOf("$");
					righthex = s.IndexOfAny(new char[] { ' ', ';', '(', ')', '[', ']', '{', '}', '+', '-', '/', '*', '>', '<', '=' }, lefthex);//the right side of the hex should either end with a white space or a semi colon
					//valid bounds check
					if (righthex == -1)
					{
						//assume end of string is the end
						righthex = s.Length;
					}
					//move lefthex  so that it excludes the $ 
					lefthex++;
					//in range check.
					if ((righthex - lefthex) > 0)
					{

						string substrhex = s.Substring(lefthex, righthex - lefthex);
						string vhdlhex = string.Format("x" + "\"{0}\"", substrhex);// if substrhex is "AA" , it should output x"AA"
						s = s.Replace("$" + substrhex, vhdlhex);
					}
					else
					{
						//problem
						s = s.Replace("0x", "x" + "\"00\"");
					}

				}
			}
			//else its integer or binary
			return s;
		}
		//String handle_VHDL_Conditions(String vCon)
		//{
		//    if (vCon.Trim() == "1")
		//    {
		//        return "TRUE";
		//    }
		//    else if (vCon.Trim() == "0")
		//    {
		//        return "FALSE";
		//    }
		//    return vCon;
		//}
		//String handle_VHDL_Actions(String vAct)
		//{
		//    string newString = "";
		//    //split the string up
		//    vAct = removeComment0(vAct);

		//    String[] splitAction = vAct.Split(';');
		//    //append to the front of LHS the word "next"
		//    foreach (string semiAction in splitAction)
		//    {
		//        if (semiAction.Trim() == "") continue;
		//        newString += "Next" + semiAction.Trim() + ";\r\n";
		//    }

		//    return newString;
		//}
		/*checks entityname, state name prefix, and period to see if it had valid input
		 *Valid input returns true.
		 * invalid or undefined input returns false
		 */
		bool AllFSMInputsValid()
		{
			return
				periodIsValid() &&
				entityNameIsValid() &&
				prefixIsValid()
				;
		}
		bool prefixIsValid()
		{
			foreach (Graph f in canvas)
			{
				if (f.GetAbbrv().Trim() == "")//needs process name
				{
					if (Error_MSG_flag == false)
					{
						Error_MSG_flag = true;
						MessageBox.Show("Error: Must have an prefix name", "Invalid prefix");
					}
					//give default
					return false;
				}
			}
			return true;
		}
		bool entityNameIsValid()
		{
			if (entityName.Trim() == "")//needs entity name
			{
				if (Error_MSG_flag == false)
				{
					Error_MSG_flag = true;
					MessageBox.Show("Error: Must have an entity name", "Invalid entity name");
				}
				//give default
				return false;
			}
			return true;
		}
		bool periodIsValid()
		{
			foreach (Graph f in canvas)
			{
				string tempstr = removeWhiteSpace(f.GetPeriod());
				bool foundADecimal = false;
				//period must be 1 or greater and must be a whole number
				foreach (char c in tempstr)
				{
					if (c < '0' || c > '9')//don't allow non number character
					{
						//allow one decimal
						if (c == '.')
						{
							if (foundADecimal == false)//detects first decimal
							{
								foundADecimal = true;
								continue;
							}
							else //detects multiple decimals
							{//do nothing just let it go to the return false below
							}
						}
						if (Error_MSG_flag == false)
						{
							Error_MSG_flag = true;
							MessageBox.Show("Error: Cannot allow non-number characters in period.\r\n", "Invalid Period");
						}
						return false;
					}
				}
			}
			return true;
		}
		//------------------------------------
		public struct threePiece
		{
			public CdataTypes dataType;
			public string varName, RHS;
			public int numbits;
		};

		public enum CdataTypes
		{
			VHDL_V,//this one isn't a C data Type.  if detected, it should be used as a way to generate non-C sysntax correctly
			VHDL_C,//this one isn't a C data Type.  if detected, it should be used as a way to generate non-C sysntax correctly
			SHORTINT,
			SIGNEDSHORTINT,
			UNSIGNEDSHORTINT,
			INT,
			SIGNEDINT,
			UNSIGNEDINT,
			LONGINT,
			SIGNEDLONGINT,
			UNSIGNEDLONGINT,
			CHAR,
			SIGNEDCHAR,
			UNSIGNEDCHAR
		};
		/*pushes primative data types into a threePiece.  
		 * Primative datatypes include: ints and chars */
		threePiece handleprimativeData(string inst, CdataTypes cdt)
		{
			threePiece temp3p = new threePiece();
			temp3p.dataType = cdt;
			temp3p.numbits = getNumbitsOfVariable(cdt);			//set numbits
			int left, right;
			left = string.Format("{0}", cdt).Length;
			if (inst.IndexOf("=") != -1)//declaraiont w/ instantiation.
			{
				right = inst.IndexOf("=");
				temp3p.RHS = inst.Substring(right + 1, inst.Length - (right + 1));//set RHS
				if (temp3p.RHS.IndexOf("0x") != -1 || temp3p.RHS.IndexOf("0X") != -1) //hex exists 
					temp3p.RHS = handlehex(temp3p.RHS);
				else //hex not detected
					temp3p.RHS = string.Format(" conv_std_logic_vector( {0}, {1} )", temp3p.RHS.Trim(), temp3p.numbits);
			}
			else//declaration w/o instantiation
			{
				right = inst.Length;
				temp3p.RHS = "(others =>'0')";//set RHS
			}
			temp3p.varName = inst.Substring(left, right - left);//set variable name
			return temp3p;
		}
		/*threePiece handleFloatingPoint()
		{ }
		threePiece handleStruct() 
		{ }
		*/



		/*takes in the local variable string.  removes the comments and then places
		 * its information onto a a global hashset.
		 */
		HashSet<threePiece> makeHashSet(String ss)
		{
			string s = ss;
			//maybe add  code to deal with "#defines..." aka constants//low priority;
			HashSet<threePiece> tempTPS = new HashSet<threePiece>();
			s = removeComment0(s.ToLower());
			s = s.Replace("static", "").Replace("\r", "").Replace("\n", "").Replace("\t", "");//remove whitespace
			string[] instructionArr = s.Split(';');

			foreach (string M_inst in instructionArr) // analyze each instruction one by one
			{
				string inst = M_inst.Replace(" ", "");
				bool is_this_line_known = false;
				if (inst == "") continue;//CHECK NEXT ENTRY IN ARRAY;
				//check to see if it is valid C syntax
				if (inst.StartsWith("signal") || inst.StartsWith("variable") ||
					 inst.StartsWith("sharedvariable") || inst.StartsWith("constant"))
				{
					is_this_line_known = true;
					if (inst.IndexOf("std_logic") == -1)
					{
						if (Error_MSG_flag == false)
						{
							Error_MSG_flag = true;
							//tell user that only std_logic and std_logic_vector is supported
							MessageBox.Show("Error: Please use std_logic or std_logic_vector \r\n Other Data Types are not yet supported", "Error");
						}
						break;
					}
					tempTPS = appendVHDL_Variables(tempTPS, inst);

				}
				//----------------------check to see if its a C data type;
				CdataTypes cdt = 0;
				int cdt_size = Enum.GetNames(typeof(CdataTypes)).Length;
				for (int k = 0; k < cdt_size; ++k, ++cdt)
				{
					string cdtSTR = string.Format("{0}", cdt).ToLower();
					if (inst.StartsWith(cdtSTR))
					{
						is_this_line_known = true;
						threePiece temp3p = handleprimativeData(inst, cdt);
						tempTPS.Add(temp3p);
					}
				}
				if (is_this_line_known == false)//save line and place it in somewhere to be reprinted later
				{
					//if (WARNING_MSG_FLAG == false) {
					//	WARNING_MSG_FLAG = true;
                     //   string Warning_MSG = string.Format("Warning:  We have found unsupported syntax in the Variables \r\n\t Text Box in state machine with prefix" + processName + ". \r\n\t We will leave it unmodified when generating VHDL code.");
					//	MessageBox.Show(Warning_MSG,"Warning");
					//}
					unknownStrings.Add(M_inst); 
				}
			}
			return tempTPS;
		}

		HashSet<threePiece> getHashSet()
		{
			return threePieceSet;
		}

		string printHashSetWithFormating(bool isGlobal)
		{
			string ReturnValue = "";
			foreach (threePiece t3 in threePieceSet)
			{
				if (t3.dataType == CdataTypes.VHDL_C)
					ReturnValue += string.Format("CONSTANT {0}: {2}:= {1} ;\r\n", t3.varName, t3.RHS, handleSTD_LOGIC_VECTOR(t3));
				else
					ReturnValue += string.Format("{3}VARIABLE {0}: {2}:= {1} ;\r\n", t3.varName, t3.RHS, handleSTD_LOGIC_VECTOR(t3), (isGlobal)? "SHARED ": "");

			}
			foreach (string str in unknownStrings)//print unknownStrings
				ReturnValue += str + ";\r\n";
			unknownStrings.Clear();//clear it for the next time it is used

			return ReturnValue;
		}
		//string printGlobalHashSetWithFormating()
		//{
		//    string ReturnValue = "";
		//    foreach (threePiece t3 in globalThreePieceSet)
		//    {
		//        if (t3.dataType == CdataTypes.VHDL_C)
		//            ReturnValue += "\t" + string.Format("CONSTANT {0}: {2}:= {1} ;\r\n", t3.varName, t3.RHS, handleSTD_LOGIC_VECTOR(t3));
		//        else
		//            ReturnValue += "\t" + string.Format("SHARED VARIABLE {0}: {2}:= {1} ;\r\n", t3.varName, t3.RHS, handleSTD_LOGIC_VECTOR(t3));
		//    }
		//    return ReturnValue;
		//}

		string printHashSetWithOUTFormating()
		{
			string ReturnValue = "";
			foreach (threePiece t3 in threePieceSet)
			{
				//	//Console.WriteLine("{0}, {1}, {2}", t3.dataType, t3.varName, t3.RHS);
				ReturnValue += string.Format("{0}, {1}, {2}\r\n", t3.dataType, t3.varName, t3.RHS);
			}
			return ReturnValue;
		}

		string handleSTD_LOGIC_VECTOR(threePiece t3)
		{
			string toReturn = "";
			int numbits = t3.numbits;
			if (numbits == -1)//appendVHDLvariables() sets numbits of this threePiece to -1 to make it appear to be std_logic
				toReturn = "STD_LOGIC";
			else
				toReturn = string.Format("STD_LOGIC_VECTOR({0} downto 0)", numbits - 1);
			return toReturn;
		}
		int getNumbitsOfVariable(CdataTypes cdt)
		{
			int numbits;
			//if (CdataTypes.CHAR == cdt ||
			//            CdataTypes.SIGNEDCHAR == cdt ||
			//            CdataTypes.UNSIGNEDCHAR == cdt) { numbits = 8; }
			//else if (CdataTypes.SHORTINT == cdt ||
			//            CdataTypes.SIGNEDSHORTINT == cdt ||
			//            CdataTypes.UNSIGNEDSHORTINT == cdt) { numbits = 16; }
			//else if (CdataTypes.INT == cdt ||
			//            CdataTypes.SIGNEDINT == cdt ||
			//            CdataTypes.UNSIGNEDINT == cdt) { numbits = 32; }
			//else if (CdataTypes.LONGINT == cdt ||
			//            CdataTypes.SIGNEDLONGINT == cdt ||
			//            CdataTypes.UNSIGNEDLONGINT == cdt) { numbits = 64; }
			//else numbits = bitWidth;
			switch (cdt)
			{
				case CdataTypes.CHAR:
				case CdataTypes.UNSIGNEDCHAR:
				case CdataTypes.SIGNEDCHAR:
					numbits = 8;
					break;
				case CdataTypes.SHORTINT:
				case CdataTypes.SIGNEDSHORTINT:
				case CdataTypes.UNSIGNEDSHORTINT:
					numbits = 16;
					break;
				case CdataTypes.INT:
				case CdataTypes.SIGNEDINT:
				case CdataTypes.UNSIGNEDINT:
					numbits = 32;
					break;
				case CdataTypes.LONGINT:
				case CdataTypes.SIGNEDLONGINT:
				case CdataTypes.UNSIGNEDLONGINT:
					numbits = 64;
					break;
				default: numbits = bitWidth; break;
			}
			return numbits;
		}
		//------------------------------------

		/*for VHDL not C
		This function should looks at the given string and compares it against each entry
		in the localvariable list.  if the string contains the same element as in the local variable
		list then it will be concatenated to the given hash set.  This function is smart enough to
		tell distinguesh reading "var1" and "var2" and "var"  Even though all have the same substring"var"
		this function can tell these appart.
	   param@ s - this is the RHS.  
	   param@ HS- this is the hashset you are appending.
	   return@ will return true
		 */
		//private HashSet<string> AddRHS2_SensitivityList(string s, HashSet<string> HS)
		//{
		//    List<string> var = getVariableNameVHDL();
		//    foreach (string tp in var)
		//    {
		//        string varName = tp;
		//        if (s.Contains(varName))
		//        {
		//            //Replace it with a dummy variable like "$" then check the condition again.  when instances of this are no longer there.
		//            //Turning the multi-letter into a single char makes it easier to manipulate.
		//            s = s.Replace(varName, "$");
		//            //----
		//            while (s.Contains("$"))	//begin loop
		//            {
		//                //verify that this is a complete varName by checking if has white space or parenthesise or brackets to the left and right
		//                int left, right, cursor;
		//                left = right = cursor = 0;
		//                cursor = s.IndexOf("$");
		//                left = cursor - 1;
		//                right = cursor + 1;

		//                bool isLeftClear = false;
		//                bool isRightClear = false;

		//                //check if left is whitespace
		//                if (left < 0) //assume var is ok to the left since nothing to its left
		//                { isLeftClear = true; }
		//                //if it gets to this condition, left is considered in range
		//                else if (s[left] == ' ' || s[left] == '('
		//                    || s[left] == ')' || s[left] == '['
		//                    || s[left] == ']' || s[left] == '\t' || s[left] == '\n')
		//                { isLeftClear = true; }
		//                //check if right is whitespace
		//                if (right >= s.Length)//assume var is ok to the right since nothing to its right
		//                { isRightClear = true; }
		//                //if it gets to this condition, right is considered in range
		//                else if (s[right] == ' ' || s[right] == '('
		//                    || s[right] == ')' || s[right] == '['
		//                    || s[right] == ']' || s[right] == '\t' || s[right] == '\n')
		//                { isRightClear = true; }


		//                if (isRightClear && isLeftClear)//completely correct--this means that the keyword is not a subset
		//                {
		//                    //replace $ with # to indicate that this is ready to be converted into stdlogic.
		//                    // i.e.  conv_std_logic_vector(# ,32) -- but replace # with the real varName
		//                    //This replace prevents additionaly blips in the other loops.
		//                    //s[cursor] = '#';
		//                    s = s.Remove(cursor, 1);
		//                    s = s.Insert(cursor, "#");

		//                    HS.Add(varName);//add RHS variable to HashSet
		//                }
		//                else //partially correct--this means that this keyword is a subset of a larger keyword.
		//                {
		//                    //repalce $ with @ to indicate that this is a subset and that you should replaces this
		//                    //with the original varname in the end.
		//                    //s[cursor] = '@';

		//                    s = s.Remove(cursor, 1);
		//                    s = s.Insert(cursor, "@");
		//                }
		//            }	//end loop

		//            //       //replaces all "#" with the varname surounded by the conversion
		//            //  s = s.Replace("#", "conv_std_logic_vector( "+ varName + " , 32)");

		//            //     //replace all "@" with the original varname

		//            //restoring original string
		//            s = s.Replace("@", varName).Replace("#", varName);
		//        }
		//    }
		//    return HS;
		//}

		/*The purpose of this function is to fulfil the current/next paradign by doubling
		 * The user input for the local variables.  It will replace the given signal with its twin.
		 * 
		 * i.e.  
		 *Input: signal counter: std_logic_vector(7 downto 0);
		 **** "counter" is replaced with "NextCounter"
		 *Result: signal counter, NextCounter : std_logic_vector(7 downto 0);
		 */
		//private string handleLocalVariables(String Lvar)
		//{
		//    string newLvar = "";
		//    string TrimmedSTR = "";
		//    string varSub = "";
		//    int left, right;
		//    left = right = 0;
		//    //split based on semi colon
		//    Lvar = removeComment0(Lvar);
		//    string[] splitLvar = Lvar.Split(';');
		//    foreach (string semiSplit in splitLvar)
		//    {
		//        //locate colon and the beginning sequence and get remove
		//        //the subset that is the var.  repalce it with the current/next paradigm
		//        TrimmedSTR = (semiSplit.Trim()).ToLower();
		//        if (TrimmedSTR == "") continue;
		//        if (TrimmedSTR.StartsWith("signal"))
		//        {
		//            if (TrimmedSTR.IndexOf(":") != -1)
		//            {
		//                left = "signal".Length;//gets the index right after the word "signal"
		//                right = TrimmedSTR.IndexOf(":");
		//                //get the variable
		//                varSub = (TrimmedSTR.Substring(left, right - left)).Trim();
		//                newLvar += (TrimmedSTR.Remove(left, right - left)).Insert(left, " " + varSub + " , Next" + varSub + " ") + "; \r\n";
		//            }
		//        }
		//        else if (TrimmedSTR.StartsWith("variable"))
		//        {
		//            if (TrimmedSTR.IndexOf(":") != -1)
		//            {
		//                TrimmedSTR = TrimmedSTR.Replace("variable", "shared variable");
		//                left = "shared variable".Length;//gets the index right after the word "signal"
		//                right = TrimmedSTR.IndexOf(":");
		//                //get the variable
		//                varSub = (TrimmedSTR.Substring(left, right - left)).Trim();
		//                newLvar += (TrimmedSTR.Remove(left, right - left)).Insert(left, " " + varSub + " , Next" + varSub + " ") + "; \r\n";
		//            }
		//        }
		//        else if (TrimmedSTR.StartsWith("constant"))
		//        {
		//            if (TrimmedSTR.IndexOf(":") != -1)
		//            {
		//                left = "constant".Length;//gets the index right after the word "signal"
		//                right = TrimmedSTR.IndexOf(":");
		//                //get the variable
		//                varSub = (TrimmedSTR.Substring(left, right - left)).Trim();
		//                newLvar += (TrimmedSTR.Remove(left, right - left)).Insert(left, " " + varSub + " , Next" + varSub + " ") + "; \r\n";
		//            }
		//        }
		//        else if (TrimmedSTR.StartsWith("shared"))
		//        {
		//            TrimmedSTR = (TrimmedSTR.Replace("shared", "")).Trim();
		//            if (TrimmedSTR.StartsWith("variable"))
		//            {
		//                if (TrimmedSTR.IndexOf(":") != -1)
		//                {
		//                    TrimmedSTR = TrimmedSTR.Replace("variable", "shared variable");
		//                    left = "shared variable".Length;//gets the index right after the word "signal"
		//                    right = TrimmedSTR.IndexOf(":");
		//                    //get the variable
		//                    varSub = (TrimmedSTR.Substring(left, right - left)).Trim();
		//                    newLvar += (TrimmedSTR.Remove(left, right - left)).Insert(left, " " + varSub + " , Next" + varSub + " ") + "; \r\n";
		//                }
		//            }
		//        }
		//    }
		//    return newLvar;
		//}

		/* This function will use the clockrate of the device (default is 50Mhz)
		 * And it will use the given period to produce the number that the device must count up to
		 * in order TICK once every period.
		 * example
		 * "(((50000000/1000)*1000)/2"  = "(((clockrate/1000)*period)/2"
		 * OR
		 * clockrate/(1/(period/1000))/2
		 * 
		 * if timer is disabled, it will return 2 which will tell the micro controller to run
		 * as fast as it can which in this case is half the clock rate.  (2 was chosen instead of 1
		 * because 1 would not function properly with the clock divider.)
		 * 
		 */
		int get_isr_OVF_VHDL()
		{
			//timer enabled
			double clockrate = Convert.ToDouble(getFpgaClockRate());
			double periodIn_ms = Convert.ToDouble(getPeriod());
			double periodIn_sec = periodIn_ms / 1000.0;
			//double freq = 1.0 / periodIn_sec;
			//double isr_OVF_value = clockrate / freq / 2.0;
			double isr_OVF_value = (periodIn_sec * clockrate) / 2.0;
			int ist_OVF_int = Convert.ToInt32(isr_OVF_value);
			if (ist_OVF_int <= 1 || enableTimer == false) //happens if result tries to be faster then your system
				return 1;//return fastest possible for your system
			return (ist_OVF_int);
		}


		/* given a number, it finds out how many bits it will need
			* i.e. 
		 *  To represent the number 8 in binary you need 4 bits (1000)
		 *  
		 * numbits = 4
		 *  
		 * std_logic_vector( numbits -1 downto 0);
		 */
		int getNumbitsFromNumber(int num)
		{
			int i = 0;
			for (; num > 0; ++i)
				num = num >> 1;
			return i;
		}
		/*Calculates the number of bits needed by the process_OVF.
		 *if the timer is disabled then it will return 1 to make the device run as fast as it can.
		 * 
		 */
		int getNumbitsOVF()
		{
			if (enableTimer == false)
				return 2;
			return getNumbitsFromNumber(get_isr_OVF_VHDL());
		}

		string printPES_Clock_Entity(int max_counter)
		{
			return
                //"--------------------------------------------------------------------------" + "\r\n" +
                //"-- Module Name:    PES_clock - Behavioral" + "\r\n" +
                //"--------------------------------------------------------------------------" + "\r\n" +
                //"library IEEE;" + "\r\n" +
                //"use IEEE.STD_LOGIC_1164.ALL;" + "\r\n" +
                //"use ieee.std_logic_arith.all;" + "\r\n" +
                //"use ieee.std_logic_unsigned.all;" + "\r\n" +
                //"\r\n" +
                //"entity PES_clock is" + "\r\n" +
                //"\t" + "generic (max_cnt: natural:= 500000); -- max_cnt = (period * clock_in_speed)/2" + "\r\n" +
                //"\t" + "Port ( clock_in : in  STD_LOGIC;" + "\r\n" +
                //"\t" + "\t" + "clock_out : out  STD_LOGIC);" + "\r\n" +
                //"\t" + "end PES_clock;" + "\r\n" +
                //"architecture Behavioral of PES_clock is" + "\r\n" +
                //"begin" + "\r\n" +
				"\t" + processName + "_clk: process(clock)" + "\r\n" +
                "\t\t" + "constant max_cnt: Integer:= " + max_counter + ";\r\n" +
				"\t\t" + "variable clk_cnt: Integer range 0 to max_cnt := 0;" + "\r\n" +
				"\t\t" + "variable clock_signal: std_logic:= '0';" + "\r\n" +
				"\t" + "begin" + "\r\n" +
				"\t\t" + "if(clock= '1' and clock'event) then" + "\r\n" +
				"\t\t" + "\t" + "clk_cnt := clk_cnt + 1;" + "\r\n" +
				"\t\t" + "\t" + "if (clk_cnt >= max_cnt) then" + "\r\n" +
				"\t\t" + "\t" + "\t" + "clock_signal := not clock_signal;" + "\r\n" +
				"\t\t" + "\t" + "\t" + "clk_cnt := 0;" + "\r\n" +
				"\t\t" + "\t" + "end if;" + "\r\n" +
				"\t\t" + processName + "_clock <= clock_signal;" + "\r\n" +
				"\t\t" + "end if;" + "\r\n" +
				"\t" + "end process;" + "\r\n" +
				//"end Behavioral;" + "\r\n" +
				"--------------------------------------------------------------------------" + "\r\n"
				;
		}
		string convert_complete_C_action2VHDL_by_translating_it_line_by_line(string temp)
		{
			string fullAction = "";
			temp = temp.Replace(";", ";$");//adding dollar sign for easy splitting;
			string[] tempArr = temp.Split('$');//use dollar sign to split up string
			foreach (string semiAction in tempArr)
			{
				if (removeWhiteSpace(semiAction) == "")
					continue;

                if (semiAction.IndexOf(":=") != -1 || semiAction.IndexOf("<=") != -1) //found a vhdl line
                    fullAction += "\t\t\t\t\t\t" + semiAction.Replace("<=", ":=").Replace("\t", "").Replace("\r", "").Replace("\n", "") + "\r\n";                       
                else //found C line
                    fullAction += "\t\t\t\t\t\t" + handle_C_Actions(semiAction) + "\r\n";
			}
			return fullAction;
		}

		HashSet<threePiece> appendVHDL_Variables(HashSet<threePiece> hs, string inst)
		{
			CdataTypes cdt;
			string RHS;
			int left, right, numbits = 0;
			if (inst.StartsWith("constant"))
				cdt = CdataTypes.VHDL_C;
			else
				cdt = CdataTypes.VHDL_V;
			inst = inst.Replace("sharedvariable", ""); inst = inst.Replace("variable", "");
			inst = inst.Replace("signal", ""); inst = inst.Replace("constant", "");
			//check numbits
			switch (inst.Contains("std_logic_vector"))
			{
				case false: //does not contain std_logic_vector therefore it must be a regular std_logic
					numbits = -1;  //using -1 to represent an std_logic
					break;
				case true: //contains std_logic_vector
					right = inst.IndexOf("downto");
					if (right == -1) // detected SLV but no downto
						goto BITWIDTH_ERROR;
					//downto found
					left = inst.LastIndexOf("(", right);
					if (left == -1)
						goto BITWIDTH_ERROR;
					left++;// left is placed right after the open parentheses thats why it is incremented
					if ((right - left) == 0)
						goto BITWIDTH_ERROR;
					///////////////EXTRACT NUMBITS/////////
					numbits = System.Convert.ToInt32(inst.Substring(left, right - left));
					//////////////
					break;
				BITWIDTH_ERROR:
					if (Error_MSG_flag == false)
					{
						Error_MSG_flag = true;
						MessageBox.Show("Error:  std_logic_vectors must be given a bitwidth \r\n i.e. std_logic_vector(7 downto 0)", "Syntax Error");
					}
				return hs;//  THIS RETURNS THE original unmodified...Untouched by man
			}
			//check rhs
			right = inst.IndexOf(":=");
			switch (right)
			{
				case -1://user did not give a value
					RHS = (numbits == -1) ? " '0' ":" (others => '0') ";
					break;
				default:// user gave a value
					if (right + 2 >= inst.Length || right < 0)//check to see if "right" is out of bounds
						goto case -1;
					RHS = inst.Substring(right + 2, inst.Length - (right + 2));
					break;
			}
			//grab var names.  they might be separated by commas.
			threePiece t3 = new threePiece();
			left = 0;//the signal or variable key word was removed, so left should be the first index
			right = inst.IndexOf(":std_logic"); if (right == -1) goto RETURN_STUFF;
			string[] varnames = (inst.Substring(left, right - left)).Split(',');
			foreach (string vn in varnames)
			{
				if (vn.Trim() == "") continue;
				t3.varName = vn.Trim();
				t3.RHS = RHS;
				//std_logic will not be incremented by one, that way it will keep the  -1 flag.  
				//if it is an stdlogicvector, then numbits must be incremented by 1 because the 
				//left most bit index will be one less then the total number of positions. 
				//i.e.  arrays of size 8 go from 7 to 0 
				t3.numbits = numbits + ((numbits == -1)? 0: 1);
				t3.dataType = cdt;
				hs.Add(t3);
			}
		RETURN_STUFF: return hs;
		}
	}
}