//
//  DHHash.h
//  HashTable_5_28_2013
//
//  Created by Derrick Ho on 5/26/13.
//  Copyright (c) 2013 Derrick Ho. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface DHHash : NSObject{
	NSMutableArray* hashTable;
	NSInteger size;
	NSInteger prime;
}
-(id)initWithSize:(NSInteger)size prime:(NSInteger) prime;
-(void)addIntoHashAKey:(NSString *)key AData:(id)data;
-(id)findDataFromKey:(NSString *)key;
@end
