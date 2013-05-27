//
//  DHKeyDataPair.h
//  HashTable_5_28_2013
//
//  Created by Derrick Ho on 5/26/13.
//  Copyright (c) 2013 Derrick Ho. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface DHKeyDataPair : NSObject
@property(strong, nonatomic) id key;
@property(strong, nonatomic) id data;
-(id) init;
-(id) initWithKey:(NSObject*) key WithData:(NSObject*) data;
@end
