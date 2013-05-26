//
//  DHNode.h
//  HashTable
//
//  Created by Derrick Ho on 5/22/13.
//  Copyright (c) 2013 Derrick Ho. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "DHKeyDataPair.h"
@interface DHNode : DHKeyDataPair
@property( strong, nonatomic) DHNode * nextDHNode;
@end
