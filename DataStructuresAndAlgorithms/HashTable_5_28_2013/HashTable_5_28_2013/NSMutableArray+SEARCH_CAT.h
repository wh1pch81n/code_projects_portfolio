//
//  NSMutableArray+SEARCH_CAT.h
//  HashTable_5_28_2013
//
//  Created by Derrick Ho on 5/26/13.
//  Copyright (c) 2013 Derrick Ho. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSMutableArray (SEARCH_CAT)
-(id) findDataBasedOnKey:(NSString *)s;
-(void) setDataBasedOnKey:(NSString *)key andData:(id) data;
@end
