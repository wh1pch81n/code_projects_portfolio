//
//  main.c
//  Node_OOC
//
//  Created by Derrick Ho on 5/27/13.
//  Copyright (c) 2013 Derrick Ho. All rights reserved.
//

#include <stdio.h>
#include "Node.h"

#define _(I) (I)->instanceSelf(I) //if you keep a convention where instanceSelf is always an instance to the class than it could work for any class.  treat instance self like a keyword

int main(int argc, const char * argv[])
{
	Node *a = newNode( 5, NULL, NULL);
	Node *b = newNode( 9, NULL, NULL);
	Node *c = newNode( 7, NULL, NULL);
	
	_(a)->setNext( b);
	_(b)->setPrev( a);
	_(b)->setNext( c);
	_(c)->setPrev( b);
	
	printf(" %d %d %d\n", _(a)->getData(),
		   _(b)->getData(),
		   _(c)->getData());
	printf(" %d %x %d\n", _(_(b)->getPrev())->getData(),
		   _(_(b)->getPrev())->getPrev(),
		   _(_(b)->getNext())->getData());
	 
    return 0;
}

