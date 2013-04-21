//
//  list_header.cpp
//  jackCompilerPart2_cpp
//
//  Created by Derrick Ho on 3/8/13.
//  Copyright (c) 2013 Derrick Ho. All rights reserved.
//

#include "list_header.h"
//#define debugging false
//void error (string msg){
//	cout << msg << endl;
//	exit(1);
//}

error::error(string str){
	this->str = str;
}
error::~error(){
	
	cerr <<"error---: "<< str << endl;
	cerr <<"error happened on:  " << FileList::getCurrLine()<< endl;
//	string temp;
//	cerr << "end program?";
//	cin >> temp;
//	cerr << "\nvoluntary exit \n";
	exit(1);
}

//"""segment could be constant argument local, static, this, that, pointer, or temp """
void writePush( string segment, int index){
	if( segment == "constant" or
	   segment == "argument"  or
	   segment == "local" or
	   segment ==  "static" or
	   segment ==  "this" or
	   segment ==  "that" or
	   segment == "pointer" or
	   segment ==  "temp"){
		if(index >= 0){
			printf( "push %s %d\n" ,segment.c_str(), index);
			return;
		}
	}
	
	error(" invalid segment or index ");
	return;
}
//"""segment could be constant argument local, static, this, that, pointer, or temp """
void writePop(string segment, int index){
	if( segment == "constant" or
	   segment == "argument"  or
	   segment == "local" or
	   segment ==  "static" or
	   segment ==  "this" or
	   segment ==  "that" or
	   segment ==  "pointer" or
	   segment ==  "temp"){
		if(index >= 0){
			printf( "pop %s %d\n",segment.c_str(), index);
			return;
		}
	}
	error(" invalid segment or index ");
	return;
}

void writeArithmetic(string cmd){
//	if(cmd == "add" ||
//	   cmd == "sub" ||
//	   cmd == "neg" ||
//	   cmd == "eq" ||
//	   cmd == "gt" ||
//	   cmd == "lt" ||
//	   cmd == "and" ||
//	   cmd == "or" ||
//	   cmd == "not"){
//		cout << cmd << endl;
//		return;
//	}
	if     (contains(cmd , "+")) {cout << "add" << endl;}
	else if(contains(cmd , "-")) {cout << "sub" << endl;}
	else if(contains(cmd , "neg")) {cout << "neg" << endl;}
	else if(contains(cmd , "=")) {cout << "eq" << endl;}
	else if(contains(cmd , "&gt;")) {cout << "gt" << endl;}
	else if(contains(cmd , "&lt;")) {cout << "lt" << endl;}
	else if(contains(cmd , "&")) {cout << "and" << endl;}
	else if(contains(cmd , "|")) {cout << "or" << endl;}
	else if(contains(cmd , "not")) {cout << "not" << endl;}
	else if(contains(cmd, "*")){ writeCall("Math.multiply", 2);}
	else if(contains(cmd, "/")){ writeCall("Math.divide", 2);}
	else error("this doesn't seem like an arithmetic operator");
	return;
}

void writeLabel(string name){
	printf( "label %s\n" ,name.c_str());
}
void writeGoto(string name){
	printf( "goto %s\n" ,name.c_str());
}

void writeIf(string name){
	printf( "if-goto %s\n",name.c_str());
}

void writeCall(string fn_name, int n_args){
	printf( "call %s %d\n",fn_name.c_str(), n_args);
}
void writeFunction(string fn_name, int n_locals){
	printf( "function %s %d\n",fn_name.c_str(), n_locals);
}
void writeReturn(){
	cout << "return" << endl;
}
void op2write(string op){
	if(op == "+")
		writeArithmetic("add");
	else if(op == "-")
		writeArithmetic("sub");
	else if(op == "*")
		writeCall("Math.multiply", 2);
	else if(op == "/")
		writeCall("Math.divide", 2);
	else if(op == "&amp;")
		writeArithmetic("and");
	else if(op == "|")
		writeArithmetic("or");
	else if(op == "&lt;")
		writeArithmetic("lt");
	else if(op == "&gt;")
		writeArithmetic("gt");
	else
		error("not sure what to do with this symbol " );
}

