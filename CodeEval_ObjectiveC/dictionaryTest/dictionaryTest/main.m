//
//  main.m
//  dictionaryTest
//
//  Created by Derrick Ho on 5/17/13.
//  Copyright (c) 2013 Derrick Ho. All rights reserved.
//

#import <Foundation/Foundation.h>

int main(int argc, const char * argv[])
{

	NSAutoreleasePool* pool = [NSAutoreleasePool new]; {
		NSString* file = [NSString stringWithContentsOfFile:
												   [NSString stringWithUTF8String:argv[1]]
												   encoding:NSASCIIStringEncoding
													  error:NULL];
		NSArray* filearr = [file componentsSeparatedByString:@"\n"];
		for (NSString* line in filearr) {
			if ([line isEqualToString:@""]) continue;
			NSArray* split = [line componentsSeparatedByString:@"|"];
			NSMutableDictionary* md = [[NSMutableDictionary new] autorelease];
			for (int i = 0; i < [split[0] length]; ++i) 
				md[ [NSNumber numberWithInt:i+1]] = [line substringWithRange:NSMakeRange(i, 1)];
			for (NSString* s in [split[1] componentsSeparatedByString:@" "]) {
				if( [s isEqualToString:@""]) continue;
				printf("%s",[md[ [NSNumber numberWithInteger:[s integerValue]]] UTF8String]);
			}printf("\n");
			
		}
	}
	[pool drain];
    return 0;
}

