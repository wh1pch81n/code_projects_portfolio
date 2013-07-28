//
//  main.m
//  3_largestPrimeFactor
//
//  Created by Derrick Ho on 7/28/13.
//  Copyright (c) 2013 Derrick Ho. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "../../5_SmallestMultiple/5_SmallestMultiple/listOfPrimes10k.h"


int main(int argc, const char * argv[])
{

	@autoreleasepool {
	    NSInteger num = 600851475143;
		NSInteger i;
		for (i = 0; cListOfPrimes10k[i] != EndOfPrimeList; ++i);
		for (--i; i > 0; --i){
			if (num % cListOfPrimes10k[i] == 0) {
				break;
			}
		}
		printf("%d", cListOfPrimes10k[i]);
	}
    return 0;
}

