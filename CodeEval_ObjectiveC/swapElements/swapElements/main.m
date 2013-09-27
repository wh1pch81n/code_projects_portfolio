//
//  main.m
//  swapElements
//
//  Created by Derrick Ho on 9/20/13.
//  Copyright (c) 2013 Derrick Ho. All rights reserved.
//

#import <Foundation/Foundation.h>

NSString *swapElements(NSString *line) {
	NSArray *listAndSwaps = [line componentsSeparatedByString:@":"];
	NSString *listStr = listAndSwaps[0];
	NSString *swaps = listAndSwaps[1];
	__block NSMutableArray *mListStr = [[listStr componentsSeparatedByString:@" "] mutableCopy];
	NSString *yourString = swaps;
	
	NSError *error = NULL;
	NSRegularExpression *regex = [NSRegularExpression regularExpressionWithPattern:@"([0-9]*)-([0-9]*)"
																		   options:NSRegularExpressionCaseInsensitive
																			 error:&error];
	[regex enumerateMatchesInString:yourString
							options:0
							  range:NSMakeRange(0, [yourString length])
						 usingBlock:^(NSTextCheckingResult *match, NSMatchingFlags flags, BOOL *stop){
							 NSArray *num2Swap = [[yourString substringWithRange:[match range]] componentsSeparatedByString:@"-"];
							 NSString *indexA = num2Swap[0];
							 NSString *indexB = num2Swap[1];
							 id temp = mListStr[indexA.integerValue];
							 mListStr[indexA.integerValue] = mListStr[indexB.integerValue];
							 mListStr[indexB.integerValue] = temp;
						 }];
	NSMutableString *ret = [NSMutableString new];
	for (NSString *s in mListStr) {
		if ([s isEqualToString:@""]) continue;
		[ret appendFormat:@"%@ ", s];
		
	}
	return ret;
}

int main(int argc, const char * argv[])
{

		NSString *fileStr = [NSString stringWithContentsOfFile:[NSString stringWithUTF8String:argv[1]]
													  encoding:NSASCIIStringEncoding
														 error:nil];
		for (NSString *line in [fileStr componentsSeparatedByString:@"\n"]) {
			if ([line isEqualToString:@""]) continue;
			//printf("%s ===== ", line.UTF8String);
			printf("%s\n", swapElements(line).UTF8String);
		}
	
    return 0;
}

