//
//  main.m
//  MultiplesOf3And5
//
//  Created by Derrick Ho on 7/20/13.
//  Copyright (c) 2013 Derrick Ho. All rights reserved.
//

#import <Foundation/Foundation.h>
@interface MultiplesOf3And5: NSObject
+(NSNumber *)mo3a5Range:(NSNumber *)num;
@end
@implementation MultiplesOf3And5
+(NSNumber *)mo3a5Range:(NSNumber *)num{
	NSInteger total = 0;
	for (int i = 0; i < [num intValue]; ++i) {
		if ((0 == (i % 3)) ||
			(0 == (i % 5))) {
			total += i;
		}
	}
	return @(total);
}
@end

int main(int argc, const char * argv[])
{

	@autoreleasepool {
		printf("%d", [[MultiplesOf3And5 mo3a5Range:@(1000)] intValue]);
		
	}
    return 0;
}

