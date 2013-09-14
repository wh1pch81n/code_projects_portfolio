//
//  main.cpp
//  CapitalizeFirstLetterOfWords
//
//  Created by Derrick Ho on 4/25/13.
//  Copyright (c) 2013 Derrick Ho. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
int main(int argc, const char * argv[])
{
	ifstream ifile;
	ifile.open(argv[1]);
	
	if( ifile.fail()){
		cout << "could not open file\n";
		return 1;
	}
	for (string line = ""; getline(ifile, line)  ; ) {
		stringstream ss(line);
		string word;
		while(ss >> word){
			if( word[0] >= 'a' && word[0] <= 'z'){
				word[0] &= ~ 0x20;
			}
			cout << word << " ";
		}cout << endl;
	}
    return 0;
}

