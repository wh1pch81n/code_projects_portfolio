//
//  NSMutableArray+SEARCH_CAT.m
//  HashTable_5_28_2013
//
//  Created by Derrick Ho on 5/26/13.
//  Copyright (c) 2013 Derrick Ho. All rights reserved.
//

#import "NSMutableArray+SEARCH_CAT.h"
#import "DHKeyDataPair.h"

@implementation NSMutableArray (SEARCH_CAT)
-(id) findDataBasedOnKey:(NSString *) key{
	for (DHKeyDataPair *cursor in self) {
		if ([[cursor key] isEqualToString:key]) {
			return [cursor data];
		}
	}
	return nil;
}
-(void) setDataBasedOnKey:(NSString *)key andData:(id)data{
		
	bool DataHasBeenSet = NO;
	for (DHKeyDataPair *cursor in self){
		if ([[cursor key] isEqualToString:key]) {
			[cursor setData:data];
			DataHasBeenSet = YES;
		}
	}
	if (DataHasBeenSet == NO ) {
		DHKeyDataPair *node = [[DHKeyDataPair alloc] initWithKey:key
														WithData:data];
		[self addObject:node];
	}

}
@end
