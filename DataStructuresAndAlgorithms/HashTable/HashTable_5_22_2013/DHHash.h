//
//  DHHash.h
//  HashTable
//
//  Created by Derrick Ho on 5/22/13.
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
