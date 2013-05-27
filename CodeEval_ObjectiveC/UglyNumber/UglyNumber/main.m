//
//  main.m
//  UglyNumber
//
//  Created by Derrick Ho on 4/27/13.
//  Copyright (c) 2013 Derrick Ho. All rights reserved.
//

#import <Foundation/Foundation.h>
////////////////////////////////////////
@interface halfAdderNnary : NSObject
+(void) addA:(NSInteger)a addB:(NSInteger)b base:(NSInteger)base carryOutReference:(NSInteger*) cout solutionReference:(NSInteger*) s;
@end
@implementation halfAdderNnary
+(void) addA:(NSInteger)a 		addB:(NSInteger)b base:(NSInteger)base 
carryOutReference:(NSInteger*) cout solutionReference:(NSInteger*) s
{
	NSInteger apb = a+b;
	a %= base; b %= base;
	*cout = apb/base;
	*s = (apb)%base;
}
@end
////////////////////////////////////////
@interface  N_tri_register: NSObject{
	NSMutableArray * _reg ;
	NSString* _baseSTR;
}
-(void)initRegOfBaseWidth:(NSInteger) n baseSTR:(NSString*)bs;
-(void)incrementRegister;
-(NSString*)getRegisterValue;
@end
@implementation N_tri_register
-(void)initRegOfBaseWidth:(NSInteger)n baseSTR:(NSString *)bs{
	_reg = [NSMutableArray arrayWithCapacity:n];
	NSInteger i;
	for (i = 0; i < n; ++i) {
		[_reg addObject:[NSNumber numberWithInteger:0]];//initialize reg to all zeros
	}
	_baseSTR = bs;
}
-(NSString*)getRegisterValue{
	NSMutableString *ms = [NSMutableString new];
	NSInteger i;
	for (i = _reg.count -1; i >= 0; --i) {
		//[ms appendFormat:@"%ld", [[_reg objectAtIndex:i] integerValue ]];
		
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
/*  a class that reads the file kind of like ifstream*/
@interface CEifstream : NSObject{
@private
	FILE* _f;
}
-(void)openFileStream:(const char*)path;
-(NSString*)getlineAndInc;
-(BOOL)didFailToOpen;
-(void)closeFileStream;
@end
@implementation CEifstream
-(void)openFileStream:(const char*)path{
	_f = fopen(path, "r");
}
-(NSString*)getlineAndInc{
	char line[1024];
	if (fgets(line, sizeof(line), _f)) {
		return [NSString stringWithFormat:@"%s", line];
	}
	return nil;
}
-(BOOL)didFailToOpen{
	return (!_f)?YES: NO;
}
-(void)closeFileStream{
	fclose(_f);
}
@end
////////////////////////////////////////
@interface CEUglyNumber : NSObject
/*todo:
a merge function will merge the given function together with the n_tri_reg number.
the resulting string would be analyzed.  Then summed up. if it is an ugly number
a running total shall be incremented.

an ugly number is a number that canbe divided by 2,3,5,7
zero is ugly.

*/
@end
////////////////////////////////////////
int main(int argc, const char * argv[])
{
	
	NSAutoreleasePool * pool = [NSAutoreleasePool new];{
		NSInteger basewidth = 2;
		NSString* bstr = @"012";
		N_tri_register* r = [N_tri_register new];
		[r initRegOfBaseWidth:basewidth baseSTR:bstr];
		for (NSInteger i = 0; i < pow(bstr.length, basewidth); ++i) {
			printf("%s\n", [[r getRegisterValue] UTF8String]);
			[r incrementRegister];
		}
		
		CEifstream* ifile = [CEifstream new];
		[ifile openFileStream:argv[1]];
		if ([ifile didFailToOpen]) {
			printf("probs opening file\n");
		}else{
			printf("%s", [[ifile getlineAndInc] UTF8String]);
			printf("%s", [[ifile getlineAndInc] UTF8String]);
			printf("%s", [[ifile getlineAndInc] UTF8String]);
			NSLog(@"stuff that happens in the middle\n");

			printf("%s", [[ifile getlineAndInc] UTF8String]);
			//these should be null since we have reached the end of file.
			printf("%s", [[ifile getlineAndInc] UTF8String]);
			printf("%s", [[ifile getlineAndInc] UTF8String]);
		}
		[ifile closeFileStream];
	}[pool drain];
	return 0;
}


