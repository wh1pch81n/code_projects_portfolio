//
//  handleStringConstant.cpp
//  jackCompilerPart2_cpp
//
//  Created by Derrick Ho on 3/11/13.
//  Copyright (c) 2013 Derrick Ho. All rights reserved.
//

#include "handleStringConstant.h"

void handleStringConstant(string line){
	
	if (isStringConstant(line)) {
		string str = extractStringConstant(line);
		writePush("constant", (int)str.length());
		writeCall("String.new", 1);
		for (int i = 0; i < str.length(); ++i) {
			writePush("constant", (int)str[i]);
			writeCall("String.appendChar", 2);
		}
	}else{
		error("expected <stringConstant>");
	}
}

