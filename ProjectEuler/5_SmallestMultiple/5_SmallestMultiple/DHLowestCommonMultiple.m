//
//  DHLowestCommonMultiple.m
//  5_SmallestMultiple
//
//  Created by Derrick Ho on 7/28/13.
//  Copyright (c) 2013 Derrick Ho. All rights reserved.
//

#import "DHLowestCommonMultiple.h"
#import "DHPair.h"
#import "listOfPrimes10k.h"
@interface DHLowestCommonMultiple ()
@property(strong, nonatomic) NSMutableArray *pairPrimeCount;
@property(strong, nonatomic) NSArray *smallPrimeList; //contains smallest prime up to but not including maxPrime
@property(strong, nonatomic) NSNumber *maxPrime; //A prime that is larger than the given array of number.
@end
@implementation DHLowestCommonMultiple
- (id)initWithArrayOfNumbers:(NSArray *)arr {
	if (!(self = [super init])) return nil;
	if (![[arr lastObject] isKindOfClass:[NSNumber class]]) return nil;
	if (![self maxPrime]) {
		//find largest in array
		NSInteger largest = 0;
		for (NSNumber *n in arr) {
			if (largest < n.integerValue) {
				largest = n.integerValue;
			}
		}
		//find the first prime larger than largest
		NSMutableArray *spl = [NSMutableArray new];
		for (int i = 0; cListOfPrimes10k[i] != EndOfPrimeList; ++i){
			if (cListOfPrimes10k[i] > largest) {
				[self setMaxPrime:@(cListOfPrimes10k[i])];
				break;
			}
			[spl addObject:@(cListOfPrimes10k[i])];
		}
		[self setSmallPrimeList:spl];
	}
	if (![self pairPrimeCount]) {
		[self setPairPrimeCount:[NSMutableArray new]];
		for (int i = 0; cListOfPrimes10k[i] != self.maxPrime.integerValue; ++i) {
			DHPair *pair = [[DHPair alloc] initWithLeftOfPair:[[self smallPrimeList] objectAtIndex:i]
												  rightOfPair:@(0)];
			[[self pairPrimeCount] addObject:pair];
		}
	}
	[self reduceToOne:[arr mutableCopy]];
	[self calcLowestCommonMultiple];
	return self;
}
- (void)reduceToOne:(NSMutableArray *)arr {
	NSArray *currArr = nil;
	NSArray *newArr = nil;
	NSInteger primeIndex = 0;
	enum state {
		eStay = 0,
		eUp = 1,
		eDown = 2
	}st;
	st = 0;
	//preset
	currArr = arr;
	//FSM -- this FSM is buggy
	while (![self isArrayOfOnes:currArr]) {
		newArr = [self reduceArray:currArr
					withPrimeIndex:primeIndex];
		if ([newArr isEqualToArray:currArr]) {
			++primeIndex;
			if (cListOfPrimes10k[primeIndex] == [[self maxPrime] intValue]) {//buggy
				primeIndex = 0;
			} 
		} else {
			NSNumber *newRightOfPair = @([[self.pairPrimeCount[primeIndex] rightOfPair] integerValue] +1);
			[[[self pairPrimeCount] objectAtIndex:primeIndex] setRightOfPair:newRightOfPair];
		}
		//tick
		currArr = newArr;
		newArr =nil;
	}
}
- (BOOL)isArrayOfOnes:(NSArray *)arr {
	if (!arr) {
		NO;
	}
	if (![arr[0] isKindOfClass:[NSNumber class]]) {
		NO;
	}
	for (NSNumber *n in arr) {
		if ([n integerValue] == 1) continue;
		return NO;
	}
	return YES;
}
- (NSArray *)reduceArray:(NSArray *)arr withPrimeIndex:(NSInteger)primeIndex {
	NSMutableArray *newArr = [arr mutableCopy];
	for (int i  = 0; i < [arr count]; ++i) {
		if ([arr[i] integerValue]  % [[[self smallPrimeList] objectAtIndex:primeIndex] integerValue]) {
			continue;
		}
		NSNumber *newObj = @([arr[i] integerValue] / [[[self smallPrimeList] objectAtIndex:primeIndex] integerValue]);
		newArr[i] = newObj;
	}
	return newArr;
}
- (void)calcLowestCommonMultiple {
	int prod = 1;
	for (DHPair *p in [self pairPrimeCount]) {
		prod *= pow([[p leftOfPair] intValue], [[p rightOfPair] intValue]);
	}
	[self setLcm:@(prod)];
}
@end
