//
//  main.m
//  14_longestCollatzSequence
//
//  Created by Derrick Ho on 8/3/13.
//  Copyright (c) 2013 Derrick Ho. All rights reserved.
//

#import <Foundation/Foundation.h>

int main(int argc, const char * argv[])
{
	@autoreleasepool {
	    NSLog(@"Start");
		NSMutableArray *collatz =[NSMutableArray new];
		for (NSInteger i = 2; i < 1000000; ++i){
			[collatz addObject:[@[@(i), @(i)] mutableCopy]];
		}
		//NSLog(@"%@", collatz );
		while ([collatz count] >1) {
			collatz = [[collatz filteredArrayUsingPredicate:[NSPredicate predicateWithBlock:^BOOL(id evaluatedObject, NSDictionary *bindings) {
				NSInteger valueOfKey = [evaluatedObject[1] integerValue];
				valueOfKey = (valueOfKey & 0x1)? 3*valueOfKey +1: valueOfKey >> 1;
				if (valueOfKey == 1) {
					return NO;
				}
				evaluatedObject[1] = @(valueOfKey);
				return YES;
			}]] mutableCopy];
			//NSLog(@"%@", collatz );
		}
		NSLog(@"The longest Chain is: %@", collatz);
		NSLog(@"End");
	}
	return 0;
}

