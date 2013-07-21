//
//  DHBinaryTree.m
//  BinaryTreeNumbers_6_30_2013
//
//  Created by Derrick Ho on 6/30/13.
//  Copyright (c) 2013 Derrick Ho. All rights reserved.
//

#import "DHBinaryTree.h"
@interface DHBinaryTree ()
@property (strong, nonatomic) NSMutableArray *treeInArr;
@end
@implementation DHBinaryTree
- (void) insertNumber:(NSInteger) num{
	if (![self treeInArr]) {
		[self setTreeInArr:[NSMutableArray new]];
		[[self treeInArr] addObject:[[DHNode alloc] initWithNum:@(num)
													  NodeLeft:nil
													  NodeRight:nil]];
		return;
	}
	[self insertNumber:num CurrNode:[[self treeInArr] objectAtIndex:0]];
}
- (void) insertNumber:(NSInteger)num CurrNode:(DHNode *) node{
	if ([[node num] integerValue] > num) {
		if ([node left]) {
			[self insertNumber:num CurrNode:[node left]];
		}else{
			[node setLeft:[[DHNode alloc] initWithNum:@(num)
											 NodeLeft:nil
											NodeRight:nil]];
			[[self treeInArr] addObject:[node left]];
		}
	}else if ([[node num] integerValue] < num){
		if ([node right]) {
			[self insertNumber:num CurrNode:[node right]];
		}else{
			[node setRight:[[DHNode alloc] initWithNum:@(num)
											 NodeLeft:nil
											NodeRight:nil]];
			[[self treeInArr] addObject:[node right]];
		}
	}else{
		return;
	}
}
- (void) printTree{
	[self printTree:[[self treeInArr] objectAtIndex:0]];
}
- (void) printTree:(DHNode *) parent{
	if (parent == nil) {
		return;
	}
	[self printTree:[parent left]];
	printf("%ld, ", [[parent num] integerValue]);
	[self printTree:[parent right]];
}
@end
