//
//  Parse1.cpp
//  Hack_Assembler
//
//  Created by Derrick Ho on 11/25/12.
//  Copyright (c) 2012 Derrick Ho. All rights reserved.
//

#include "Parse1.h"

parse1::parse1(){
	hash["@SP"] = 0;
	hash["@LCL"] = 1;
	hash["@ARG"] = 2;
	hash["@THIS"] = 3;
	hash["@THAT"] = 4;
	hash["@R0"] = 0;
	hash["@R1"] = 1;
	hash["@R2"] = 2;
	hash["@R3"] = 3;
	hash["@R4"] = 4;
	hash["@R5"] = 5;
	hash["@R6"] = 6;
	hash["@R7"] = 7;
	hash["@R8"] = 8;
	hash["@R9"] = 9;
	hash["@R10"] = 10;
	hash["@R11"] = 11;
	hash["@R12"] = 12;
	hash["@R13"] = 13;
	hash["@R14"] = 14;
	hash["@R15"] = 15;
	hash["@SCREEN"] = 16384;
	hash["@KBD"] = 24576;
	//hash["@-1"] = 0x0FFFF;
	
	comp_table["0"] = (int)strtoul("0101010", NULL, 2);
	comp_table["1"] = (int)strtoul("0111111", NULL, 2);
	comp_table["-1"] = (int)strtoul("0111010", NULL, 2);
	comp_table["D"] = (int)strtoul("0001100", NULL, 2);
	comp_table["A"] = (int)strtoul("0110000", NULL, 2);
	comp_table["!D"] = (int)strtoul("0001101", NULL, 2);
	comp_table["!A"] = (int)strtoul("0110001", NULL, 2);
	comp_table["-D"] = (int)strtoul("0001111", NULL, 2);
	comp_table["-A"] = (int)strtoul("0110011", NULL, 2);
	comp_table["D+1"] = (int)strtoul("0011111", NULL, 2);
	comp_table["A+1"] = (int)strtoul("0110111", NULL, 2);
	comp_table["D-1"] = (int)strtoul("0001110", NULL, 2);
	comp_table["A-1"] = (int)strtoul("0110010", NULL, 2);
	comp_table["D+A"] = (int)strtoul("0000010", NULL, 2);
	comp_table["D-A"] = (int)strtoul("0010011", NULL, 2);
	comp_table["A-D"] = (int)strtoul("0000111", NULL, 2);
	comp_table["D&A"] = (int)strtoul("0000000", NULL, 2);
	comp_table["D|A"] = (int)strtoul("0010101", NULL, 2);
	comp_table["M"] = (int)strtoul("1110000", NULL, 2);
	comp_table["!M"] = (int)strtoul("1110001", NULL, 2);
	comp_table["-M"] = (int)strtoul("1110011", NULL, 2);
	comp_table["M+1"] = (int)strtoul("1110111", NULL, 2);
	comp_table["M-1"] = (int)strtoul("1110010", NULL, 2);
	comp_table["D+M"] = (int)strtoul("1000010", NULL, 2);
	comp_table["D-M"] = (int)strtoul("1010011", NULL, 2);
	comp_table["M-D"] = (int)strtoul("1000111", NULL, 2);
	comp_table["D&M"] = (int)strtoul("1000000", NULL, 2);
	comp_table["D|M"] = (int)strtoul("1010101", NULL, 2);
	
	dest_table["null"] = (int)strtoul("000", NULL, 2);
	dest_table["M"] = (int)strtoul("001", NULL, 2);
	dest_table["D"] = (int)strtoul("010", NULL, 2);
	dest_table["MD"] = (int)strtoul("011", NULL, 2);
	dest_table["A"] = (int)strtoul("100", NULL, 2);
	dest_table["AM"] = (int)strtoul("101", NULL, 2);
	dest_table["AD"] = (int)strtoul("110", NULL, 2);
	dest_table["AMD"] = (int)strtoul("111", NULL, 2);
	
	jump_table["null"] = (int)strtoul("000", NULL, 2);
	jump_table["JGT"] = (int)strtoul("001", NULL, 2);
	jump_table["JEQ"] = (int)strtoul("010", NULL, 2);
	jump_table["JGE"] = (int)strtoul("011", NULL, 2);
	jump_table["JLT"] = (int)strtoul("100", NULL, 2);
	jump_table["JNE"] = (int)strtoul("101", NULL, 2);
	jump_table["JLE"] = (int)strtoul("110", NULL, 2);
	jump_table["JMP"] = (int)strtoul("111", NULL, 2);
}

