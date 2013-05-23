//
//  DHKeyDataPair.h
//  HashTable
//
//  Created by Derrick Ho on 5/22/13.
//  Copyright (c) 2013 Derrick Ho. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface DHKeyDataPair : NSObject{
	NSArray * pairArr;
}
-(id) init;
-(id) initWithKey:(NSObject*) key WithData:(NSObject*) data;
-(id) getKey;
-(id) getData;
@end
