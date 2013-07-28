//
//  main.m
//  5_SmallestMultiple
//
//  Created by Derrick Ho on 7/26/13.
//  Copyright (c) 2013 Derrick Ho. All rights reserved.
//
/*Read me
 
 2520 is the smallest number that can be divided by each of the numbers from 1 to 10 without any remainder.
 
 What is the smallest positive number that is evenly divisible by all of the numbers from 1 to 20?
 */
/*in other words, what is the FIRST number that is divisible by all numbers in the range*/

#import <Foundation/Foundation.h>
#import "DHLowestCommonMultiple.h"

@interface DHSmallestMultiple : NSObject
+ (NSNumber *)SmallestNumDivisibleByAllNumInRange:(NSRange)range;
@end
@implementation DHSmallestMultiple
/*This is a brute force algorithm.  I would probably have better luck using the seive*/
+ (NSNumber *)SmallestNumDivisibleByAllNumInRange:(NSRange)range{
	NSInteger smallestNum;
	NSInteger sumOfMods;
	for (smallestNum = range.location + range.length; YES; ++smallestNum){
		sumOfMods = 0;
		for (NSInteger r = 0; r < range.length; ++r) {
			sumOfMods += smallestNum % (range.location + r);
		}
		if (!sumOfMods) {
			break;
		}
	}
	return @(smallestNum);
}
@end
int main(int argc, const char * argv[])
{
	@autoreleasepool {
		//NSLog(@"%@", [DHSmallestMultiple SmallestNumDivisibleByAllNumInRange:NSMakeRange(1, 20)]);
		DHLowestCommonMultiple *lcm = [[DHLowestCommonMultiple alloc] initWithArrayOfNumbers:
		 @[@(1),
		 @(2),
		 @(3),
		 @(4),
		 @(5),
		 @(6),
		 @(7),
		 @(8),
		 @(9),
		 @(10)]];
		NSLog(@"%@", lcm.lcm);
	}
    return 0;
}
