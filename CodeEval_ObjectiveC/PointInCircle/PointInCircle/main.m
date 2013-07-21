//
//  main.m
//  PointInCircle
//
//  Created by Derrick Ho on 5/26/13.
//  Copyright (c) 2013 Derrick Ho. All rights reserved.
//

#import <Foundation/Foundation.h>
#define CGFloat float
#define CGPoint MYPoint
#define CGPointMake MYPointMake
////////////////////////////////////////////////////
struct MYPoint{
	float x,y;
};
typedef struct MYPoint MYPoint;
struct CRP{
	CGPoint center, point;
	CGFloat radius;
};
typedef struct CRP CRP;
////////////////////////////////////////////////////
CRP makeCRP( NSString *line);
MYPoint MYPointMake(NSInteger x, NSInteger y){
	return (MYPoint){.x=x, .y=y};
}
////////////////////////////////////////////////////
@interface NSString (EASYFILEREADER)
+(NSArray *) FileArrayFromPath:(NSString *) path;
@end
////////////////////////////////////////////////////
@interface Circle : NSObject{
	CGPoint center;
	CGFloat radius;
}
-(id) initCircleWithCenter:(CGPoint )c WithRadius:(CGFloat)r;
-(bool) isIntersectedAtPoint:(CGPoint )p;
@end
////////////////////////////////////////////////////

int main(int argc, const char * argv[])
{
	NSAutoreleasePool *pool = [NSAutoreleasePool new];{
		NSArray *f = [NSString FileArrayFromPath:[NSString stringWithUTF8String:argv[1]]];
		for (NSString *s in f) {
			if( [s isEqualToString:@""]) continue;
			CRP crp_v = makeCRP(s);
			Circle *c = [[Circle alloc] initCircleWithCenter:crp_v.center
												  WithRadius:crp_v.radius];
			printf ("%s\n", ([c isIntersectedAtPoint:crp_v.point]) ? "true" :"false");
		}
	}
	[pool drain];
    return 0;
}
////////////////////////////////////////////////////
CRP makeCRP( NSString *line){
	NSArray *a = [line componentsSeparatedByString:@";"];
	NSString *c = [a objectAtIndex:0];
	NSString *r = [a objectAtIndex:1];
	NSString *p = [a objectAtIndex:2];
	CRP crp_v;
	crp_v.center = CGPointMake([[c substringFromIndex:[c rangeOfString:@"("].location +1] floatValue],
							   [[c substringFromIndex:[c rangeOfString:@","].location +1] floatValue]);
	crp_v.radius = [[r substringFromIndex:[r rangeOfString:@":"].location +1] floatValue];
	crp_v.point.x = [[p substringFromIndex:[p rangeOfString:@"("].location +1] floatValue];
	crp_v.point.y = [[p substringFromIndex:[p rangeOfString:@","].location +1] floatValue];
	return crp_v;
}
////////////////////////////////////////////////////
@implementation NSString (EASYFILEREADER)
+(NSArray *) FileArrayFromPath:(NSString *)path{
	NSString *filecontents = [NSString stringWithContentsOfFile:path
													   encoding:NSASCIIStringEncoding
														  error:NULL];
	NSArray *fileArr = [filecontents componentsSeparatedByCharactersInSet:[NSCharacterSet newlineCharacterSet]];
	return fileArr;
}
@end
////////////////////////////////////////////////////
@implementation Circle
-(id) initCircleWithCenter:(CGPoint )c WithRadius:(CGFloat)r{
	if( !(self = [super init])){ return nil; }
	self->center = c;
	self->radius = r;
	return self;
}
-(bool) isIntersectedAtPoint:(CGPoint )p{
	CGFloat dx = ( self->center.x - p.x);
	CGFloat dy = ( self->center.y - p.y);
	CGFloat distance = sqrtf( (dx * dx) + (dy * dy));
	return ((self->radius - distance) >= 0)? YES : NO;
}

@end
////////////////////////////////////////////////////