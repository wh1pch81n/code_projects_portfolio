//
//  main.m
//  9_pythagorean_Triplet
//
//  Created by Derrick Ho on 8/3/13.
//  Copyright (c) 2013 Derrick Ho. All rights reserved.
//

#import <Foundation/Foundation.h>

int main(int argc, const char * argv[])
{

	@autoreleasepool {
		for (int a =1; a < 1000; ++a) {
			for (int b =1; b < 1000; ++b) {
				for (int c =1; c < 1000; ++c) {
					if (a < b && b < c){
						if (a*a + b*b == c*c) {
							if (a + b + c == 1000) {
								printf("pythagorean Triplet: %d", a*b*c);
								return 0;
							}
						}
					}
				}
			}
		}
	  	    
	}
    return 0;
}

