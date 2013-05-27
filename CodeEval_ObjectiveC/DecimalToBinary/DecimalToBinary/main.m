//
//  main.m
//  DecimalToBinary
//
//  Created by Derrick Ho on 5/7/13.
//  Copyright (c) 2013 Derrick Ho. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface DHfileReader : NSObject{
	FILE* f;
	char line[1024];
}
-(void) openFile:(const char*) filename;
-(void) closefile;
-(BOOL) wasOpenSuccessFull;
-(NSString*) getline;
@end
@implementation DHfileReader

-(void) openFile:(const char*) filename{
	f = fopen(filename, "r");
}
-(void) closefile{
	fclose(f);
}
-(BOOL) wasOpenSuccessFull{
	if(f){
		return YES;
	}
	return NO;
}
-(NSString*) getline{
	if(fgets(line, sizeof(line), f)){
	return [[NSString stringWithUTF8String: line] stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceAndNewlineCharacterSet]];
	}
return nil;
}


@end
//////////////////////
@interface Dec2Binary : NSObject
-(NSString*) d2b:(NSInteger) num;
@end
@implementation Dec2Binary

-(NSString*)d2b:(NSInteger)num{
	if (num == 0) {
		return @"";
	}
	return [NSString stringWithFormat:@"%@%ld" ,[self d2b:num>>1], num%2];
}

@end
int main(int argc, const char * argv[])
{

	NSAutoreleasePool * pool =[NSAutoreleasePool new];
	{
	Dec2Binary * x = [Dec2Binary new];
	DHfileReader * f = [DHfileReader new];
	[f openFile:argv[1]];
	if(![f wasOpenSuccessFull]){
		printf("Can't open file");
	}else{
		NSString * str = nil;
		while ( (str = [f getline] )) {
			if ([str integerValue]) {
				printf("%s\n", [[x d2b:[str integerValue]]UTF8String]);
			}else{
				printf("%d\n", 0);
			}
			
		}
	}
	[f closefile];
	}
	
	[pool drain];
    return 0;
}

