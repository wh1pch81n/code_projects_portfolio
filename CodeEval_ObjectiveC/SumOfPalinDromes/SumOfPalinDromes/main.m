//
//  main.m
//  SumOfPalinDromes
//
//  Created by Derrick Ho on 4/10/13.
//  Copyright (c) 2013 Derrick Ho. All rights reserved.
//

#import <Foundation/Foundation.h>
@interface PrimeSums: NSObject{
	
}
+(void) run_prog:(int) argc :(const char **) argv;
+(void) getSumOfPrimesUpto:(int) thisNum;
@end

int main(int argc, const char * argv[])
{
	NSAutoreleasePool * pool = [NSAutoreleasePool new];//[[NSAutoreleasePool alloc]init];
	{
		[PrimeSums run_prog: argc: argv];
	}
	[pool drain];
	return 0;
}

@implementation PrimeSums
+(void) run_prog:(int) argc :(const char **) argv{
	[PrimeSums getSumOfPrimesUpto:10000];
}
+(void) getSumOfPrimesUpto:(int) thisNum{
	NSMutableArray * arrOfBools = [NSMutableArray array];
	//default every number to prime
	int i;
	for (i = 0; i < thisNum; ++i) {
		[arrOfBools addObject:@"isPrime"];
	}
	[arrOfBools replaceObjectAtIndex:0 withObject:@"notPrime"];
	[arrOfBools replaceObjectAtIndex:1 withObject:@"notPrime"];
	//filter out what is and what is not prime via Seive of Eratosthenes
	for (i = 2; i < thisNum; ++i) {
		if ([[arrOfBools objectAtIndex:i] isEqualTo:@"isPrime"]) {
			int j;
			for (j = i; (j*i) < thisNum; ++j) {
				[arrOfBools replaceObjectAtIndex:j*i withObject:@"notPrime"];
			}
		}
	}
	//find the sum of palendrime prime under 100
	int j;
	int summaprimes= 0;
	int numPrimes = 0;
	for (j = 2; numPrimes < 1000; ++j ) {
		if( [[arrOfBools objectAtIndex:j] isEqualTo:@"isPrime"]){
			summaprimes += j;
			++numPrimes;
			//printf("[%d] %d += %d\n",numPrimes, summaprimes, j);
		}
	}
	printf("%d", summaprimes);
}
@end
