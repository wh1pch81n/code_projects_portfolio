//
//  main.m
//  SwapCase
//
//  Created by Derrick Ho on 5/8/13.
//  Copyright (c) 2013 Derrick Ho. All rights reserved.
//

#import <Foundation/Foundation.h>
/*  a class that reads the file kind of like ifstream*/
@interface CEFileReader : NSObject{
@private
	FILE* _f;
}
-(void)openFileStream:(const char*)path;
-(NSString*)getlineAndInc;
-(BOOL)didFailToOpen;
-(void)closeFileStream;
@end
@implementation CEFileReader
-(void)openFileStream:(const char*)path{
	_f = fopen(path, "r");
}
-(NSString*)getlineAndInc{
	char line[1024];
	if (fgets(line, sizeof(line), _f)) {
		return [[NSString stringWithFormat:@"%s", line] stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceAndNewlineCharacterSet]];
	}
	return nil;
}
-(BOOL)didFailToOpen{
	return (!_f)?YES: NO;
}
-(void)closeFileStream{
	fclose(_f);
}
@end
////////////////////////////////////////
int main(int argc, const char * argv[])
{

	NSAutoreleasePool* pool = [NSAutoreleasePool new];{
		CEFileReader * f = [CEFileReader new];
		[f openFileStream:argv[1]];
		if ([f didFailToOpen]) {
			printf("Can't open file\n");
		}else{
			NSString* s = nil;
			for (;(s =[f getlineAndInc]); printf("\n")) {
				int i;
				for (i =0; i < s.length; ++i) {
					char c = [s characterAtIndex:i];
					if ((c >= 'a' && c <= 'z') ||
						(c >= 'A' && c <= 'Z')) {
						if (c & 0x20) { c &= ~0x20;
						}else{	 c |= 0x20;
						}
					}
					printf("%c", c);
				}
			}
		}
	}
	[pool drain];
	return 0;
}
	
