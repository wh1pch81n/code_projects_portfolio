//
//  main.c
//  CapitalizeFirstLetterOfWords
//
//  Created by Derrick Ho on 4/25/13.
//  Copyright (c) 2013 Derrick Ho. All rights reserved.
//
#include <stdio.h>
#include <string.h>


int main(int argc, const char * argv[])
{
	char line[1024];
	FILE * f = fopen(argv[1], "r");
	
	if( !f){
		printf("can't open file\n");
		return 1;
	}
	while (fgets(line, sizeof(line), f)) {
		char *word;
		word = strtok(line, " \n");
		for(; word != NULL; ){
			if (word[0] >= 'a' && word[0] <= 'z') {
				word[0] &= ~0x20;
			}
			
			printf("%s", word);
			printf("%s", (word = strtok(NULL, " \n"))? " ": "");
		}
		printf("\n");
	}
    return 0;
}

