//
//  main.m
//  12.1_highlyDivisible
//
//  Created by Derrick Ho on 8/4/13.
//  Copyright (c) 2013 Derrick Ho. All rights reserved.
//

#import <Foundation/Foundation.h>
/*
 Found this brute force algorithm online:
 http://www.mathblog.dk/triangle-number-with-more-than-500-divisors/
 */
NSInteger numberOfDivisors(NSInteger number) {
	int nod = 0;
    int sqrt = (int)sqrtl(number);
	
    for(int i = 1; i<= sqrt; ++i){
        if(number % i == 0){
            nod += 2;
        }
    }
    //Correction if the number is a perfect square
    if (sqrt * sqrt == number) {
        nod--;
    }
    return nod;
}

int main(int argc, const char * argv[])
{

	@autoreleasepool {
	    int i;
		for ( i = 1; numberOfDivisors(i*(i + 1)/2) < 500; ++i);
	    printf("%d", i*(i + 1)/2);
	}
    return 0;
}

