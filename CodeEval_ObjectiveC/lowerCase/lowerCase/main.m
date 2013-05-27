//
//  main.m
//  lowerCase
//
//  Created by Derrick Ho on 4/15/13.
//  Copyright (c) 2013 Derrick Ho. All rights reserved.
//

#import <Foundation/Foundation.h>

int main(int argc, const char * argv[])
{

	NSAutoreleasePool* pool = [NSAutoreleasePool new];
		char line[1024];
		FILE* f = fopen(argv[1], "r");
		if(!f){
			printf("Can't open. help!\n");
			exit(0);
		}
		while (fgets(line, sizeof(line), f)) {
			if(*line == '\n'){
				continue;
			}
			int i;
			for (i = 0; i< strlen(line); ++i) {
				if (line[i] >= 'A' && line[i] <= 'Z') {
					putchar(line[i] | 0x20);
				}else{
					putchar(line[i]);
				}
			}
		}
	[pool drain];
    return 0;
}

