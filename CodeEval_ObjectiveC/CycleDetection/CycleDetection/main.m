//
//  main.m
//  CycleDetection
//
//  Created by Derrick Ho on 9/11/13.
//  Copyright (c) 2013 Derrick Ho. All rights reserved.
//

#import <Foundation/Foundation.h>

const NSString *input = @"2 0 6 3 1 6 3 1 6 3 1";
const NSString *output = @"6 3 1";

NSRange brent(NSArray *x0) {
	int power = 1, len = 1, loc = 0, turtle = 0, hare = 1;
	for (; ![x0[turtle] isEqualTo:x0[hare]]; ++hare, ++len) {
		if (power == len) {
			turtle = hare;
			power <<= 1;
			len = 0;
		}
	}
	turtle = hare = 0;
	for (int i = 0; i < len; ++hare, ++i) {	}
	for (; ![x0[turtle] isEqualToString:x0[hare]]; ++turtle, ++hare, ++loc) {  }
	return NSMakeRange(loc, len);
}

int main(int argc, const char * argv[])
{

	@autoreleasepool {
		NSArray *a =[input componentsSeparatedByString:@" "];
		NSRange r = brent(a);
		NSArray *subarr = [a subarrayWithRange:r];
		
		NSLog(@"%@\n", subarr);
	}
    return 0;
}

