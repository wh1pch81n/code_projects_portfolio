//
//  handleArray.cpp
//  jackCompilerPart2_cpp
//
//  Created by Derrick Ho on 3/8/13.
//  Copyright (c) 2013 Derrick Ho. All rights reserved.
//

#include "handleArray.h"

void handleArray(string line){

	if(contains(line, "<callArray>")){
		if (contains(getNextLine(), "<identifier>")) {
			string id = getCurrLine();
			
			handleExpression(getNextLine());//looks inside [...]
			handleIdentifier(id);//pushes array name on stack
			writeArithmetic("+");//offset array
			//writePop("pointer", 1); //set point to correct place in memory
//			writePush("that", 0); //place array[offset] on stack
			while ( !contains(getCurrLine(), "</callArray>")) {
				incFilePtr();
			}
		}else{
			error("expected to get array name <identifier> at this point");
		}
	}else{
		error("expected callArray");
	}
}