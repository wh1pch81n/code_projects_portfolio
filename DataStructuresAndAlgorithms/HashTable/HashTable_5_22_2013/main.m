//
//  main.m
//  HashTable_5_22_2013
//
//  Created by Derrick Ho on 5/22/13.
//  Copyright (c) 2013 Derrick Ho. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "DHKeyDataPair.h"

void testKeyDataPair();
int main(int argc, const char * argv[])
{

	@autoreleasepool {
		testKeyDataPair();
	}
    return 0;
}
void testKeyDataPair(){
	NSArray * arr = @[
				   [[DHKeyDataPair alloc] initWithKey:@"A" WithData:@"Andy"],
	   [[DHKeyDataPair alloc] initWithKey:@"B" WithData:@"Brandon"],
	   [[DHKeyDataPair alloc] initWithKey:@"C" WithData:@"Carmen"],
	   [[DHKeyDataPair alloc] initWithKey:@"D" WithData:@"Derrick"]
	   ];
	for (DHKeyDataPair* kdp in arr) {
		printf("%s, ", [[kdp getKey] UTF8String]);
	}
	printf("\n");
	
	for (DHKeyDataPair* kdp in arr) {
		printf("%s, ", [[kdp getData] UTF8String]);
	}
	
}
