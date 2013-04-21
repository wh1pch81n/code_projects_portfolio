//
//  main.cpp
//  jackCompilerPart2_cpp
//
//  Created by Derrick Ho on 3/8/13.
//  Copyright (c) 2013 Derrick Ho. All rights reserved.
//

#include <iostream>
#include <list>
#include "list_header.h"
using namespace std;

//list<string> fileARR;
//list<string>::iterator currLine;
//string class_fileName;
//int class_Var_num;
//void printFileArr(){
//	for (list<string>::iterator it = FileList::fileARR.begin()	; it != FileList::fileARR.end(); ++it) {
//		cout << *it;
//	}
//}

int main(int argc, const char * argv[])
{
	char line [1024];
	FILE * f = fopen(argv[1], "r");
	if(!f){
		cerr << "problem opening file" << endl;
		exit(1);
	}
	FileList::resetClassVarNum();
	FileList::clearClassFileName();
	
	//convert file into a linkedlist of lines
	while (fgets(line, sizeof(line), f)) {
		if (*line == '\n') {
			continue;
		}
		FileList::pushBack(line);
//		fileARR.push_back(line);
	}
	//set iterator to point to first element
	FileList::initIterator();
//	currLine = fileARR.begin();
	
//	//printFileArr();
//	for (; !FileList::atFileEnd(); incFilePtr()) {
//		if (contains(getCurrLine(), "<expressionList>")) {
//			handleExpressionList(getCurrLine());
//		}else if(contains(getCurrLine(), "<expression>")){
//			handleExpression(getCurrLine());
//		}else if(contains(getCurrLine(), "<doStatement>")){
//			handleDo(getCurrLine());
//		}else if(contains(getCurrLine(), "<letStatement>")){
//			handleLet(getCurrLine());
//		}else if(contains(getCurrLine(), "<class>")){
//			handleClassDefinition(getCurrLine());
//		}else{
//			error("what?");
//		}
//	}

	handleClassDefinition(getCurrLine());

	return 0;
}

