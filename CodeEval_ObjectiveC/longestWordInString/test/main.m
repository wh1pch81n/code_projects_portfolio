//
//  main.m
//  test
//
//  Created by Derrick Ho on 9/13/13.
//  Copyright (c) 2013 Derrick Ho. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef struct Range {
    unsigned int loc;
    unsigned int len;
} Range;

int main( int argc, char **argv) {
    
	FILE *f = fopen(argv[1], "r");
	char line[1024];
	{
	while (1==fscanf(f,"%[^\n]\n", line)) {
        // Skip empty lines
        if (line[0] == '\n') {
            continue;
        }
        // Do something with the line
        Range maxRange;
        maxRange.loc = 0;
        maxRange.len = 0;
        int left = 0;
        int curr = 0;
        char del = ' ';
        while(1) {
            if( line[curr] == del || line[curr] == '\0') {
                if(maxRange.len < (curr-left)) {
                    maxRange.loc = left;
                    maxRange.len = curr -left;
                }
                left = curr +1;
                if( line[curr] == '\0') break;
            }
            ++curr;
        }
        char *s = line + maxRange.loc;
        s[maxRange.len] = '\0';
        printf("%s\n", s);
    }
    return 0;
	}
}
