//
//  main.m
//  MergeSortWithBlocks_8-21-2013
//
//  Created by Derrick Ho on 8/21/13.
//  Copyright (c) 2013 Derrick Ho. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSArray (MergeSort)
- (NSArray *)mergeSortWithCompare:(int(^)(int a, int b))compare;
@end
@implementation NSArray (MergeSort)
- (NSArray *)mergeSortWithCompare:(int(^)(int a, int b))compare {
	if (self.count >1) {
		return [self mergeArray1:[[self subarrayWithRange:NSMakeRange(0, self.count >> 1)]
								  mergeSortWithCompare:compare]
					  withArray2:[[self subarrayWithRange:NSMakeRange(self.count >> 1, self.count - (self.count >> 1))]
								  mergeSortWithCompare:compare]
				  withComparator:compare];
	}
	return self;
}
- (NSArray *)mergeArray1:(NSArray *)arr1 withArray2:(NSArray *)arr2 withComparator:(int(^)(int a, int b))compare{
	int index_1 , index_2, max_count;
	index_1 = index_2 = 0;
	max_count = (int)arr1.count + (int)arr2.count;
	NSMutableArray *fusion = [[NSMutableArray alloc] initWithCapacity:max_count];
	for (int i = 0; i < max_count; ++i){
		if (index_1 >= [arr1 count]) {
			[fusion addObjectsFromArray:[arr2 subarrayWithRange:NSMakeRange(index_2, arr2.count - index_2)]];
			break;
		} else if (index_2 >= [arr2 count]) {
			[fusion addObjectsFromArray:[arr1 subarrayWithRange:NSMakeRange(index_1, arr1.count - index_1)]];
			break;
		} else if ( compare( [arr1[index_1] intValue], [arr2[index_2] intValue]) > 0) {
			[fusion addObject:arr1[index_1++]];
		} else if ( compare( [arr1[index_1] intValue], [arr2[index_2] intValue]) <= 0) {
			[fusion addObject:arr2[index_2++]];
		} else {
			@try {
				NSException *e = [NSException exceptionWithName:@"Unknown"
														 reason:@"unHandled" userInfo:nil];
				@throw e;
			} @catch (NSException *theException) {
				if ([[theException name] isEqualToString:@"Unknown"]) {
					NSLog(@"caught something weird");
					exit(-1);
				}
			}
		}
	}
	return fusion;
}
@end

int main(int argc, const char * argv[])
{
	@autoreleasepool {
		__block int(^bigToSmall)(int a, int b) = ^int(int a, int b) {
			return a - b;
		};
		__block int(^smallToBig)(int a, int b) = ^int(int a, int b) {
			return b - a;
		};
		int sizeOfArray = 100000;
	    NSMutableArray *marr = [NSMutableArray arrayWithCapacity:sizeOfArray];
		for (int i = 0; i < sizeOfArray; ++i) {
			[marr addObject:@(arc4random() % sizeOfArray)];
		}
	    NSLog(@"%@", marr);
		NSLog(@"%@ big to small", [marr mergeSortWithCompare:bigToSmall]);
		NSLog(@"%@ small to big", [marr mergeSortWithCompare:smallToBig]);
	}
    return 0;
}

