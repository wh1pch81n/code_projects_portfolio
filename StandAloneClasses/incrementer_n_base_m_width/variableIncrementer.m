#import <Foundation/Foundation.h>
////////////////////////////////////////
@interface halfAdderNnary : NSObject
+(void) addA:(NSInteger)a addB:(NSInteger)b base:(NSInteger)base carryOutReference:(NSInteger*) cout solutionReference:(NSInteger*) s;
@end
@implementation halfAdderNnary
+(void) addA:(NSInteger)a addB:(NSInteger)b base:(NSInteger)base carryOutReference:(NSInteger*) cout solutionReference:(NSInteger*) s
{
	a %= base; b %= base;
	*cout = (a+b)/base;
	*s = (a+b)%base;
}
@end
////////////////////////////////////////
@interface  variableIncRegister: NSObject{
	NSMutableArray * _reg ;
	NSString* _baseSTR;
}
-(void)initRegOfBaseWidth:(NSInteger) n baseSTR:(NSString*)bs;
-(void)incrementRegister;
-(NSString*)getRegisterValue;
@end
@implementation variableIncRegister
-(void)initRegOfBaseWidth:(NSInteger)n baseSTR:(NSString *)bs{
	_baseSTR = bs;
	_reg = [NSMutableArray arrayWithCapacity:n];
	NSInteger i;
	for (i = 0; i < n; ++i) {
		[_reg addObject:[NSNumber numberWithInteger:0]];//initialize reg to all zeros
	}
	
}
-(NSString*)getRegisterValue{
	NSMutableString *ms = [NSMutableString new];
	NSInteger i;
	for (i = _reg.count -1; i >= 0; --i) {
		NSRange range = NSMakeRange([[_reg objectAtIndex:i] integerValue ], 1);
		NSString* stringToAppend =[_baseSTR substringWithRange:range];
		[ms appendFormat:@"%@", stringToAppend ];
	}
	return ms;
}
-(void)incrementRegister{
	NSInteger b,c,s ;
	NSInteger i;
	for (i =0, b=1; i < _reg.count; ++i) {
		[halfAdderNnary addA:[[_reg objectAtIndex:i] integerValue]
						  addB:b
						  base:[_baseSTR length]
			 carryOutReference:&c
			 solutionReference:&s];
		b = c;
		[_reg replaceObjectAtIndex:i withObject:[NSNumber numberWithInteger:s]];
	}
}
@end
////////////////////////////////////////

int main(int argc, const char * argv[])
{
	
	NSAutoreleasePool * pool = [NSAutoreleasePool new];{
		NSInteger basewidth = 2;
		NSString* bstr = @"012";
		variableIncRegister* r = [variableIncRegister new];
		[r initRegOfBaseWidth:basewidth baseSTR:bstr];
		for (NSInteger i = 0; i < pow(bstr.length, basewidth); ++i) {
			printf("%s\n", [[r getRegisterValue] UTF8String]);
			[r incrementRegister];
		}
	}[pool drain];
	return 0;
}