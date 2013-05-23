//
//  DHKeyDataPair.h
//  HashTable
//
//  Created by Derrick Ho on 5/22/13.
//  Copyright (c) 2013 Derrick Ho. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface DHKeyDataPair : NSObject{
	NSArray * pairArr;
}
@property ( strong, nonatomic) NSObject * key;
@property ( strong, nonatomic) NSObject * data;
-(id) init;
-(id) initWithKey:(NSObject*) key WithData:(NSObject*) data;
@end
