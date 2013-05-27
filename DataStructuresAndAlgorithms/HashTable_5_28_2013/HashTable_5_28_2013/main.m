//
//  main.m
//  HashTable_5_28_2013
//
//  Created by Derrick Ho on 5/26/13.
//  Copyright (c) 2013 Derrick Ho. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "DHKeyDataPair.h"
#import "DHHash.h"
void hashReader( DHHash *hash, NSString *key);
void testHash();
void testKeyDataPair();
int main(int argc, const char * argv[])
{

	@autoreleasepool {
		testKeyDataPair();
		printf("=====================\n");
		testHash();
	}
    return 0;
}
void testHash(){
	DHHash *hash = [[DHHash alloc] initWithSize:11 prime:11];
	[hash addIntoHashAKey:@"andy" AData:@"msp protoge"];
	[hash addIntoHashAKey:@"brandon" AData:@"the cocky bastard"];
	[hash addIntoHashAKey:@"carmen" AData:@"sister at south bay honda"];
	[hash addIntoHashAKey:@"derrick" AData:@"the programmer"];
	
	hashReader( hash, @"derrick");
	hashReader( hash, @"carmen");
	hashReader( hash, 0);
	hashReader( hash, @"brandon");
	
}
void hashReader( DHHash *hash, NSString *key){
	id data = [hash findDataFromKey:key];
	if( [data isKindOfClass:[NSString class]]){
		printf("%s : %s\n", [key UTF8String], [data UTF8String]);
	}else if( [data isKindOfClass:[NSNumber class]]){
		printf("%s : %ld\n", [key UTF8String], [data integerValue]);
	}
}
void testKeyDataPair(){
	NSArray * arr = @[
				   [[DHKeyDataPair alloc] initWithKey:@"A" WithData:@"Andy"],
	   [[DHKeyDataPair alloc] initWithKey:@"B" WithData:@"Brandon"],
	   [[DHKeyDataPair alloc] initWithKey:@"C" WithData:@"Carmen"],
	   [[DHKeyDataPair alloc] initWithKey:@"D" WithData:@"Derrick"]
	   ];
	for (DHKeyDataPair* kdp in arr) {
		printf("%s, ", [[kdp key] UTF8String]);
	}
	printf("\n");
	
	for (DHKeyDataPair* kdp in arr) {
		printf("%s, ", [[kdp data] UTF8String]);
	}
	
}

