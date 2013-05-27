//
//  main.m
//  PrimePalindrome
//
//  Created by Derrick Ho on 4/10/13.
//  Copyright (c) 2013 Derrick Ho. All rights reserved.
//

#import <Foundation/Foundation.h>
@interface PrimePalindrome: NSObject{
	
}
+(void) run_prog:(int) argc argumentVariables:(const char **) argv;
+(void) getPrimePaliThatIsLessThan:(int) thisNum;
@end

int main(int argc, const char * argv[])
{
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc]init];
	{
		[PrimePalindrome run_prog: argc
				argumentVariables: argv];
	}
	[pool drain];
	return 0;
}

@implementation PrimePalindrome
+(void) run_prog:(int) argc argumentVariables:(const char **) argv{
	[PrimePalindrome getPrimePaliThatIsLessThan:1000];
}
+(void) getPrimePaliThatIsLessThan:(int) thisNum{
	NSMutableArray * arrOfBools = [NSMutableArray array];
	//default every number to prime
	int i;
	for (i = 0; i < thisNum; ++i) {
		[arrOfBools addObject:@"isPrime"];
	}
	[arrOfBools replaceObjectAtIndex:0 withObject:@"notPrime"];
	[arrOfBools replaceObjectAtIndex:1 withObject:@"notPrime"];
	//filter out what is and what is not prime via Seive of Eratosthenes
	for (i = 2; i < thisNum; ++i) {
		if ([[arrOfBools objectAtIndex:i] isEqualTo:@"isPrime"]) {
			int j;
			for (j = i; (j*i) < thisNum; ++j) {
				[arrOfBools replaceObjectAtIndex:j*i withObject:@"notPrime"];
			}
		}
	}
	//for (NSString* s in arrOfBools) {
	//	static int num = 0;
	//	NSLog(@"%d %@", num++, s);
	//}
	
	//find the largest palendrime prime
	int j;
	BOOL found = false;
	for (j = (int)[arrOfBools count]-1; j > 1; --j) {
		found = true;
		if( [[arrOfBools objectAtIndex:j] isEqualTo:@"isPrime"]){
			//check if it is a palindromic
			NSString* s= [NSString stringWithFormat:@"%d", j];
			int left = 0;
			int right =(int) [s length]-1;
			for (; left < right; ++left, --right) {
				if([ s characterAtIndex:left] != [s characterAtIndex:right] ){
					found = false;
					break;
				}
			}
			if (found) {
				printf("%d\n", j);
				
				return;
			}
		}
	}
}
@end
