//
//  main.m
//  SumOfNumbersFromFile
//
//  Created by Derrick Ho on 4/17/13.
//  Copyright (c) 2013 Derrick Ho. All rights reserved.
//

#import <Foundation/Foundation.h>

int main(int argc, const char * argv[])
{
	char line[10];
	FILE* f = fopen(argv[1], "r");
	if(!f ){
		printf("could not open file\n");
		exit(0);
	}
	int i;
	for (i =0; fgets(line, sizeof(line), f); ) {
		if(line[0] == '\n') continue;
		i += (int)strtol(line, NULL, 10);
	}
	printf("%d", i);
	return 0;
}

