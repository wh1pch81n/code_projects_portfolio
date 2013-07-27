//
//  main.m
//  6_Sum_Square_diff
//
//  Created by Derrick Ho on 7/26/13.
//  Copyright (c) 2013 Derrick Ho. All rights reserved.
//

#import <Foundation/Foundation.h>
/*
 use range to set the bounds on consecutive numbers to sum up
 */
@interface DHSumSquareDiff : NSObject
+ (NSNumber *)sumOfSquares:(NSRange)range;
+ (NSNumber *)squareOfSum:(NSRange)range;
@end
int main(int argc, const char * argv[])
{
	@autoreleasepool {
		NSRange r = NSMakeRange(1, 100);
		NSInteger sumOfSq = [[DHSumSquareDiff sumOfSquares:r] integerValue];
		NSInteger sqOfSum = [[DHSumSquareDiff squareOfSum:r] integerValue];
		NSInteger diff = abs(sumOfSq - sqOfSum);
		NSString *mathEquation = nil;
		if (sumOfSq > sqOfSum) {
			mathEquation = [NSString stringWithFormat:@"%ld - %ld = ", (long)sumOfSq, (long)sqOfSum];
		} else {
			mathEquation = [NSString stringWithFormat:@"%ld - %ld = ", (long)sqOfSum, (long)sumOfSq];
		}
		NSLog(@"%@%ld", mathEquation, diff);
	}
    return 0;
}

@implementation DHSumSquareDiff
+ (NSNumber *)sumOfSquares:(NSRange)range {
	NSInteger total = 0;
	for (NSInteger i = 0; i < range.length; ++i) {
		total += (range.location + i) * (range.location + i);
	}
	return @(total);
}
+ (NSNumber *)squareOfSum:(NSRange)range {
	NSInteger total = 0;
	for (NSInteger i = 0; i < range.length; ++i) {
		total += range.location + i;
	}
	return @(total * total);
}
@end
