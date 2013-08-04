//
//  main.m
//  12_highlydivisibletriangle
//
//  Created by Derrick Ho on 8/3/13.
//  Copyright (c) 2013 Derrick Ho. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "listOfPrimes10k.h"

@interface Factorize : NSObject
- (NSArray *)factorsOfNum:(NSNumber *)num;
- (id)init;
@property (strong, nonatomic) NSMutableArray *smallPrimeList;
@property (strong, nonatomic) NSMutableDictionary *primeCount;
@property (strong, nonatomic) NSMutableSet *divisors;
@end
@implementation Factorize
- (id)init{
	if (!(self = [super init])) {
		return nil;
	}
	[self setSmallPrimeList:[NSMutableArray new]];
	[self setPrimeCount:[NSMutableDictionary new]];
	return self;
}
- (NSArray *)factorsOfNum:(NSNumber *)num {
	[self setPrimeCount:[NSMutableDictionary new]];
	while ([num integerValue] > 1) {
		for (NSNumber *n in [self smallPrimeList]) {
			if ([num integerValue] % [n integerValue] == 0) {
				[self primeCount][n] = @([[self primeCount][n] integerValue] + 1);
				num = @([num integerValue] / [n integerValue]);
			}
		}
	}
	return [[[self primeCount] allKeys] filteredArrayUsingPredicate:[NSPredicate predicateWithBlock:^BOOL(id evaluatedObject, NSDictionary *bindings) {
		return [[[self primeCount] objectForKey:evaluatedObject] boolValue];
	}]];
}
- (NSNumber *)numOfDivisors:(NSNumber *)num {
	if (num.integerValue == 0) return nil;
	NSArray *factors = [self factorsOfNum:num];
	NSInteger total = (num.integerValue == 1)? 1: 2;
	NSMutableArray *coPrime = [NSMutableArray new];
	for (NSNumber *n in factors) {
		//total += [[[self primeCount] objectForKey:n] integerValue];
		[coPrime addObject:@([num integerValue]/[n integerValue])];
	}
	self.divisors = [NSMutableSet new];
	[self.divisors addObjectsFromArray:factors];
	[self.divisors addObjectsFromArray:coPrime];
	[self.divisors addObjectsFromArray:@[@(1), num]];
	return @(self.divisors.count);
}
/**makes an array with size count filled with primes*/
- (void)makeSmallPrimeListWithCount:(NSInteger)count {
	for (int i = 0; i < count; ++i) {
		[[self smallPrimeList] addObject:@(cListOfPrimes10k[i])];
		[[self primeCount] addEntriesFromDictionary:@{@(cListOfPrimes10k[i]): @(0)}];
	}
}
@end

int main(int argc, const char * argv[])
{

	@autoreleasepool {
		{
		Factorize *f = [Factorize new];
		int largest = 0;
		[f makeSmallPrimeListWithCount:10000];
		long long int total = 0;
		for (int i = 1; i < 100000; ++i) {
			total = i*(i + 1)/2;
			
			NSNumber *n = [f numOfDivisors:@(total)];
			if (largest < [n integerValue]) {
				largest = [n integerValue];
				NSLog(@"[%d] %lld: %@\n%@", i, total, n,  [f divisors]);
			}
			if ([n integerValue] >= 500){
				break;
			}
		}
		printf("done\n");
		}
//		int total = 0;
//		for (int i = 1; i < 10; ++i) {
//			total += i;
//			NSLog(@"%d: %@\n%@", total, [f numOfDivisors:@(total)],  [f divisors]);
//		}
	
		
//		NSLog(@"%@", [f smallPrimeList]);
//		NSLog(@"%@", [f factorsOfNum:@(21)]);
//		NSLog(@"%@", [f primeCount]);
//		NSLog(@"%@", [f numOfDivisors:@(21)]);
//		total = 28;
//		NSLog(@"%d: %@\n%@", total, [f numOfDivisors:@(total)],  [f divisors]);
	}
    return 0;
}

