//
//  main.c
//  penUltimateWord
//
//  Created by Derrick Ho on 4/24/13.
//  Copyright (c) 2013 Derrick Ho. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char * argv[])
{
	char line[1024];
	char* word_n;
	char* word_n1;
	char* word_n2;
	FILE * f = fopen(argv[1], "r");
	if(!f){
		printf("can't open file\n");
		return 1;
	}
	while (fgets(line , sizeof(line), f)) {
		if(line[0] == '\n') continue;
		word_n2 = strtok(line, " \n"); //does not create a dynamically allocated string
		while (word_n2 ) {
			word_n = word_n1;
			word_n1 = word_n2;
			word_n2 = strtok(NULL, " \n");
		}
		printf("%s\n", word_n);
		
	}
    return 0;
}

