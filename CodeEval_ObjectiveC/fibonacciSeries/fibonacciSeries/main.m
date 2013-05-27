//
//  main.m
//  fibonacciSeries
//
//  Created by Derrick Ho on 4/16/13.
//  Copyright (c) 2013 Derrick Ho. All rights reserved.
//

#import <Foundation/Foundation.h>

int main(int argc, const char * argv[])
{
	char line[10];
	FILE* f = fopen(argv[1], "r");
	if(!f){
		printf("Can't open file!\n");
		exit(0);
	}
	while (1 == fscanf(f, "%s", line)) {
		if (line[0] == '\n') {
			continue;
		}
		NSInteger num = strtoul(line, NULL, 10);
		NSInteger fib = 0;
		NSInteger prenum;
		switch (num) {
			case 0:fib = 0;
				break;
			case 1:fib = 1;
			default:
			{
				NSInteger f1, f2, f3;
				f1 = 0; f2 = 1;
				for (prenum = 1; prenum< num; ++prenum) {
					f3 = f2+ f1;
					f1 = f2;
					f2 = f3;
					if(f3 <= 0){
						NSLog(@"overflowed....");
					}
				}
				fib = f3;
				break;
			}
		}
		printf("%ld\n", fib);
	}
    return 0;
}

