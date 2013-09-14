//
//  main.cpp
//  panagrams
//
//  Created by Derrick Ho on 4/27/13.
//  Copyright (c) 2013 Derrick Ho. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

string panagram(string line);

int main(int argc, const char * argv[])
{
	ifstream ifile;
	ifile.open(argv[1]);
	if (ifile.fail()) {
		cout << "can't open file \n";
		return 1;
	}
	string line;
	while (getline(ifile, line)) {
		cout << panagram(line)<< endl;
	}
	ifile.close();
    return 0;
}

string panagram(string line){
	stringstream not_in_line;
	stringstream in_line;
	char arr[26]={};
	char c;
	for (int i = 0; i < line.size(); ++i) {
		c = line[i] | 0x20;
		if( c >= 'a' && c <= 'z'){
			arr[c-'a'] = -1;
		}
	}
	for (int i = 0; i < sizeof(arr) ; ++i ) {
		if( arr[i] != -1){
			char b = ('a' + i);
			not_in_line << b;
		}
	}
	return (not_in_line.str() == "")? "NULL": not_in_line.str();
}
