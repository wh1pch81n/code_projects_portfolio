//
//  main.cpp
//  Hack_Assembler
//
//  Created by Derrick Ho on 11/25/12.
//  Copyright (c) 2012 Derrick Ho. All rights reserved.
//

#include <iostream>
#include "Parse1.h"

int main(int argc, const char * argv[])
{
	char line[1024];
	FILE* f;
	if ( !(f = fopen(argv[1], "r") )) {
		printf("Error: can't open file");
		return 0;
	}
	parse1 p;
	while (fgets(line, sizeof(line), f )) {
		p.insert(string(line));
	}
	p.to_hack_bin();
    return 0;
}

