//
//  main.m
//  FindAWriter
//
//  Created by Derrick Ho on 5/16/13.
//  Copyright (c) 2013 Derrick Ho. All rights reserved.
//

#import <Foundation/Foundation.h>

int main(int argc, const char * argv[])
{

	NSAutoreleasePool * pool = [NSAutoreleasePool new];
	{
	NSError* err = nil;
	NSString* filecontents = [NSString stringWithContentsOfFile:
							  [NSString stringWithUTF8String:argv[1]]
													   encoding:NSASCIIStringEncoding error:&err];
	if(filecontents != nil){
		NSArray* fileArr = [filecontents componentsSeparatedByCharactersInSet:
							[NSCharacterSet newlineCharacterSet]];
		for (NSString* line in fileArr) {
			if ([ line isEqualToString:@""]) {
				continue;
			}
			NSCharacterSet * whitespaceandNL = [NSCharacterSet whitespaceAndNewlineCharacterSet];
			NSArray* split =[line componentsSeparatedByString:@"|"] ;
			NSString* sp[2] = { [split objectAtIndex:0], [split objectAtIndex:1] };
			sp[0] = [sp[0] stringByTrimmingCharactersInSet:whitespaceandNL];
			sp[1] = [sp[1] stringByTrimmingCharactersInSet:whitespaceandNL];
//			NSString * obj = [split objectAtIndex:0];
//			obj = [obj stringByTrimmingCharactersInSet:whitespaceandNL];
			
//			NSString* obj2 = [split objectAtIndex:1];
//			obj2 = [obj2 stringByTrimmingCharactersInSet:whitespaceandNL];
			
			NSArray* nums = [sp[1] componentsSeparatedByString:@" "];//[obj2 componentsSeparatedByString:@" "];
		
			NSString* name = @"";
			for (NSString* s in nums) {
				name = [name stringByAppendingFormat:@"%c",
						[sp[0] characterAtIndex:[s integerValue]-1]];
//				[name appendFormat:@"%c", [obj characterAtIndex:[s integerValue]-1] ];
			}
			printf("%s\n", [name UTF8String]);
		}
	}else{
		NSLog(@"couldn't open file...");
	}
	    
	    
	}
	[pool drain];
    return 0;
}

