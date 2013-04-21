//
//  handleSubroutineDec.cpp
//  jackCompilerPart2_cpp
//
//  Created by Derrick Ho on 3/12/13.
//  Copyright (c) 2013 Derrick Ho. All rights reserved.
//

#include "handleSubroutineDec.h"
#include <sstream>
void handleSubroutineDec(string line){
	if (isSubroutineDecBegin(line)) {
		
		for (incFilePtr();!isSubroutineDecEnd(getCurrLine()) ; incFilePtr()) {
			if(contains(getCurrLine(), "<keyword>", "constructor")){
				handleConstructorDefinition(getCurrLine());
			}elif(contains(getCurrLine(), "<keyword>", "function")){
				handleFunctionDefinition(getCurrLine());
			}elif(contains(getCurrLine(), "<keyword>", "method")){
				handleMethodDefinition(getCurrLine());
			}else{
				error("found something weird inside SubroutineDec");
			}
		}
	}else{
		error("expected SubroutineDec");
	}
}
void generateSubroutineHeader(string line) {
	string className;
	string fn_name;
	int numVarDec = getNumVarInSubroutine();
	stringstream ss;
	//verify that we are on Return type
	if (contains(getCurrLine(), "<identifier>", "class#used") ||
		contains(getCurrLine(), "<keyword>", " void ") ||
		contains(getCurrLine(), "<keyword>", " int ") ||
		contains(getCurrLine(), "<keyword>", " boolean ") ||
		contains(getCurrLine(), "<keyword>", " char ")) {
		className = getClassFileName();
	}else{
		error("expected a valid return type");
	}
	incFilePtr();
	//verify that we are on fn_name
	if (contains(getCurrLine(), "subroutine#def", className)) {
		fn_name = extractIdentifier(getCurrLine());
	}else{
		error("expected function name after return type");
	}
	//compile string
	ss << className << "."<<fn_name;
	//write header
	writeFunction(ss.str(), numVarDec);
}
void handleConstructorDefinition(string line){
	if(contains(getCurrLine(), "<keyword>", "constructor")){
		CurrFunctionKind::IS_A = CONSTRUCTOR;
		generateSubroutineHeader(getNextLine());
		//skip (paremeterList)
		handleParameterList(getNextLine());
		//should be at subroutineBody
		writePush("constant", getClassVarNum());//tell compiler how much memory to allocate
		writeCall("Memory.alloc", 1);//
		writePop("pointer", 0);//set "this" to point to the location in memory just allocated
	
		//subroutine contents
		if (contains(getNextLine(), "<subroutineBody>")) {
			handleSubroutineBody(getCurrLine());
		}else{
			error("expected subrouthine body");
		}

	}else{
		error("exprected constructor definition");
	}
}

void handleFunctionDefinition(string line){
	if(contains(getCurrLine(), "<keyword>", "function")){
		CurrFunctionKind::IS_A = FUNCTION;
		generateSubroutineHeader(getNextLine());
		handleParameterList(getNextLine());
		if (contains(getNextLine(), "<subroutineBody>")) {
			handleSubroutineBody(getCurrLine());
		}else{
			error("expected subrouthine body");
		}
	}else{
		error("expected a function definition");
	}
}

void handleMethodDefinition(string line){
	if(contains(getCurrLine(), "<keyword>", "method")){
		CurrFunctionKind::IS_A = METHOD;
		generateSubroutineHeader(getNextLine());
		handleParameterList(getNextLine());
		//should be at subroutineBody
		writePush("argument", 0);//get implicit_param
		writePop("pointer", 0);//this = implicit_param
		
		//subroutine contents
		if (contains(getNextLine(), "<subroutineBody>")) {
			handleSubroutineBody(getCurrLine());
		}else{
			error("expected subrouthine body");
		}
	}else{
		error("expected method definition");
	}

}

void handleReturnStatement(string line){
	if (contains(line, "<returnStatement>")) {
		for (incFilePtr(); !contains(getCurrLine(), "</returnStatement>"); incFilePtr()) {
			if (contains(getCurrLine(), "<keyword>", "return")) {
				handleReturnStatement(getCurrLine());
				writeReturn();
			}else{
				error("expected return keyword");
			}
		}
	}elif(contains(line, "<keyword>", "return")){
		//methods and functions should always evaluate the expression in return
		if (contains(getNextLine(), " ; ")) {
			writePush("constant", 0); //a return of nothing pushes 0
		}
		for (; !contains(getCurrLine(), " ; "); incFilePtr()) {
			if (isExpressionBegin(getCurrLine())) {
				handleExpression(getCurrLine());
			}else{
				error("expected expression between return and semicolon");
			}
		}
	}else{
		error("expected <returnStatement>");
	}
}
void handleParameterList(string line) {
	if (contains(getCurrLine(), " ( ")) {
		//move past the parameter list
		for (incFilePtr(); !contains(getCurrLine(), " ) "); incFilePtr()) ;
	}else{
		error("expected parameter List");
	}
}

void handleSubroutineBody(string line){
	if(contains(line, "<subroutineBody>")){
		for (incFilePtr(); !contains(getCurrLine(), "</subroutineBody>"); incFilePtr()) {
			if (contains(getCurrLine(), " { ")) {
				handleSubroutineBody(getCurrLine());
			}else{
				error("expected { ... } 1");
			}
		}
	}elif(contains(line, " { ")){
		for (incFilePtr(); !contains(getCurrLine(), " } "); incFilePtr()) {
			if (contains(getCurrLine(), "<statements>")) {
				handleStatements(getCurrLine());
			}elif (isVarDecBegin(getCurrLine())) {
				handleVarDec(getCurrLine());
			}else{
				error("expected { ... } 2");
			}
		}
	}else{
		error("expected subroutine body");
	}
}

void handleStatements(string line){
	if(contains(line, "<statements>")){
		for(incFilePtr(); !contains(getCurrLine(), "</statements>"); incFilePtr()){
			if(isLetStatementBegin(getCurrLine())){
				handleLet(getCurrLine());
			}elif(isDoStatementBegin(getCurrLine())){
				handleDo(getCurrLine());
			}elif(isIfStatementBegin(getCurrLine())){
				handleIfStatement(getCurrLine());
			}elif(isWhileStatementBegin(getCurrLine())){
				handleWhileStatement(getCurrLine());
			}elif(contains(getCurrLine(), " { ")){
				handleStatements(getCurrLine());
			}elif(contains(getCurrLine(), "<returnStatement>")){
				handleReturnStatement(getCurrLine());
			}else{
				error("unknown thing in statement");
			}
		}
	}elif(contains(line, " { ")){
		for (incFilePtr(); !contains(getCurrLine(), " } "); incFilePtr()) {
			if (contains(getCurrLine(), "<statements>")) {
				handleStatements(getCurrLine());
			}else{
				error("expected { ... } 3");
			}
		}
	}else{
		error("expected a statements");
	}
}

void handleVarDec(string line){
	if (isVarDecBegin(line)) {
		for (incFilePtr(); !isVarDecEnd(getCurrLine()); incFilePtr()) {
			//just skip past the variables
		}
	}else{
		error("expected a VarDec");
	}
}