int toInt(string s){
	return (int) strtol(s.c_str() , NULL, 10);
}

string extractItemFrom(string thisLine,string left="> ", string right=" </"){
	unsigned long L = thisLine.find(left)+left.length();
	unsigned long width =thisLine.find(right)-L;
	return thisLine.substr(L, width);
}
string extractItemFromRev(string thisLine,string left="> ", string right=" </"){
	unsigned long L = thisLine.rfind(left)+left.length();
	unsigned long width =thisLine.rfind(right)-L;
	return thisLine.substr(L, width);
}
string extractTag(string thisLine){
	return extractItemFromRev(thisLine, "(", ")");
}
int extractIntegerConstant(string thisLine){
	return toInt(extractItemFrom(thisLine, "<integerConstant> ", " </integerConstant"));
}
string extractStringConstant(string thisLine){
	return extractItemFrom(thisLine, "<stringConstant> ", " </stringConstant>");
}
string extractIdentifier(string thisLine){
	return extractItemFrom(thisLine, "<identifier> ", " </identifier>");
}
string extractSymbol(string thisLine){
	return extractItemFrom(thisLine, "<symbol> ", " </symbol>");
}
int extractHashNum(string thisLine){
	return toInt(extractItemFromRev(thisLine, "_", ")"));
}
int extractNumArg(string thisLine){
	return toInt(extractItemFromRev(thisLine, "num_arg#", ")"));
}
string extractVariableKind(string thisLine){
	string str = extractItemFrom(thisLine, "</identifier>(", "#");
	if (str == "var") {
		str = "local";
	}else if(str == "argument"){
	}else if(str == "field"){
		str = "this";
	}else if(str == "static"){
	}else{
		error("Exprected, var, argument, field, or static");
	}
	return str;
}
string extractVMfn_name(string thisLine){
	return extractItemFromRev(thisLine, "</callFunction>(", "#");
}
bool contains(string str, string sub){
	if (str.find(sub) != string::npos)
		return true;
	return false;
}
bool contains(string str, string sub1, string sub2){
	return contains_both(str, sub1, sub2);
}
bool contains_both(string str, string sub1, string sub2){
	if(contains(str, sub1) && contains(str, sub2))
		return true;
	return false;
}
//////////////
int FileList::_getNumVarInSubroutine(){
	int NumVarInSubroutine = 0;
	
	list<string>::iterator it = currLine;
	string temp = *currLine;
	temp = * it;
	for (it  = currLine;	!isSubroutineDecEnd(*it)	; ++it, temp = *it) {
		if (it == fileARR.end()) {
			error("failed to find subroutine ender");
		}
		if (contains(*it, "var#def")) {
			++NumVarInSubroutine;
		}
	}
	return NumVarInSubroutine;
}
void FileList::clearClassFileName(){class_fileName ="";}
void FileList::resetClassVarNum(){FileList::class_Var_num = 0;}
void FileList::pushBack(std::string line){fileARR.push_back(line);  }
void FileList::initIterator(){currLine = fileARR.begin();}
//	static list<string>::iterator getEnd(){ return fileARR.end();}
//	static list<string>::iterator getEnd(){ return fileARR.end();}
bool FileList::atFileEnd(){return currLine == fileARR.end();}


