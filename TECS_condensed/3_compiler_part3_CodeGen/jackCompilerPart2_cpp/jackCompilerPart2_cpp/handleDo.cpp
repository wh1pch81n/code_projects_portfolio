//
//  handleDo.cpp
//  jackCompilerPart2_cpp
//
//  Created by Derrick Ho on 3/9/13.
//  Copyright (c) 2013 Derrick Ho. All rights reserved.
//

#include "handleDo.h"

void handleDo(string line){

	if (isDoStatementBegin(line)) {
		incFilePtr();//skip past <doStatement>
		for (; !isDoStatementEnd(getCurrLine()); incFilePtr()){
			if (isCallFunctionBegin(getCurrLine())) {
				handleFunction(getCurrLine());
			}else if(contains(getCurrLine(), "<keyword>", " do ")){
			}else if(contains(getCurrLine(), "<symbol>", " ; ")){
			}else{
				error("expected a <callFunction>");
			}
		}
		writePop("temp", 0);//the function places some arbirary value on the stack, so I must Pop the arbitrary value to an arbitrary place like temp0
	}else{
		error("exprected a <doStatement>");
	}
}