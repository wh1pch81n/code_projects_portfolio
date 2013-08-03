//
//  main.m
//  13_largeSum
//
//  Created by Derrick Ho on 8/2/13.
//  Copyright (c) 2013 Derrick Ho. All rights reserved.
//

#import <Foundation/Foundation.h>
#define kFile 

int main(int argc, const char * argv[])
{

	@autoreleasepool {
	    FILE *f = fopen(argv[1], "r");
		if (!f) {
			fprintf(stderr, "%s\n", "can't open");
		}
		char c[1024];
		NSInteger total = 0;
		while (fscanf(f , "%[^\n]\n", c) == 1) {
			NSString *num = [NSString stringWithUTF8String:c];
			total += [[num substringWithRange:NSMakeRange(0, 11)] integerValue];
		}
	    printf("Total: %ld\n", total);
		NSString *str = [NSString stringWithFormat:@"%ld", total];
		printf("first ten: %ld\n", [str substringWithRange:NSMakeRange(0, 10)].integerValue);
	}
    return 0;
}