string FileList::_getCurrLine(){
	return *currLine;
}
string FileList::_getNextLine(){
	incFilePtr();
	return getCurrLine();
}
void FileList::_incFilePtr(){
	if (currLine != fileARR.end()) {
		if(debugging){
			cout << getCurrLine();
		}
		++currLine;
	}else{
		error("Reached end of file");
	}
}
void FileList::_setClassFileName(){
	class_fileName = extractIdentifier(getCurrLine());
}
//counts the number of Class Variables within scope
//starts at current line and interates until it hits </class>
void FileList::_setClassVarNum(){
	for (list<string>::iterator it = currLine	; !isClassDefinitionEnd(*it) ; ++it) {
		if(it == fileARR.end()){
			cerr << "missing end of class i.e. </class>" << endl;
			exit(1);
		}
		
		if (contains(*it, "field#def") ) { //statics are handled in the vm_translator, not in the compiler
			class_Var_num++; //this values is used in the contructor function to figure out how many memory to allocat
		}
		
	}
}
int FileList::_getClassVarNum(){
	return class_Var_num;
}
string FileList::_getClassFileName(){
	return class_fileName;
}
std::string FileList::class_fileName = string();
int FileList::class_Var_num = 0;
std::list<std::string> FileList::fileARR = std::list<std::string>();
std::list<std::string>::iterator FileList::currLine = std::list<std::string>::iterator();

////////////////
fnKind CurrFunctionKind::IS_A = VOID;
unsigned int CurrFunctionKind::num_of_if = 0;
unsigned int CurrFunctionKind::num_of_while = 0;
////////////////
bool isExpressionBegin(string line){
	return contains(line, "<expression>");
}
bool isExpressionEnd(string line){
	return contains(line, "</expression>");
}
bool isParenthesesBegin(string line){
	return contains(line, "<symbol>", " ( ");
}
bool isParenthesesEnd(string line){
	return contains(line, "<symbol>", " ) ");
}
bool isSquareBracketBegin(string line){
	return contains(line, "<symbol>", " [ ");
}
bool isSquareBracketEnd(string line){
	return contains(line, "<symbol>", " ] ");
}

bool isStringConstant(string line){
	return contains(line, "<stringConstant>", "</stringConstant>");
}

bool isDoStatementBegin(std::string line){
	return contains(line, "<doStatement>");
}
bool isDoStatementEnd(std::string line){
	return (contains(line, "</doStatement>"));
}

bool isLetStatementBegin(std::string line){
	return (contains(line, "<letStatement>"));
}
bool isLetStatementEnd(std::string line){
	return (contains(line, "</letStatement>"));
}

bool isExpressionListBegin(std::string line){
	return (contains(line, "<expressionList>"));
}

bool isExpressionListEnd(std::string line){
	return (contains(line, "</expressionList>"));
}

bool isTermBegin(std::string line){
	return (contains(line, "<term>"));
}

bool isTermEnd(std::string line){
	return (contains(line, "</term>"));
}

bool isIdentifier(std::string line){
	return (contains(line, "<identifier>", "</identifier>"));
}

bool isCallArrayBegin(std::string line){
	return (contains(line, "<callArray>"));
}
bool isCallArrayEnd(std::string line){
	return contains(line, "</callArray>");
}

bool isCallFunctionBegin(std::string line){
	return contains(line, "<callFunction>");
}
bool isCallFunctionEnd(std::string line){
	return contains(line, "</callFunction>");
}


bool isIntegerConstant(std::string line){
	return contains(line, "<integerConstant>", "</integerConstant>");
}
bool isClassDefinitionBegin(std::string line){
	return contains(line, "<class>");
}
bool isClassDefinitionEnd(std::string line){
	return contains(line , "</class>");
}
bool isClassVarDecBegin(std::string line ){return contains(line , "<classVarDec>");}
bool isClassVarDecEnd(std::string line ){return contains(line , "</classVarDec>");}

bool isVarDecBegin(std::string line ){return contains(line, "<varDec>");}
bool isVarDecEnd(std::string line ){return contains(line, "</varDec>");}

bool isSubroutineDecBegin(std::string line){return contains(line, "<subroutineDec>");}
bool isSubroutineDecEnd(std::string line){return contains(line, "</subroutineDec>");}

bool isWhileStatementBegin(std::string line){return contains(line, "<whileStatement>");}
bool isWhileStatementEnd(std::string line){return contains(line, "</whileStatement>");}

bool isIfStatementBegin(std::string line){return contains(line, "<ifStatement>");}
bool isIfStatementEnd(std::string line){return contains(line, "</ifStatement>");}

