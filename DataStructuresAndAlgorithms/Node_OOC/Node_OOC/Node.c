//
//  Node.c
//  Node_OOC
//
//  Created by Derrick Ho on 5/27/13.
//  Copyright (c) 2013 Derrick Ho. All rights reserved.
//

#include "Node.h"
/*GLOBALs*/
static Node *_CURRENT_INSTANCE = NULL;
/*protypes of member functions*/
static void _deAlloc();
static void _setData(int data);
static void _setNext(Node *next);
static void _setPrev(Node *prev);
static int _getData();
static Node *_getNext();
static Node *_getPrev();

/*definitions of member functions*/
static void _deAlloc(){
	free(_CURRENT_INSTANCE);
}
static void _setData(int data){
	_CURRENT_INSTANCE->data = data;
}
static void _setNext(Node *next){
	_CURRENT_INSTANCE->next = next;
}
static void _setPrev(Node *prev){
	_CURRENT_INSTANCE->prev = prev;
}
static int _getData(){
	return _CURRENT_INSTANCE->data;
}
static Node *_getNext(){
	return _CURRENT_INSTANCE->next;
}
static Node *_getPrev(){
	return _CURRENT_INSTANCE->prev;
}

/*global functions*/
//it may be possible to further hide stuff to prevent direct access to Node.  Perhaps  The user has access to a Node and the the instanceNode function has access to a special __node__ type.  That way Node n; n->method(); is not allowed.  You'd have to do instanceNode(n)->method()

static Node *_instanceSelf( Node *n){
	return _CURRENT_INSTANCE = n;
}

extern
Node *newNode( int data, Node *prev, Node *next){
	Node *newInstance = malloc( sizeof(Node));
	//init member variables
	newInstance->data = data;
	newInstance->next = prev;
	newInstance->prev = next;
	//init methods
	newInstance->setData = _setData;
	newInstance->setNext = _setNext;
	newInstance->setPrev = _setPrev;
	newInstance->getData = _getData;
	newInstance->getNext = _getNext;
	newInstance->getPrev = _getPrev;
	newInstance->deAlloc = _deAlloc;
	newInstance->instanceSelf = _instanceSelf;
	return newInstance;
}


