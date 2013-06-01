//
//  Node.h
//  Node_OOC
//
//  Created by Derrick Ho on 5/27/13.
//  Copyright (c) 2013 Derrick Ho. All rights reserved.
//

#ifndef __Node_OOC__Node__
#define __Node_OOC__Node__

#include <stdio.h>
#include <stdlib.h>

typedef struct _Node Node;
struct _Node{
	int data;
	Node *next;
	Node *prev;
	void (*setData)(int data);
	void (*setNext)(Node *next);
	void (*setPrev)(Node *prev);
	int (*getData)();
	Node *(*getNext)();
	Node *(*getPrev)();
	void (*deAlloc)();
	Node *(*instanceSelf)(Node *n);
};

//extern
//Node *instanceNode( Node *n);

extern
Node *newNode( int data, Node *prev, Node *next);


#endif /* defined(__Node_OOC__Node__) */
