//
//  main.m
//  reverse_words_order
//
//  Created by Derrick Ho on 4/11/13.
//  Copyright (c) 2013 Derrick Ho. All rights reserved.
//

#import <Foundation/Foundation.h>
@interface reverseWordsOrder: NSObject{
	NSMutableArray * marr;
}
-(void) run_prog:(int)argc :(const char**)argv;
-(void) reverse:(NSString*) s;

//@property(nonatomic, strong) NSMutableArray * marr;
@end

int main(int argc, const char * argv[])
{
	NSAutoreleasePool * pool = [NSAutoreleasePool new];
	
	[[reverseWordsOrder new] run_prog:argc :argv];
	[pool drain];
    return 0;
}
@implementation reverseWordsOrder
//@synthesize marr ;

-(void) run_prog:(int)argc :(const char **)argv{
	char line[1024];
	FILE * f = fopen(argv[1], "r");
	if(!f){
		printf("Could not open File...\n");
		exit(0);
	}
	marr = [NSMutableArray new];
	while (fgets(line, sizeof(line), f)) {
		if (line[0] == '\n') {
			continue;
		}
		[self reverse: [NSString stringWithFormat:@"%s", line]];
	}
}
-(void) reverse:(NSString *) str{
	NSString* striped_string = [str stringByTrimmingCharactersInSet:
								[NSCharacterSet whitespaceAndNewlineCharacterSet] ];
	NSArray* split_arr =[striped_string componentsSeparatedByString:@" "];
	NSInteger i;
	for (i = split_arr.count -1; i >= 0; --i ) {
		printf("%s ", [[split_arr objectAtIndex:i] UTF8String] );
		//NSLog(@"%@ ", [split_arr objectAtIndex:i]  );
	}printf("\n");
}
@end
