//
//  main.m
//  BinaryTreeNumbers
//
//  Created by Derrick Ho on 6/30/13.
//  Copyright (c) 2013 Derrick Ho. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "DHBinaryTree.h"
int main(int argc, const char * argv[])
{

	@autoreleasepool {
		DHBinaryTree *tree =  [DHBinaryTree new];
		for (int i = 0; i < 10; ++i) {
			[tree insertNumber:(arc4random()*101) % 100];
		}
		[tree printTree];
	}
    return 0;
}

