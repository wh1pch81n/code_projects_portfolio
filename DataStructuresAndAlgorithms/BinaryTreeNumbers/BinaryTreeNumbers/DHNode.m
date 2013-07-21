//
//  DHNode.m
//  BinaryTreeNumbers_6_30_2013
//
//  Created by Derrick Ho on 6/30/13.
//  Copyright (c) 2013 Derrick Ho. All rights reserved.
//

#import "DHNode.h"

@implementation DHNode
-(id)initWithNum:(NSNumber *)num NodeLeft:(DHNode *)left NodeRight:(DHNode *)right{
	if (self = [super init]) {
		[self setNum:num];
		[self setLeft:left];
		[self setRight:right];
		return self;
	}
	return nil;
}
@end
