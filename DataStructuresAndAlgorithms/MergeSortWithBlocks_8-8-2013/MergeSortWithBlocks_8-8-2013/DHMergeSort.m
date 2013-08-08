//
//  DHMergeSort.m
//  MergeSortWithBlocks_8-8-2013
//
//  Created by Derrick Ho on 8/8/13.
//  Copyright (c) 2013 Derrick Ho. All rights reserved.
//

#import "DHMergeSort.h"

@implementation DHMergeSort
+ (NSArray *)mergeSort:(NSArray *)arr compareALessThanBBlock:(BOOL(^)(id a, id b))compare {
	if (!arr || !compare) {
		printf("error can't be nil\n");
		return nil;
	}
	if (arr.count >1) {
		NSArray *arr1 = [DHMergeSort mergeSort:[arr subarrayWithRange:NSMakeRange(0, arr.count/2)]
						compareALessThanBBlock:compare];
		NSArray *arr2 = [DHMergeSort mergeSort:[arr subarrayWithRange:NSMakeRange(arr.count/2, arr.count - arr.count/2)]
						compareALessThanBBlock:compare];
		return [DHMergeSort mergeArrays:arr1
								 array2:arr2
						   compareBlock:compare];
	} else {
		return arr;
	}
}
+ (NSArray *)mergeArrays:(NSArray *)arr1 array2:(NSArray *)arr2 compareBlock:(BOOL(^)(id a, id b))compare {
	NSInteger index1, index2;
	index1 = index2 = 0;
	NSMutableArray *mergedArray = [[NSMutableArray alloc] initWithCapacity:arr1.count + arr2.count ];
	for (NSInteger i = 0; i < (arr1.count + arr2.count); ++i) {
		if (index1 == arr1.count) {
			[mergedArray addObject:arr2[index2]];
			++index2;
		} else if(index2 == arr2.count) {
			[mergedArray addObject:arr1[index1]];
			++index1;
		} else if (!compare(arr1[index1], arr2[index2])) {//arr1[index1] >= arr2[index2]
			[mergedArray addObject:arr2[index2]];
			++index2;
		} else if (compare(arr1[index1], arr2[index2])){//(arr1[index1] < arr2[index2])
			[mergedArray addObject:arr1[index1]];
			++index1;
		} else {
			printf("Error can't use nil\n");
			return nil;
		}
	}
//	NSLog(@"%@", mergedArray);
	return mergedArray;
}
@end
