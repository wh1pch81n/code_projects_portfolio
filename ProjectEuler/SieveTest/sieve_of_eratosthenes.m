//
//  sieve_of_eratosthenes.m
//  sieve_of_eratosthenes
//
//  Created by Derrick Ho on 8/2/13.
//  Copyright (c) 2013 Derrick Ho. All rights reserved.
//

#import "sieve_of_eratosthenes.h"
@interface DHsieveOfEratosthenes ()
@property (strong, nonatomic) NSMutableArray *sieveUnrefined;
@property (strong, nonatomic) NSMutableArray *sieveClean;
@end
@implementation DHsieveOfEratosthenes
-(NSArray *)generateSieveUnrefined:(NSNumber *)maxNum {
	[self setSieveUnrefined:[[NSMutableArray alloc] init]];
	for (NSInteger i = 0; i <= [maxNum integerValue]; ++i) {
		[[self sieveUnrefined] addObject:[NSNumber numberWithBool:YES]];
	}
	self.sieveUnrefined[0] = [NSNumber numberWithBool:NO];
	self.sieveUnrefined[1] = [NSNumber numberWithBool:NO];
	
	for (NSInteger  i = 2; i <= [maxNum integerValue]; ++i) {
		if ([[[self sieveUnrefined] objectAtIndex:i] boolValue] == YES) {
			NSInteger j = i * i;
			for (NSInteger jMul = 0; (j + jMul) <= [maxNum integerValue]; jMul += i) {
				self.sieveUnrefined[j + jMul] = [NSNumber numberWithBool:NO];
			}
		}
	}
	return [self sieveUnrefined];
}
-(NSArray *)generateSieveUpTo:(NSNumber *)maxNum {
	if ([self sieveUnrefined] == nil) {
		[self generateSieveUnrefined:maxNum];
	}
	NSMutableArray *cleanSieve = [NSMutableArray new];
	for (NSInteger i = 0; i < [[self sieveUnrefined] count]; ++i) {
		if ([[[self sieveUnrefined] objectAtIndex:i] boolValue] == YES) {
			[cleanSieve addObject:@(i)];
		}
	}
	[self setSieveClean:cleanSieve];
	return [self sieveClean];
}
-(NSNumber *)getPrimeNumberLessThan:(NSNumber *)num {
	return
	([self sieveClean])?	[[self sieveClean] lastObject]: [[self generateSieveUpTo:num] lastObject];
}
@end
