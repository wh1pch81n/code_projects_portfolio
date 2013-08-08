//
//  DHMergeSort.h
//  MergeSortWithBlocks_8-8-2013
//
//  Created by Derrick Ho on 8/8/13.
//  Copyright (c) 2013 Derrick Ho. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface DHMergeSort : NSObject
+ (NSArray *)mergeSort:(NSArray *)arr compareALessThanBBlock:(BOOL(^)(id a, id b))compare;
@end
