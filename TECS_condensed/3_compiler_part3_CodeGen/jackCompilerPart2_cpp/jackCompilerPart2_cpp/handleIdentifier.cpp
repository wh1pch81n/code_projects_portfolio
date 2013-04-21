//
//  handleIdentifier.cpp
//  jackCompilerPart2_cpp
//
//  Created by Derrick Ho on 3/8/13.
//  Copyright (c) 2013 Derrick Ho. All rights reserved.
//

#include "handleIdentifier.h"

void handleIdentifier(string line){
	
	if(contains(line, "<identifier>")){
		if( contains(line , "field")){
			writePush("this" , extractHashNum(line));
		}else if(contains(line, "static")){
			writePush("static", extractHashNum(line));
		}else if(contains(line, "var")){
			writePush("local" , extractHashNum(line));
		}else if(contains(line, "argument")){
			int offset = (CurrFunctionKind::IS_A == METHOD)?1:0;
			writePush("argument", offset + extractHashNum(line));
		}else if(contains(line, "class#used")){
			incFilePtr(); //#no need to push this as the argument 0
			incFilePtr(); //#skip past "."
		}else if(contains_both(line, "subroutine" , "method")){
//			writePush("argument", 0);//internal method call.  push "this"
			writePush("pointer", 0);//internal method call.  push "this"
			
		}
//		else if( contains_both(line, "subroutine", "function")){
//			incFilePtr();
//		}
		else{
			error("Should have gotten field, static, arg, var, or class#used, or subroutine");
			return;
		}
	}else{
		error("expected an identifier");
	}
}
