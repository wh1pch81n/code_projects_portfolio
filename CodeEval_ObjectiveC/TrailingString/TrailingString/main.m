//
//  main.m
//  TrailingString
//
//  Created by Derrick Ho on 5/15/13.
//  Copyright (c) 2013 Derrick Ho. All rights reserved.
//

#import <Foundation/Foundation.h>
@protocol FileHandling
-(void)openFile:(const char*) argv;
-(void)closeFile;
-(bool)fail;
@end
@interface FileReader : NSObject <FileHandling>
{ FILE* f;}
+(id) FileReaderWithOpenFile:(const char*)argv;
//open file for reading
-(void)openFile:(const char*) argv ;
//close file 
-(void)closeFile;
//returns false if opening did not fail
-(bool)fail;
//takes in a string reference.  It will modify the given string
//via strRef.  returns a pointer to that string.
-(NSString*) getline:(NSString**) StrRef;
@end
@implementation FileReader
+(id) FileReaderWithOpenFile:(const char*)argv{
	id newInstance = [[[self class]alloc]init];
	[newInstance openFile:argv];
	return [newInstance autorelease];
}
-(void)openFile:(const char*) argv {
	f = fopen(argv, "r");
}
-(void)closeFile{
	fclose(f);
}
-(bool)fail{
	return (f)?NO:YES;
}
-(NSString*) getline:(NSString**) StrRef{
	char line[1024];
	return *StrRef = (fgets(line, sizeof(line), f))?	[NSString stringWithUTF8String:line]:nil;
}
@end
@interface DHTrailingString : NSObject
-(BOOL) isTrailingString:(NSString*) full;
@end
@implementation DHTrailingString
-(BOOL) isTrailingString:(NSString*) full{
	if ([full rangeOfString:@","].location == NSNotFound) {
		return NO;
	}
	NSArray* arr = [full componentsSeparatedByString:@"," ];
	return [self isTrailingString:[[arr objectAtIndex:0]
								   stringByTrimmingCharactersInSet:
								   [NSCharacterSet whitespaceAndNewlineCharacterSet]]
							Trail:[[arr objectAtIndex:1]
								   stringByTrimmingCharactersInSet:
								   [NSCharacterSet whitespaceAndNewlineCharacterSet]]
			];
}
-(bool) isTrailingString:(NSString*) body  Trail: (NSString*) tail{
	NSRange r =  [body rangeOfString:tail];
	if(r.location != NSNotFound){
		if (body.length == (r.location+r.length)) {
			return YES;
		}
	}
	return NO;
}
@end
	

int main(int argc, const char * argv[])
{
	NSAutoreleasePool * pool = [NSAutoreleasePool new];{
//		NSData* dataStream = [[NSFileManager defaultManager] contentsAtPath:[NSString stringWithUTF8String:argv[1]]];
		//		[dataStream ]
//		for( NSString * s in [[NSFileManager defaultManager] contentsOfDirectoryAtPath:[NSString stringWithUTF8String:argv[1]]
//																				 error:nil]){
//			printf("%s\n", [s UTF8String]);
//		}
		NSString* filepath = [NSString stringWithUTF8String:argv[1]];
		NSFileHandle * file = [NSFileHandle fileHandleForReadingAtPath:filepath];
		[file seekToFileOffset:0];//begining of file
		NSData* TheWholeFileContents = [file readDataToEndOfFile];
		NSArray* alsoTheWholeFileContents = [NSArray arrayWithContentsOfFile:filepath];
		for( NSString* s in alsoTheWholeFileContents){
			printf("%s\n", [s UTF8String]);
		}
		NSString* fcon = [NSString stringWithContentsOfFile:filepath
												   encoding:NSASCIIStringEncoding error:nil];
		NSString* aa = [[NSString alloc] initWithData:TheWholeFileContents
											 encoding:NSASCIIStringEncoding];
		NSArray* bb = [fcon componentsSeparatedByString:@"\n"];
		
		FileReader* f = [FileReader FileReaderWithOpenFile:argv[1]];
		if ([f fail]) {
			printf("probs...\n");
			goto DRAIN;
		}
		NSString* str = nil;
		NSString* s = nil;
		while ( (s=[f getline:&str]) ) {
			printf("%d\n", [[DHTrailingString new] isTrailingString: str]);
		}
	DRAIN:
		[f closeFile];
	}
	
	[pool drain];
    return 0;
}

