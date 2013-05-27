//
//  main.m
//  bitPositions
//
//  Created by Derrick Ho on 4/13/13.
//  Copyright (c) 2013 Derrick Ho. All rights reserved.
//

#import <Foundation/Foundation.h>
@interface bitPositions: NSObject{}
+(void)getBitPositions:(char*)n p1:(char*)p1 p2:(char*)p2;
@end
void run_prog(int argc, const char ** argv);


int main(int argc, const char * argv[])
{
	NSAutoreleasePool* pool = [NSAutoreleasePool new];
	run_prog(argc, argv);
	[pool drain];
    return 0;
}
@implementation bitPositions
+(void)getBitPositions:(char *)n p1:(char *)p1 p2:(char *)p2{
	[bitPositions getBitPositions2:strtol(n, NULL, 10)
								p1:strtol(p1, NULL, 10)-1
								p2:strtol(p2, NULL, 10)-1];
}
+(void)getBitPositions2:(NSInteger)n p1:(NSInteger)p1 p2:(NSInteger)p2{
	//printf("%lx %x %lx\n", n, (1) << p1,(n & (1 << p2)) );
	//printf("%lx %x %lx\n", n, (1) << p1,(n & (1 << p2)) );

	if ( ((n & (1 << p1))==0) ^ ((n & (1 << p2))==0) ) {
		printf("false\n");
	}else{
		printf("true\n");
	}
}

@end
void run_prog(int argc, const char** argv){
	char A[10];
	char B[10];
	char C[10];
	FILE * f= fopen(argv[1], "r");
	if( !f){
		printf("can't open file");
		exit(0);
	}
	while (3 == fscanf(f, "%[^,],%[^,],%[^\n]\n", A, B, C)) {
		[bitPositions getBitPositions:A  p1:B  p2:C ];
	}
	
}