//
//  DHPair.m
//  5_SmallestMultiple
//
//  Created by Derrick Ho on 7/28/13.
//  Copyright (c) 2013 Derrick Ho. All rights reserved.
//

#import "DHPair.h"
@interface DHPair ()
@end

@implementation DHPair
- (id)initWithLeftOfPair:(id)left rightOfPair:(id)right {
	if (!(self = [super init])) {
		return nil;
	}
	//initialization code in here
	[self setLeftOfPair:left];
	[self setRightOfPair:right];
	return self;
}
- (id)init {
	return [self initWithLeftOfPair:nil rightOfPair:nil];
}
@end
