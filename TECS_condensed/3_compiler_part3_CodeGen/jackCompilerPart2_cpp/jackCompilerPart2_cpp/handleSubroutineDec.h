//
//  handleSubroutineDec.h
//  jackCompilerPart2_cpp
//
//  Created by Derrick Ho on 3/12/13.
//  Copyright (c) 2013 Derrick Ho. All rights reserved.
//

#ifndef __jackCompilerPart2_cpp__handleSubroutineDec__
#define __jackCompilerPart2_cpp__handleSubroutineDec__

#include <iostream>
#include "list_header.h"

void handleSubroutineDec(std::string);
void handleConstructorDefinition(std::string);
void handleFunctionDefinition(std::string);
void handleMethodDefinition(std::string);
void generateSubroutineHeader(std::string);
void handleReturnStatement(std::string);
void handleParameterList(std::string line);
void handleSubroutineBody(std::string);
void handleStatements(std::string);
void handleVarDec(std::string);
#endif /* defined(__jackCompilerPart2_cpp__handleSubroutineDec__) */
