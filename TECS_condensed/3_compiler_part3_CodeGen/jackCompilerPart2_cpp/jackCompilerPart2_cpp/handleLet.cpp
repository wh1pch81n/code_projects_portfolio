//
//  handleLet.cpp
//  jackCompilerPart2_cpp
//
//  Created by Derrick Ho on 3/9/13.
//  Copyright (c) 2013 Derrick Ho. All rights reserved.
//

#include "handleLet.h"

void handleLet(string line){

	if (isLetStatementBegin(line)) {
		incFilePtr();//skip past <letStatement>
		for (; !isLetStatementEnd (getCurrLine()); incFilePtr()){
			if(contains(getCurrLine(), "<keyword>", " let ")){
				incFilePtr();
				string L_val_kind ="";
				int L_val_hash= 0;
				if(isCallArrayBegin(getCurrLine())){
					handleArray(getCurrLine());
					L_val_kind = "that";
					L_val_hash = 0;
					handleExpression(getNextLine());//evaluate RHS
					writePop("temp", 0);//put RHS into temp to uncover the array pointer
					writePop("pointer", 1);//retrieve the array pointer
					writePush("temp", 0);//put RHS back on stack
					writePop("that", 0);//use pointer to place RHS into the right place in memory
					
				}else if(isIdentifier(getCurrLine())){
					//handleIdentifier(getCurrLine());
					L_val_kind = extractVariableKind(getCurrLine());
					L_val_hash = extractHashNum(getCurrLine());
					handleExpression(getNextLine());// evaluations the RHS
					writePop(L_val_kind, L_val_hash); //after expression finishes, pop it off the stack and give it a good home
				}else{
					error("unknown L-value.  expected a variable or array");
				}
			}else if(contains(getCurrLine(), "<symbol>", " ; ")){
			}else{
				error("something weird in let statement");
			}
		}
	}else{
		error("exprected a <letStatement>");
	}

}