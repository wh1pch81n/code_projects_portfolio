//
//  main.m
//  MultiplicationTable
//
//  Created by Derrick Ho on 4/17/13.
//  Copyright (c) 2013 Derrick Ho. All rights reserved.
//

#import <Foundation/Foundation.h>
@interface MultTable: NSObject
+(void) makeTableWithCol:(NSInteger) col withRow:(NSInteger) row;
@end

int main(int argc, const char * argv[])
{

	NSAutoreleasePool* pool = [NSAutoreleasePool new];
	{
	    [MultTable makeTableWithCol:12 withRow:12];
	 
	}
	[pool drain];
    return 0;
}

@implementation MultTable

+(void) makeTableWithCol:(NSInteger)col withRow:(NSInteger)row{
	NSInteger x, y;
	
	for (y = 1; y <= row; ++y ) {
		for( x = 1; x <= col; ++x){
			printf("%4ld", x*y);
		}printf("\n");
	}
	
}

@end