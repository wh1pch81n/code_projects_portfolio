#include "handleClassDefinition.h"


void handleClassDefinition(string line){
	
	if (isClassDefinitionBegin(line)) {
		//todo: change the fd such that stdout goes to a dot VM file
		//with the same name as the class
		//
		//implement here:(status not done)(open af file for writing)
		//
		for (incFilePtr(); !isClassDefinitionEnd(getCurrLine()); incFilePtr()) {
			if (contains(getCurrLine(), "<keyword>", " class ")) {
			}else if(contains(getCurrLine(),"<identifier>", "class#def")){
				setClassFileName();
			}else if(contains(getCurrLine(), "<symbol>", " { ")){
			//count number of class variables
				setClassVarNum(); 
				handleClassDefinition(getCurrLine());
			}else{
				error("unexpected Item in class");
			}
		}
		//todo:close the file for writing and prepare for a
		//second class def in the current file.
		FileList::clearClassFileName(); //reset values when class definition finishes up
		FileList::resetClassVarNum();
		
	}elif(contains(line, "<symbol>", " { ")){
		for(incFilePtr(); !contains(getCurrLine(), "<symbol>", " } "); incFilePtr()) {
//			printf("class name: %s  num class var:  %d\n", class_fileName.c_str(), class_Var_num);
//			error("for fun");
			if (contains(getCurrLine(), "<classVarDec>")) {
				//move past all field or static declarations
				handleClassVarDec(getCurrLine());
			}elif(contains(getCurrLine(), "<subroutineDec>")){
				CurrFunctionKind::num_of_if = 0;
				CurrFunctionKind::num_of_while = 0;
				handleSubroutineDec(getCurrLine());
			}else{
				error("expected either classVarDec or subroutineDec");
			}
		}
	}else{
		error("expected class definition");
	}
}

void handleClassVarDec(std::string line){
	if (isClassVarDecBegin(line)) {
		//since the number has already been counted
		//This function shall imply verify that it was given propper stuff
		for (incFilePtr(); !isClassVarDecEnd(getCurrLine()); incFilePtr()) {
			if (contains(getCurrLine(), "<keyword>")) {}
			elif(isIdentifier(getCurrLine())){}
			elif(contains(getCurrLine(), "<symbol>", " , ")){}
			elif(contains(getCurrLine(), "<symbol>", " ; ")){}
			else{
				error("unexpected stuff in classVarDec");
			}
		}
	}else{
		error("exprected classVarDec");
	}
}