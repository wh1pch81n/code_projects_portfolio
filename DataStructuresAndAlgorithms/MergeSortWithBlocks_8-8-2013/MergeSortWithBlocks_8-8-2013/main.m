//
//  main.m
//  MergeSortWithBlocks_8-8-2013
//
//  Created by Derrick Ho on 8/8/13.
//  Copyright (c) 2013 Derrick Ho. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "DHMergeSort.h"
int main(int argc, const char * argv[])
{

	@autoreleasepool {
		NSMutableArray *arc = [NSMutableArray new];
		for (int i = 0; i < 30; ++i) {
			[arc addObject:@(arc4random() % 30)];
		}
		NSLog(@"%@", arc);
	    NSLog(@"%@", [DHMergeSort mergeSort:arc
					 compareALessThanBBlock:^BOOL(id a, id b) {
							 return ([a integerValue] < [b integerValue]);
					 }]);
	}
    return 0;
}

