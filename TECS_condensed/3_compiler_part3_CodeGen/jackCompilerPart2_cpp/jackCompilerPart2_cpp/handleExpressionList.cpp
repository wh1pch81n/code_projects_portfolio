//
//  handleExpressionList.cpp
//  jackCompilerPart2_cpp
//
//  Created by Derrick Ho on 3/8/13.
//  Copyright (c) 2013 Derrick Ho. All rights reserved.
//

#include "handleExpressionList.h"

//brief: this handles the arguments sent to a function call
//returns the number of arguments
int handleExpressionList(string line){
	
	int num_arg = 0;
	if (isExpressionListBegin(line)) {
		incFilePtr();//skip past <expressionList>
		
		while( !isExpressionListEnd(getCurrLine())) {
			if (isExpressionBegin(getCurrLine())) {
				num_arg++;
				handleExpression(getCurrLine());
			}else if( contains(getCurrLine(), "<symbol>", " , ")){
				//divides expression list up.  offers no output
			}else{
				error("unexpected line in expressionList");
			}
			incFilePtr();
		}
		//incFilePtr();//skip past </expressionList> tag
	}else{
		error("expected expressionList");
	}
	return num_arg;
}