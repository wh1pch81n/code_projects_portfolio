//
//  DHKeyDataPair.h
//  HashTable
//
//  Created by Derrick Ho on 5/22/13.
//  Copyright (c) 2013 Derrick Ho. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface DHKeyDataPair : NSObject
@property(strong, nonatomic) id key;
@property(strong, nonatomic) id data;
-(id) init;
-(id) initWithKey:(NSObject*) key WithData:(NSObject*) data;
@end
