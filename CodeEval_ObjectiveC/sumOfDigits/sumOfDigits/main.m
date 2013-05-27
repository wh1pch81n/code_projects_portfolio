//
//  main.m
//  sumOfDigits
//
//  Created by Derrick Ho on 4/16/13.
//  Copyright (c) 2013 Derrick Ho. All rights reserved.
//

#import <Foundation/Foundation.h>
@interface sumOfDigits : NSObject{
	NSInteger _totalSum;
}
-(void) calcSumOfDigitsFrom:(NSInteger) num;
-(int) retreiveSumOfDigits;

@property (nonatomic, assign) NSInteger totalSum;
@end

void runProg(const char** argv){
	char line[6];
	FILE* f = fopen(argv[1], "r");
	if(!f){
		printf("Can't open file\n");
		exit(0);
	}
	sumOfDigits* sod = [sumOfDigits new];
	while (1 == fscanf(f, "%s", line)) {
		if(*line == '\n') continue;
		[sod calcSumOfDigitsFrom:strtol(line, NULL, 10)];
		printf("%d\n", [sod retreiveSumOfDigits]);
	}
}
int main(int argc, const char * argv[])
{

	NSAutoreleasePool* pool = [NSAutoreleasePool new];
	{
		runProg(argv);
	}
	[pool drain];
    return 0;
}

@implementation sumOfDigits
@synthesize totalSum = _totalSum;
-(void) calcSumOfDigitsFrom:(NSInteger)num{
	_totalSum = 0;
	while (num > 0) {
		_totalSum += num % 10;
		num /=10;
	}
}
-(int) retreiveSumOfDigits{
	return _totalSum;
}
@end

