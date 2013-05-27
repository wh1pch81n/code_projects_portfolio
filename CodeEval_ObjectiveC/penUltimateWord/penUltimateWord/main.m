//
//  main.m
//  penUltimateWord
//
//  Created by Derrick Ho on 4/24/13.
//  Copyright (c) 2013 Derrick Ho. All rights reserved.
//

#import <Foundation/Foundation.h>

int main(int argc, const char * argv[])
{

	NSAutoreleasePool * pool= [NSAutoreleasePool new];{
	    char line[1024];
		FILE * f = fopen(argv[1], "r");
		if( !f){
			printf("can't open file\n");
			exit(0);
		}
		while (fgets(line, sizeof(line), f)) {
			if(line[0] == '\n') continue;
			
			NSArray * arrOfWords =[[[NSString stringWithFormat:@"%s", line
									 ]stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceAndNewlineCharacterSet]
									]componentsSeparatedByString:@" "];
		
			printf("%s\n", [[arrOfWords objectAtIndex: arrOfWords.count-2] UTF8String]);
		}
	    	  
	}
	[pool drain];
    return 0;
}