void parse1::to_hack_bin(){
	int i = 0;
	int print_num = 0;
	for (list<string>::iterator it = linked_list.begin(); it != linked_list.end(); ++it , ++i  ) {
		if( it->find("@") != string::npos ){
			print_num = (handle_A(*it ));
		}else if (it->find(";") != string::npos) {
			print_num = (handle_J(*it ));
		}else if (it->find("=") != string::npos) {
			print_num = (handle_C(*it ));
		}else {
			cout << "unknown command at line: " << *it << endl;
			break;
		}
		//to print or not to print
		if(print_num >= 0){
			cout <<bitset<BITWIDTH>(print_num) << endl;
		}else{
			cout <<"command Error on line : " << *it << endl;
			break;
		}
	}
}
int  parse1::handle_A(const string& str){
	map<string,size_t>::iterator m = hash.find(str);
	if (m == hash.end() ) {
		//check if it is a number
		for (int i = 1; i < str.size(); ++i ) {
			if(str[i] >= '0' && str[i] <= '9'){ continue;}
			else if (str[1] == '-' || str[1] == '#') {continue;}
			else {
				//else it is a variable
				static int var_place = 15;
				++var_place;
				hash[str] = var_place;
				return var_place;
			}
		}
		//char n_str[str.size()-1];
		int n =
		(str[1] == '#')?
		(uint16_t)strtoul(str.substr(2).c_str(), NULL , 16)
		:(uint16_t)strtoul(str.substr(1).c_str(), NULL , 10);
		
		return(n);
	}else{//element is found so return binary
		return ((int)m->second);
	}
}
int  parse1::handle_C(const string& str){
	static char  Left_margin = 0x07; //3 bits
	static char  comp= 0x00; //7 bits
	static char  dest = 0x00; //3 bits
	static char  jump = 0x00; //3 bits
	static int concat_num = 0;
	string left_str =
	(str.find("="))? str.substr(0, str.find("="))
	: "null";
	dest_table_it = dest_table.find(left_str);
	comp_table_it = comp_table.find(str.substr(str.find("=")+1));
	if (comp_table_it == comp_table.end()
		|| dest_table_it == dest_table.end()) {
		return -1;
	}else{
		comp = comp_table_it->second;
		dest = dest_table_it-> second;
		concat_num= 0;
		concat_num |= Left_margin; concat_num <<= 7;
		concat_num |= comp; concat_num <<= 3;
		concat_num |= dest; concat_num <<= 3;
		concat_num |= jump;
		return concat_num;
	}
}
int  parse1::handle_J(const string& str){
	static char  Left_margin = 0x07; //3 bits
	static char  comp= 0x00; //7 bits
	static char  dest = 0x00; //3 bits
	static char  jump = 0x00; //3 bits
	static int concat_num = 0;
	string left_str =
	(str.find(";"))? str.substr(0, str.find(";"))
	: "0";
	comp_table_it = comp_table.find(left_str);
	jump_table_it = jump_table.find(str.substr(str.find(";")+1));
	if (comp_table_it == comp_table.end()
		|| jump_table_it == jump_table.end()) {
		return -1;
	}else{
		comp = comp_table_it->second;
		jump = jump_table_it-> second;
		concat_num= 0;
		concat_num |= Left_margin; concat_num <<= 7;
		concat_num |= comp; concat_num <<= 3;
		concat_num |= dest; concat_num <<= 3;
		concat_num |= jump;
		return concat_num;
	}
}
size_t parse1::insert(const string & str){
	string t_str = remove_white( remove_comments(str));
	if (isLabel(t_str)) {
		makeSymbol(t_str);
		return linked_list.size();
	}else if(is_at(t_str)){
		makeSplit(t_str);
		return linked_list.size();
	}
	if (t_str == "") { return linked_list.size();}
	else {linked_list.push_back(t_str);}
	return linked_list.size();
}
bool parse1::is_at(const string & str){
	return (str[0] == '@')? true: false;
}
/*if an A instruction and a C-instr are on the same line, then split it so that they both get their own line in binary
 ie.
 @7,D=A
 
 becomes 
 @7
 D=A
 */
void parse1::makeSplit(const string & str){
	int sp = (int)str.find(",");
	if(sp == string::npos) {linked_list.push_back(str);}
	else {
		linked_list.push_back(str.substr(0,sp));
		if(str.length()-1 == sp) return;
		else linked_list.push_back(str.substr(sp+1));
	}
}
string parse1::makeSymbol(const string & str){
	int left = (int)str.find("(");
	int right = (int)str.find(")");
	string t_str = "@";
	t_str += str.substr(left+1, right - left -1);
	hash[t_str] = linked_list.size();
	if (str.size()-1 != right){
		string x_string = str.substr(right+1);
		insert(x_string);
	}
	return t_str;
}
bool parse1::isLabel(const string & str){
	return (str[0] == '(')? true: false;
}
string parse1::remove_white(const string & str){
	string t_str = "";
	for (int i = 0; i < str.size(); ++i ) {
		if (str[i] == ' ' || str[i] == '\t' ||
			str[i] == '\r' || str[i] == '\n') {
			continue;
		}
		t_str += str[i];
	}
	return t_str;
}
/*if a comment slash slash is found, then it will
 print everything before the comment
 else, it will print the whole string*/
string parse1::remove_comments(const string & str){
	return	str.substr(0,str.find("//"));
}