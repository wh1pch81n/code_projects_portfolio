//
//  main.m
//  panagrams
//
//  Created by Derrick Ho on 4/27/13.
//  Copyright (c) 2013 Derrick Ho. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface ifstream : NSObject{
	NSArray* _fileArr;
	NSInteger _currLine;
}
-(void)fileOpenPath:(const char*) argv openForWhatAction:(const char*) RW;
-(BOOL)fail;

-(NSString*)getLine;

@end

@interface panagram : NSObject
+(NSString*)getMissingLetters:(NSString*) str;
@end

int main(int argc, const char * argv[])
{

	NSAutoreleasePool * pool = [NSAutoreleasePool new];
	{
		ifstream * ifile = [ifstream new];
		[ifile fileOpenPath:argv[1] openForWhatAction:"r"];
		if([ifile fail]){
			printf("can't open file\n");
		}else{
			NSString * str = nil;
			while ((str = [ifile getLine])) {
				//printf("%s", [str UTF8String]);
				printf("%s\n", [[panagram getMissingLetters:str] UTF8String]);
			}
		}
	}
	[pool drain];
    return 0;
}

@implementation ifstream
-(void)fileOpenPath:(const char*) argv openForWhatAction:(const char*) RW{
	_currLine = 0;
	char line[1024];
	FILE * f = fopen(argv, RW);
	NSMutableArray* marr = [NSMutableArray new];
	if(!f ){
		_fileArr = nil;
	}else{
		while (fgets(line, sizeof(line), f)) {
			[marr addObject:[[NSString stringWithFormat:@"%s", line]
										   stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceAndNewlineCharacterSet]]];
			
		}
		_fileArr = marr;
	}
}
-(BOOL)fail{
	if (_fileArr == nil) {
		return YES;
	}else{
		return NO;
	}
}

-(NSString*)getLine{
	if (_currLine < _fileArr.count) {
		return [_fileArr objectAtIndex:_currLine++];
	}else{
		return nil;
	}
}

@end

@implementation panagram
+(NSString*)getMissingLetters:(NSString*) str{
	NSString* answer= @"";
	BOOL arr[26]={};
	char c;
	NSInteger i;
	for (i = 0; i < [str length]; ++i) {
		c = [str characterAtIndex:i] | 0x20;
		if( c >= 'a' && c <= 'z'){
			arr[c-'a'] = YES;
		}
	}
	for (i = 0; i < sizeof(arr); ++i) {
		if( arr[i] == NO){
			answer =[answer stringByAppendingFormat:@"%c",(char )('a' + i)];
		}
	}
	return ([answer isEqualToString: @""])? @"NULL": answer;
}
@end