//
//  main.c
//  panagram
//
//  Created by Derrick Ho on 4/27/13.
//  Copyright (c) 2013 Derrick Ho. All rights reserved.
//


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define _A (0x00000001 << 0)
#define _B (0x00000001 << 1)
#define _C (0x00000001 << 2)
#define _D (0x00000001 << 3)
#define _E (0x00000001 << 4)
#define _F (0x00000001 << 5)
#define _G (0x00000001 << 6)
#define _H (0x00000001 << 7)
#define _I (0x00000001 << 8)
#define _J (0x00000001 << 9)
#define _K (0x00000001 << 10)
#define _L (0x00000001 << 11)
#define _M (0x00000001 << 12)
#define _N (0x00000001 << 13)
#define _O (0x00000001 << 14)
#define _P (0x00000001 << 15)
#define _Q (0x00000001 << 16)
#define _R (0x00000001 << 17)
#define _S (0x00000001 << 18)
#define _T (0x00000001 << 19)
#define _U (0x00000001 << 20)
#define _V (0x00000001 << 21)
#define _W (0x00000001 << 22)
#define _X (0x00000001 << 23)
#define _Y (0x00000001 << 24)
#define _Z (0x00000001 << 25)
#define _ABC_ 0x03FFFFFF 

char * getMissingLetters(char *);
void addToBar(uint32_t * bar, char letter);

int main(int argc, const char * argv[])
{
	char line[1024];
	
	FILE* f = fopen(argv[1], "r");
	
	if( !f){
		printf("can't open file\n");
		return -1;
	}
	while (fgets(line, sizeof(line), f)) {
		if( line[0] == '\n') continue;
		printf("%s\n", getMissingLetters(line));
	}
	
	
    return 0;
}

char * getMissingLetters(char * line){
	static char ret_line[1024];
	uint32_t arb_bar;
	for( arb_bar = 0;*line != '\0'; ++line) {
		char c = *line;
		c |= 0x20;
		if (c >= 'a' && c <= 'z') {
			addToBar(&arb_bar, c);
		}
	}
	if (arb_bar == _ABC_) {
		strcpy(ret_line, "NULL");
	}else{
		int i, reti;
		for (i = 0, reti = 0; i < 26; ++i) {
			if( ((0x00000001 << i ) & arb_bar) == 0x00000000){
				ret_line[ reti] = 'a' + i;
				++reti;
			}
		}
		ret_line[reti] ='\0';
	}
	return ret_line;
}

void addToBar(uint32_t * bar, char letter){
	*bar |= 0x00000001 << (letter - 'a');
}