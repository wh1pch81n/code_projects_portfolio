//
//  handleTerm.cpp
//  jackCompilerPart2_cpp
//
//  Created by Derrick Ho on 3/8/13.
//  Copyright (c) 2013 Derrick Ho. All rights reserved.
//

#include "handleTerm.h"

void handleTerm(string line){
	
	if (contains(line, "<term>")) {
		incFilePtr();
		while (!contains(getCurrLine(), "</term>")) {
			
			if (contains_both(getCurrLine(), "<identifier>", "</identifier>")) {
				handleIdentifier(getCurrLine());
			}else if(contains(getCurrLine(), "<integerConstant>", "</integerConstant>")){
				handleIntegerConstant(getCurrLine());
			}else if(contains(getCurrLine(), "<stringConstant>", "</stringConstant")){
				handleStringConstant(getCurrLine());
			}else if(contains(getCurrLine(), "<callFunction>")){
				handleFunction(getCurrLine());
			}else if(contains(getCurrLine(), "<callArray>")){
				handleArray(getCurrLine());
				writePop("pointer", 1); //retrieve pointer from stack and set pointer to correct memory location
				writePush("that", 0); //place array[offset] on stack
			}else if(contains(getCurrLine(), "<symbol>", " ( ")){
				handleExpression(getCurrLine());
			}else if(contains(getCurrLine(), "<symbol>", " ~ ") ||
					contains(getCurrLine(), "<symbol>", " - ")){
				string op = extractSymbol(getCurrLine());
				if(contains(op, "~")) op = "not";
				else if(contains(op, "-")) op = "neg";
				else error("somehow neither ~ not -");
				handleTerm(getNextLine());
				writeArithmetic(op);
			}elif(contains(getCurrLine(),"<keyword>", " true ")
				  ||contains(getCurrLine(),"<keyword>", " TRUE ")){
				writePush("constant", 0);
				writeArithmetic("not");
			}elif(contains(getCurrLine(),"<keyword>", " false ")
				  ||contains(getCurrLine(),"<keyword>", " FALSE ")){
				writePush("constant", 0);
			}elif(contains(getCurrLine(), "<keyword>", " this ")
				  ||contains(getCurrLine(),"<keyword>", " THIS ")){
				writePush("pointer", 0);
			}elif(contains(getCurrLine(), "<keyword>", " null ")
				  ||contains(getCurrLine(),"<keyword>", " NULL ")){
				writePush("constant", 0);
			}else{
				error("Not sure where term should go next");
			}
			incFilePtr();
		}
		//incFilePtr(); //skip past the </term>
	}else{
		error("expected term");
	}
}