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
-(id)initWithSize:(NSInteger)s prime:(NSInteger)p{
	if (!(self = [super init])) {
		return nil;
	}
	//initialization stuff
	self->size = s;
	self->prime = p;
	self->hashTable = [NSMutableArray new];
	for (int i = 0; i < self->size ; ++i) {
		[hashTable addObject:[NSMutableArray new]];
	}
	return self;
}
-(NSNumber *)hashFunction:(NSString *)key{
	NSInteger sum = 0;
	for (int i = 0; i < [key length]; ++i) {
		sum += [key characterAtIndex:i ];
	}
	return [NSNumber numberWithInteger:(sum * self->prime) % self->size];
}
-(void)addIntoHashAKey:(NSString *)key AData:(id)data{
	DHKeyDataPair *node = [[DHKeyDataPair alloc] initWithKey:key
									   WithData:data];
	NSNumber *ind = [self hashFunction:key];
	NSInteger index = [ind integerValue] ;
	
	bool DataHasBeenSet = NO;
	NSMutableArray *listOfPairs = hashTable[index];
	for (DHKeyDataPair *cursor in listOfPairs){
		if ([[cursor key] isEqualToString:key]) {
			[cursor setData:data];
			DataHasBeenSet = YES;
		}
	}
	if (DataHasBeenSet == NO ) {
		[hashTable[index] addObject:node];
	}
}
-(id)findDataFromKey:(NSString *)key{
	NSInteger index = [[self hashFunction:key] integerValue];
	NSMutableArray *listOfPairs = hashTable[index];
	for (DHKeyDataPair *cursor in listOfPairs) {
		if ([[cursor key] isEqualToString:key]) {
			return [cursor data];
		}
	}
	return nil;
}
@end
