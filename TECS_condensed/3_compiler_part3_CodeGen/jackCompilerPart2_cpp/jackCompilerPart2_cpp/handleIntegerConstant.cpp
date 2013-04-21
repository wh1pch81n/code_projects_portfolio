//
//  handleIntegerConstant.cpp
//  jackCompilerPart2_cpp
//
//  Created by Derrick Ho on 3/8/13.
//  Copyright (c) 2013 Derrick Ho. All rights reserved.
//

#include "handleIntegerConstant.h"

void handleIntegerConstant(string line){
	
	if(contains(line, "<integerConstant>")){
		writePush("constant", extractIntegerConstant(line));
	}else{
		error("expected Integer Constant");
	}
}