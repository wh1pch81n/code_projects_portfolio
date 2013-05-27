//
//  main.m
//  OddNumbers
//
//  Created by Derrick Ho on 4/23/13.
//  Copyright (c) 2013 Derrick Ho. All rights reserved.
//

#import <Foundation/Foundation.h>

int main(int argc, const char * argv[])
{

	NSAutoreleasePool* pool = [NSAutoreleasePool new];
	{
		NSInteger i;
	    for( i = 1; i < 100 ; i += 2){
			printf("%ld\n", i);
		}
	    
	}
	[pool drain];
    return 0;
}

