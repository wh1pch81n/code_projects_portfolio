//
//  main.m
//  CapitalizeFirstLetterOfWords
//
//  Created by Derrick Ho on 4/25/13.
//  Copyright (c) 2013 Derrick Ho. All rights reserved.
//

#import <Foundation/Foundation.h>
@interface CapitalizeFirstLetterOfWords: NSObject{
	NSArray * _arrOfLines;
	NSInteger _numLines;
}
-(void) makeArrayofLines: (NSString*) str;
-(NSString*) getCapitalizedLineAtIndex:( NSInteger) num;
-(NSInteger) getNumLines;
//@property(nonatomic, strong) NSArray * arrOfLines;
//@property(nonatomic, strong) NSInteger numLines;
@end

int main(int argc, const char * argv[])
{

	NSAutoreleasePool * pool = [NSAutoreleasePool new];
	{
	    NSString * path = [NSString stringWithFormat:@"%s",  argv[1]];
		NSStringEncoding enc;
		NSError * err;
		NSString * fileContents = [NSString stringWithContentsOfFile:path
															usedEncoding: &enc
															   error: &err];
		//if (err) {
		//	printf(" problems opening file\n");
		//}else{
			//printf("%s", [fileContents UTF8String]);
			CapitalizeFirstLetterOfWords* it = [CapitalizeFirstLetterOfWords new];
			[it makeArrayofLines:fileContents];
			int i;
			for( i = 0; i < [it getNumLines]; ++i){
				
				printf("%s\n",[[it getCapitalizedLineAtIndex:i] UTF8String] );
			}
		//}
		
	}
    [pool drain];
	return 0;
}

@implementation CapitalizeFirstLetterOfWords
//@synthesize numLines = _numLines;
//@synthesize arrOfLines = _arrOfLines;

-(void) makeArrayofLines: (NSString*) str{
	_arrOfLines = [str componentsSeparatedByCharactersInSet:[NSCharacterSet newlineCharacterSet]];
	_numLines = [_arrOfLines count];
}
-(NSString*) getCapitalizedLineAtIndex:( NSInteger) num{
	NSArray * line = [[[NSString stringWithString:[_arrOfLines objectAtIndex:num]]
					  stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceAndNewlineCharacterSet]]
					  componentsSeparatedByString:@" "];
	NSMutableString * mstr = [NSMutableString new];
	for (NSString* word in line) {
		char c = [word UTF8String][0];
		if( c >= 'a' && c <= 'z') c &= ~0x20;
		[mstr appendFormat:@"%c%@ ", c, [word substringFromIndex:1]];
	}
	return mstr;
}
-(NSInteger) getNumLines{
	return [_arrOfLines count];
}
@end