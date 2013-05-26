//
//  DHHash.m
//  HashTable
//
//  Created by Derrick Ho on 5/22/13.
//  Copyright (c) 2013 Derrick Ho. All rights reserved.
//

#import "DHHash.h"
#import "DHKeyDataPair.h"

@implementation DHHash
-(id)initWithSize:(NSInteger)size{
	if (!(self = [super init])) {
		return nil;
	}
	//initialization stuff
	hashTable = [NSMutableArray new];
	for (int i = 0; i < size ; ++i) {
		hashTable[i] = [NSMutableArray new];
	}
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
	DHKeyDataPair *node = [[DHKeyDataPair alloc] initWithKey:key
									   WithData:data];
	NSNumber *ind = [self hashFunction:key];
	NSInteger index = [ind integerValue];
	
	bool DataHasBeenSet = NO;
	for (DHKeyDataPair *cursor in hashTable[index]){
		if ([[cursor key] isEqualToString:key]) {
			[cursor setData:data];
			DataHasBeenSet = YES;
		}
	}
	if (DataHasBeenSet == NO ) {
		[hashTable[index] addObject:node];
	}
}
-(id)findDataFromLList:(NSString *)key{
	
}
-(id)findDataFromKey:(NSString *)key{
	
}
@end
