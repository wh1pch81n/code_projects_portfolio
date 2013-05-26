//
//  DHKeyDataPair.m
//  HashTable
//
//  Created by Derrick Ho on 5/22/13.
//  Copyright (c) 2013 Derrick Ho. All rights reserved.
//

#import "DHKeyDataPair.h"

@implementation DHKeyDataPair
-(id) init{
	return [self initWithKey:[NSObject new] WithData:[NSObject new]];
}
-(id) initWithKey:(NSObject*) key WithData:(NSObject*) data{
	if( !(self = [super init])) { return nil; }
	//initialization code in here
	[self setKey:key];
	[self setData:data];
	return self;
}

@end
