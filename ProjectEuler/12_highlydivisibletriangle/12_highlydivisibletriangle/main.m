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
	NSArray *factors = [self factorsOfNum:num];
	NSInteger total = 0;
	for (NSNumber *n in factors) {
		total += [[[self primeCount] objectForKey:n] integerValue];
	}
	return @(total);
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
		int total = 0;
		for (int i = 1; i < 10; ++i) {
			total += i;
			printf("%d\n", total);
		}
		Factorize *f = [Factorize new];
		[f makeSmallPrimeListWithCount:500];
		
		NSLog(@"%@", [f smallPrimeList]);
		NSLog(@"%@", [f factorsOfNum:@(21)]);
		NSLog(@"%@", [f primeCount]);
		NSLog(@"%@", [f numOfDivisors:@(21)]);
	}
    return 0;
}

