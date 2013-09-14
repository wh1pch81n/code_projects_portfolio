//
//  main.cpp
//  penUltimateWord
//
//  Created by Derrick Ho on 4/24/13.
//  Copyright (c) 2013 Derrick Ho. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
std::vector<std::string> splitStr(const string& s, const char delimiter){
	stringstream ss(s);
	string str;
	vector<string> v;
	while (std::getline(ss, str , delimiter)) {
		v.push_back(str);
	}
	return v;
}

int main(int argc, const char * argv[])
{
	std::string line;
	std::ifstream f;
	f.open(argv[1]);
	
	if( f.fail()){
		std::cout << "Can't open file" << std:: endl;
		return 1;
	}
	while (std::getline(f , line)) {
		if (line == "\n") {
			continue;
		}
		vector<string> v( splitStr(line, ' '));
		cout << v[v.size()-2] << endl;
	}
	
    return 0;
}

