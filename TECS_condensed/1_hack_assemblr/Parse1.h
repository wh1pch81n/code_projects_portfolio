//
//  Parse1.h
//  Hack_Assembler
//
//  Created by Derrick Ho on 11/25/12.
//  Copyright (c) 2012 Derrick Ho. All rights reserved.
//

#ifndef Hack_Assembler_Parse1_h
#define Hack_Assembler_Parse1_h
#include <list>
#include <map>
#include <iostream>
#include <bitset>
#define BITWIDTH 16
using namespace std;
class parse1{
public:
	parse1();
	size_t insert(const string & str );
	void to_hack_bin();
private:
	int  handle_A(const string&);
	int  handle_C(const string&);
	int  handle_J(const string&);
	string remove_white(const string & str);
	string remove_comments(const string & str);
	list<string> linked_list;
	map<string, size_t> hash;
	bool isLabel(const string & str);
	bool is_at(const string & str);
	string makeSymbol(const string & str);
	void makeSplit(const string& str);
	map<string, int > comp_table;
	map<string, int> dest_table;
	map<string, int> jump_table;
	map<string,int>::iterator comp_table_it;
	map<string,int>::iterator dest_table_it;
	map<string,int>::iterator jump_table_it;
	
};
#endif
