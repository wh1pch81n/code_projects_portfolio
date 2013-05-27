//
//  main.m
//  multiplesOfANumber
//
//  Created by Derrick Ho on 4/12/13.
//  Copyright (c) 2013 Derrick Ho. All rights reserved.
//

#import <Foundation/Foundation.h>
@interface MOAN : NSObject{
	
}
-(NSInteger) getMOAN:(NSInteger)x :(NSInteger)n;
@end
void run_prog( int argc, const char ** argv);
int main(int argc, const char * argv[])
{

	NSAutoreleasePool* pool= [NSAutoreleasePool new];
	{
	    run_prog(argc, argv);
	}
	[pool drain];
    return 0;
}

void run_prog( int argc, const char ** argv) {
	//char line[1024];
	char x[10];
	char n[10];
	FILE* f= fopen(argv[1], "r");
	if( !f){
		printf("Couldn't open file\n");
		exit(0);
	}
	while (2 == fscanf(f, "%[^,],%[^\n]\n", x, n)) {
		MOAN* temp = [MOAN new];
		printf("%ld\n", (long)[temp getMOAN:strtoul(x,NULL,10)  :strtoul(n,NULL,10) ]);
	}
}
@implementation MOAN
-(NSInteger) getMOAN:(NSInteger)x :(NSInteger)n{
	int i;
	for( i = 1; x > (n*i); ++i );
	
	return n*i;
}
@end
