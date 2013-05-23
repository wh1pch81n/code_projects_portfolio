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
	self->_key = self->pairArr[0];
	self->_data = self->pairArr[1];
	return self;
}
-(id) initWithKey:(NSObject*) key WithData:(NSObject*) data{
	if( !(self = [super init])) { return nil; }
	//initialization code in here
	self->pairArr = @[key, data];
	self->_key = self->pairArr[0];
	self->_data = self->pairArr[1];
	return self;
}

@end
