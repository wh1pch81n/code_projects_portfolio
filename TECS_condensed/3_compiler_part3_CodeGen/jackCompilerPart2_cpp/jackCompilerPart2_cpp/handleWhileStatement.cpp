//
//  handleWhileStatement.cpp
//  jackCompilerPart2_cpp
//
//  Created by Derrick Ho on 3/12/13.
//  Copyright (c) 2013 Derrick Ho. All rights reserved.
//

#include "handleWhileStatement.h"
#include <sstream>
void handleWhileStatement(string line){
	if(contains(line, "<whileStatement>")){
		stringstream ssEXP, ssEND;
		ssEXP << "WHILE_EXP" << CurrFunctionKind::num_of_while;
		ssEND << "WHILE_END" << CurrFunctionKind::num_of_while;
		++CurrFunctionKind::num_of_while;
		for (incFilePtr(); !contains(getCurrLine(), "</whileStatement>"); incFilePtr()) {
			if(contains(getCurrLine(), "<keyword>", "while")){
				writeLabel(ssEXP.str());
			}elif(isParenthesesBegin(getCurrLine())){
				handleExpression(getCurrLine());
				writeArithmetic("not");
				writeIf(ssEND.str());
			}elif(contains(getCurrLine(), "<symbol>", " { ")){
				handleStatements(getCurrLine());
				writeGoto(ssEXP.str());
				writeLabel(ssEND.str());
			}else{
				error("found something weird in whileStatement");
			}
		}
	}else{
		error("expected WhileStatement");
	}
}