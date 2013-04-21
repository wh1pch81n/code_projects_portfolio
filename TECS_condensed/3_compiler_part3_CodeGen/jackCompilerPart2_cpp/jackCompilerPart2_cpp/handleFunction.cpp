//
//  handleFunction.cpp
//  jackCompilerPart2_cpp
//
//  Created by Derrick Ho on 3/8/13.
//  Copyright (c) 2013 Derrick Ho. All rights reserved.
//

#include "handleFunction.h"

void handleFunction(string line){
	
	if (contains(line, "<callFunction>")) {
		string fn_name = extractTag(line);
		fn_name += ".";
		string str = getNextLine();
		int num_of_args = 0;
		int implicit_offset = 0;
		if (contains(str, "subroutine")) { //internal method call
			handleIdentifier(str);
			fn_name += extractIdentifier(str); //save name of function for later use
			implicit_offset = 1;
		}else if(contains(str, "class#used")){//function call
			handleIdentifier(str);
			fn_name += extractIdentifier(getCurrLine());
			implicit_offset = 0;
		}else{//external method call
			handleIdentifier(str);
			incFilePtr();//skip past implicit
			incFilePtr();//skip past "."
			fn_name += extractIdentifier(getCurrLine());
			implicit_offset = 1;
		}
		
		if (contains(getNextLine(), "<symbol>", " ( ")) {
			if (contains(getNextLine(), "<expressionList>")) {
				num_of_args = handleExpressionList(getCurrLine());
			}else{
				error("There should be an expressionList between a function's parentheses");
			}
			while ( !contains(getCurrLine(), "</callFunction>")) {
				incFilePtr();
			}
			//num_of_args = extractNumArg(getCurrLine());
			
			writeCall(fn_name, num_of_args + implicit_offset);
		}else{
			error("expected function to have parentheses ()");
		}
	}else{
		error("expected <callFunction>");
	}
}