//
//  main.m
//  Word2Digit
//
//  Created by Derrick Ho on 8/29/13.
//  Copyright (c) 2013 Derrick Ho. All rights reserved.
//

#import <Foundation/Foundation.h>
void word2digit( const char *argv[]) {
	NSDictionary *dict = [[NSDictionary alloc] initWithObjectsAndKeys:
						  [NSNumber numberWithInt:0], @"zero",
						  [NSNumber numberWithInt:1], @"one",
						  [NSNumber numberWithInt:2], @"two",
						  [NSNumber numberWithInt:3], @"three",
						  [NSNumber numberWithInt:4], @"four",
						  [NSNumber numberWithInt:5], @"five",
						  [NSNumber numberWithInt:6], @"six",
						  [NSNumber numberWithInt:7], @"seven",
						  [NSNumber numberWithInt:8], @"eight",
						  [NSNumber numberWithInt:9], @"nine", nil];
	
	NSString *f = [NSString stringWithContentsOfFile:[NSString stringWithUTF8String:argv[1]]
											encoding:NSASCIIStringEncoding error:Nil];
	for (NSString *str in [f componentsSeparatedByString:@"\n"]) {
		if ([str isEqualToString:@""]) {	continue;	}
		for (NSString *num in [str componentsSeparatedByString:@";"]) {
			if ([str isEqualToString:@""]) { 	continue;}
			printf("%d", [[dict objectForKey:num] intValue]);
		}
		printf("\n");
	}
}
//////////////////////////////////////////////////////////
int main(int argc, const char * argv[])
{
	NSAutoreleasePool *pool = [NSAutoreleasePool new];
	word2digit(argv);
	[pool drain];
    return 0;
}

