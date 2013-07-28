//
//  DHPair.h
//  5_SmallestMultiple
//
//  Created by Derrick Ho on 7/28/13.
//  Copyright (c) 2013 Derrick Ho. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface DHPair : NSObject
@property(strong, nonatomic) id leftOfPair;
@property(strong, nonatomic) id rightOfPair;
- (id)initWithLeftOfPair:(id)left rightOfPair:(id)right;
- (id)init;
@end
