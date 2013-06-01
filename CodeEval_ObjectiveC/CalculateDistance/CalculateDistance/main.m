//
//  main.m
//  CalculateDistance
//
//  Created by Derrick Ho on 6/1/13.
//  Copyright (c) 2013 Derrick Ho. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface DHPoint: NSObject
@property (readonly) 	CGPoint Pt;
-(id)initWithPointInString:(NSString *) pt;
-(NSInteger)distanceBetweenTwoPoints:(DHPoint *) pt;
@end
@implementation DHPoint
-(id)initWithPointInString:(NSString *) pt{
	if (! (self = [super init])) {
		return nil;
	}
	//else do stuff to make the object
	pt = [pt stringByReplacingOccurrencesOfString:@"(" withString:@""];
	pt = [pt stringByReplacingOccurrencesOfString:@")" withString:@""];
	pt = [pt stringByReplacingOccurrencesOfString:@" " withString:@""];
	NSArray *xy = [pt componentsSeparatedByString:@","];
	self->_Pt = CGPointMake([xy[0] integerValue], [xy[1] integerValue]);
	return self;
}
-(NSInteger)distanceBetweenTwoPoints:(DHPoint *) pt{
	NSInteger dx = [self Pt].x- [pt Pt].x;
	NSInteger dy = [self Pt].y- [pt Pt].y;
	return sqrt((dx*dx) + (dy*dy));
}
@end
////////////////////////////////////
@interface NSString (FileReader)
+ (NSArray *)MakeFileArrayFromFileWithPath:(NSString *)path;
@end
@implementation NSString (FileReader)
+ (NSArray *)MakeFileArrayFromFileWithPath:(NSString *)path{
	NSString *File =[NSString stringWithContentsOfFile:path
											  encoding:NSUTF8StringEncoding
												 error:NULL];
	return [File componentsSeparatedByCharactersInSet:
			[NSCharacterSet newlineCharacterSet]];
}
@end

int main(int argc, const char * argv[])
{
	NSAutoreleasePool *pool = [NSAutoreleasePool new]; {
		for (NSString *line in [NSString MakeFileArrayFromFileWithPath:[NSString stringWithUTF8String:argv[1]]]) {
			if ([[line stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceAndNewlineCharacterSet]] isEqualToString:@""]) {
				continue;
			}
			NSArray *twoPoints = [line componentsSeparatedByString:@") ("];
			DHPoint *p1 = [[DHPoint alloc] initWithPointInString:[twoPoints objectAtIndex:0]];
			DHPoint *p2 = [[DHPoint alloc] initWithPointInString:[twoPoints objectAtIndex:1]];
			printf("%ld\n", [p1 distanceBetweenTwoPoints:p2]);
		}
	}[pool drain];
    return 0;
}

