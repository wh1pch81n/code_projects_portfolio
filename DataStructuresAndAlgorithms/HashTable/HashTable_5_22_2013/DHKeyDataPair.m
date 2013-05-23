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
	if (!( self = [super init])) { return nil;}
	//initialization code in here
	self->pairArr = @[ [NSObject new] , [NSObject new] ];
	return self;
}
-(id) initWithKey:(NSObject*) key WithData:(NSObject*) data{
	if( !(self = [super init])) { return nil; }
	//initialization code in here
	self->pairArr = @[key, data];
	return self;
}
-(id) getKey{
	return pairArr[0];
}
-(id) getData{
	return pairArr[1];
}
@end
