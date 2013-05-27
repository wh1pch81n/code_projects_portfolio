//
//  main.m
//  FizzBuzz_Objc
//
//  Created by Derrick Ho on 4/9/13.
//  Copyright (c) 2013 Derrick Ho. All rights reserved.
//

#import <Foundation/Foundation.h>
@interface fizzBuzz : NSObject{
	
}
+(void) firstDiv:(NSInteger) A secondDiv:(NSInteger)B length:(NSInteger)C;
@end


void run_prog(const int argc, const char** argv);
int main(int argc, const char * argv[])
{
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	{
		run_prog(argc, argv);
	}
	[pool drain];
    return 0;
}
void run_prog(const int argc, const char ** argv){
	char A[3];
	char B[3];
	char C[3];
	FILE*f= fopen(argv[1], "r");
	if((!f) || (argc != 2)){
		printf("problem opening file...");
		exit(0);
	}
	while (3 == fscanf(f, "%s %s %s", A , B, C)) {
		NSInteger div1 = strtoul(A, NULL, 10);
		NSInteger div2 = strtoul(B, NULL, 10);
		NSInteger length = strtoul(C , NULL, 10);
		[fizzBuzz firstDiv:div1  secondDiv:div2  length:length ];
		
	}

}
@implementation fizzBuzz
+(void) firstDiv:(NSInteger) A secondDiv:(NSInteger)B length:(NSInteger)C{
	NSInteger i;
	for (i = 1; i <= C; ++i) {
		if ( ((i % A)==0) && ((i % B)==0) ) { //fizz buzz
			printf("FB ");
		}else if(((i % A)==0) && ((i % B)!=0)){ //fizz
			printf("F ");
		}else if(((i % A)!=0) && ((i % B)==0)){ //buzz
			printf("B ");
		}else{
			printf("%d ", (int)i);
		}
	}printf("\n");
}
@end
