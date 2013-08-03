//
//  main.m
//  SieveTest
//
//  Created by Derrick Ho on 8/2/13.
//  Copyright (c) 2013 Derrick Ho. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "sieve_of_eratosthenes.h"


int main(int argc, const char * argv[])
{

	@autoreleasepool {
	    
	    // insert code here...
		NSLog(@"hello world");
	    DHsieveOfEratosthenes *a = [[DHsieveOfEratosthenes alloc] init];
	    NSLog(@"%@", [a generateSieveUpTo:@(2000000)]);
	}
    return 0;
}

