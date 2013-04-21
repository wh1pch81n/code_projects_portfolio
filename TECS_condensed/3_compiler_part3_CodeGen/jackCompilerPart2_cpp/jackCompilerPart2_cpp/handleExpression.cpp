//
//  handleExpression.cpp
//  jackCompilerPart2_cpp
//
//  Created by Derrick Ho on 3/8/13.
//  Copyright (c) 2013 Derrick Ho. All rights reserved.
//

#include "handleExpression.h"

void handleExpression(string line){

	if (isExpressionBegin(line)) {
		incFilePtr();
		while ( !isExpressionEnd(getCurrLine())) {
			if (isTermBegin(getCurrLine())) {
				handleTerm(getCurrLine());
			}else if(contains(getCurrLine(), "<symbol>")){
				// lhs op rhs
				//assume lhs has been pushed n stack
				string op = extractSymbol(getCurrLine());
				handleTerm(getNextLine());
				writeArithmetic(op);
			}else{
				error("not sure where expressions should go next");
			}
			incFilePtr();
		}
		//incFilePtr(); //skip past the </expression>
	}else if(isParenthesesBegin(line)){
		incFilePtr();//skip past the "("
		while (!isParenthesesEnd(getCurrLine())) {
			if (isExpressionBegin(getCurrLine())) {
				handleExpression(getCurrLine());
			}else{
				error("expected an expression inside (...)");
			}
			incFilePtr();
		}
	}else if(isSquareBracketBegin(line)){
		incFilePtr(); //skip past the "["
		while (!isSquareBracketEnd(getCurrLine())){
			if (isExpressionBegin(getCurrLine())) {
				handleExpression(getCurrLine());
			}else{
				error("array call offert expects an expression in side [...]");
			}
			incFilePtr();
		}
		
	}else if(contains(getCurrLine(), "<symbol>", " = ")){
		incFilePtr();
		for(;!contains(getCurrLine(), "<symbol>" , " ; ");incFilePtr()){
			if (isExpressionBegin(getCurrLine())) {
				handleExpression(getCurrLine());
			}else{
				error("R-value expected to be an expression ending with a semicolon");
			}
		}
	}else{
		error("expected expression");
	}
}

