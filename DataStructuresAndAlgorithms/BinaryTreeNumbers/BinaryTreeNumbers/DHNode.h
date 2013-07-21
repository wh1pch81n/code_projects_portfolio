//
//  DHNode.h
//  BinaryTreeNumbers_6_30_2013
//
//  Created by Derrick Ho on 6/30/13.
//  Copyright (c) 2013 Derrick Ho. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface DHNode : NSObject
@property (strong, nonatomic) NSNumber *num;
@property (strong, nonatomic) DHNode *left;
@property (strong, nonatomic) DHNode *right;
-(id) initWithNum:(NSNumber *)num NodeLeft:(DHNode *)left NodeRight:(DHNode *) right;
@end
