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
@interface DHSmallestMultiple : NSObject
+ (NSNumber *)SmallestNumDivisibleByAllNumInRange:(NSRange)range;
+ (NSNumber *)SmallestNumDivisibleByAllNumInRange:(NSRange)range maxNumber:(NSNumber *)max;
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
/*Incomplete and probably wrong*/
+ (NSNumber *)SmallestNumDivisibleByAllNumInRange:(NSRange)range maxNumber:(NSNumber *)max {
	//init array
	NSMutableArray *seive = [NSMutableArray new];
	for (NSInteger i = 0; i < max.integerValue; ++i) {
		[seive addObject:@(0)];
	}
	[seive addObject:@(-1)];
	[seive addObject:@(-1)];
	//sieve
	for (NSInteger i = range.location; i < range.location + range.length; ++i) {
		if (seive[i] >= 0){
			NSInteger j = i * i;
			NSInteger jmul = 0;
			for (; (j + jmul) < max.integerValue; jmul += i) {
				seive[j+jmul] = @([seive[j+jmul] integerValue] + 1);
			}
		}
	}
	
	//smallest num
	return @(0);
}
@end
int main(int argc, const char * argv[])
{

	@autoreleasepool {
		NSLog(@"%@", [DHSmallestMultiple SmallestNumDivisibleByAllNumInRange:NSMakeRange(1, 20)]);
//NSLog(@"%@", [DHSmallestMultiple SmallestNumDivisibleByAllNumInRange:NSMakeRange(1, 20) maxNumber:@(1<<30)]);
	}
    return 0;
}
