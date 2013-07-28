//
//  DHLowestCommonMultiple.h
//  5_SmallestMultiple
//
//  Created by Derrick Ho on 7/28/13.
//  Copyright (c) 2013 Derrick Ho. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface DHLowestCommonMultiple : NSObject
- (id)initWithArrayOfNumbers:(NSArray *)arr;
@property(strong, nonatomic) NSNumber *lcm;
@end
