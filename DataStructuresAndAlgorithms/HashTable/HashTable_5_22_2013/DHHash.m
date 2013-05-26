//
//  DHHash.m
//  HashTable
//
//  Created by Derrick Ho on 5/22/13.
//  Copyright (c) 2013 Derrick Ho. All rights reserved.
//

#import "DHHash.h"
#import "DHNode.h"

@implementation DHHash
-(id)initWithSize:(NSInteger)size{
	if (!(self = [super init])) {
		return nil;
	}
	//initialization stuff
	hashTable = [NSMutableArray arrayWithObjects:nil
										   count:size];
	return self;
}
-(NSNumber *)hashFunction:(NSString *)key{
	const long primeNumber = 3571;//101;
	NSInteger sum = 0;
	for (int i = 0; i < [key length]; ++i) {
		sum += [key characterAtIndex:i ];
	}
	return [NSNumber numberWithInteger:sum % primeNumber];
}
-(void)addIntoHashAKey:(NSString *)key AData:(id)data{
	DHNode *node = [[DHNode alloc] initWithKey:key
									   WithData:data];
	NSNumber *ind = [self hashFunction:key];
	NSInteger index = [ind integerValue];
	if ( hashTable[ index] == nil) {//index is empty so just fill it
		hashTable[ index] = node;
	}else{
		//there is a possible linked list so I must go through each
		DHNode *cursor = hashTable[ index];
		while ( YES) {
			if ( [[cursor key] isEqualToString:key]){
				//if the key is the same, then replace the data
				[cursor setData:data];
				break;
			}else if ([cursor nextDHNode] == nil) {
				//add to the end
				[cursor setNextDHNode:node];
				break;
			}
			//move to the next
			cursor = [cursor nextDHNode];
		}
	}
}
-(id)findDataFromLList:(NSString *)key{
	
}
-(id)findDataFromKey:(NSString *)key{
	
}
@end
