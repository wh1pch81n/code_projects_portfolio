//
//  main.m
//  4_LargestPalindromeProduct
//
//  Created by Derrick Ho on 7/28/13.
//  Copyright (c) 2013 Derrick Ho. All rights reserved.
//
/*
 A palindromic number reads the same both ways. The largest palindrome made from the product of two 2-digit numbers is 9009 = 91  99.
 
 Find the largest palindrome made from the product of two 3-digit numbers.
 */
#import <Foundation/Foundation.h>
#import "../../5_SmallestMultiple/5_SmallestMultiple/listOfPrimes10k.h"

BOOL isPalindromicNumber(NSInteger n){//this should detect prime, but not doesn't detect palindrome
	NSString *numAsString = [NSString stringWithFormat:@"%ld", n];
	char *number = [numAsString UTF8String];
	int L = 0;
	int R = [numAsString length] - 1;
	for (; L < R; L++, R--) {
		if (number[L] != number[R]) {
			return NO;
		}
	}
	return YES;
}

NSInteger largestPalindromicProduct(int i, int j){
	NSInteger largestPali = 0;
	for (int m = i;m > 0; --m) {
		for (int n = j;n > 0; --n) {
			if (isPalindromicNumber(m*n)) {
				largestPali = (largestPali < m*n)?m*n:largestPali;
			}else{
				//printf("%d * %d = %d;not paliPrime\n", m, n, m*n);
			}
		}
	}
	return largestPali;
}

int main(int argc, const char * argv[])
{

	@autoreleasepool {
	    
	    // insert code here...
	    NSLog(@"%ld", largestPalindromicProduct(999, 999));
	    
	}
    return 0;
}

