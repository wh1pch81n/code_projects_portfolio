//
//  main.m
//  2_sumEvenFibs
//
//  Created by Derrick Ho on 7/20/13.
//  Copyright (c) 2013 Derrick Ho. All rights reserved.
//

#import <Foundation/Foundation.h>
@interface fib3: NSObject
@end
@implementation fib3
+(NSMutableArray *)arrayOfFibWithMax:(NSNumber *)max{
	NSInteger fn1 = 0;
	NSInteger fn2 = 1;
	NSInteger fn;
	NSMutableArray *marr = [NSMutableArray new];
	[marr addObject:@(fn1)];
	[marr addObject:@(fn2)];
	fn = [marr.lastObject integerValue];
	for (; fn < [max integerValue]; ) {
		fn1 = [[marr objectAtIndex:marr.count-1] integerValue];
		fn2 = [[marr objectAtIndex:marr.count-2] integerValue];
		if (fn2 + fn1 >= [max integerValue]) {
			break;
		}
		[marr addObject:@(fn1 +fn2)];
		fn = [marr.lastObject integerValue];
	}
	return marr;
}
+(NSNumber *)sumOfEvenNumberInArray:(NSMutableArray *)arr{
	NSInteger num = 0;
	for (NSNumber *n in arr) {
		if (0 == (n.integerValue % 2)) {
			num += n.integerValue;
		}
	}
	return @(num);
}
@end

int main(int argc, const char * argv[])
{

	@autoreleasepool {
		NSMutableArray *m = [fib3 arrayOfFibWithMax:@(4000000)];
		NSNumber *n = [fib3 sumOfEvenNumberInArray:m];
		NSLog(@"%@", m);
		NSLog(@"%@", n);
	}
    return 0;
}

