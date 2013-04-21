//
//  handleIfStatement.cpp
//  jackCompilerPart2_cpp
//
//  Created by Derrick Ho on 3/12/13.
//  Copyright (c) 2013 Derrick Ho. All rights reserved.
//

#include "handleIfStatement.h"
#include <sstream>
void handleIfStatement(string line){
	if( isIfStatementBegin(line)){
		stringstream ssT; ssT <<"IF_TRUE"<<CurrFunctionKind::num_of_if;
		stringstream ssF; ssF <<"IF_FALSE"<<CurrFunctionKind::num_of_if;
		stringstream ssE; ssE <<"IF_END"<<CurrFunctionKind::num_of_if;
		++CurrFunctionKind::num_of_if;
		for (incFilePtr(); !isIfStatementEnd(getCurrLine()); ) {
			if(contains(getCurrLine(), "<keyword>", " if ")){
			}elif(isParenthesesBegin(getCurrLine())){
				handleExpression(getCurrLine());
				
				writeIf(ssT.str());
				writeGoto(ssF.str());
				writeLabel(ssT.str());
			}elif(contains(getCurrLine(), " { ")){
				handleStatements(getCurrLine());
				
			}else{
				error("found something weird in ifStatement");
			}
			incFilePtr();
			if(isIfStatementEnd(getCurrLine())){
				writeLabel(ssF.str());
			}
			if (contains(getCurrLine(), "<keyword>", " else ")) {
				writeGoto(ssE.str());
				writeLabel(ssF.str());
				handleStatements(getNextLine());
				writeLabel(ssE.str());
				incFilePtr();
				if(!isIfStatementEnd(getCurrLine())){
					error("end of ifStatement expected after else statement");
				}
			}
			
		}

	}else{
		error("expected if statement");
	}
}