//
//  list_header.h
//  jackCompilerPart2_cpp
//
//  Created by Derrick Ho on 3/8/13.
//  Copyright (c) 2013 Derrick Ho. All rights reserved.
//

#ifndef jackCompilerPart2_cpp_list_header_h
#define jackCompilerPart2_cpp_list_header_h
#include <iostream>
#include <list>
#include "handleExpression.h"
#include "handleExpressionList.h"
#include "handleTerm.h"
#include "handleIdentifier.h"
#include "handleArray.h"
#include "handleFunction.h"
#include "handleIntegerConstant.h"
#include "handleDo.h"
#include "handleLet.h"
#include "handleStringConstant.h"
#include "handleClassDefinition.h"
#include "handleSubroutineDec.h"
#include "handleIfStatement.h"
#include "handleWhileStatement.h"
using namespace std;
#define elif else if
#define debugging false
//extern list<string> fileARR;
//extern list<string>::iterator currLine;
//extern string class_fileName;
//extern int class_Var_num;
//void error (string msg);

class error{
private:
	std::string str;
public:
	error(std::string);
	~error();
};
void writePush( string segment, int index);
void writePop(string segment, int index)  ;
void writeArithmetic(string cmd);
void writeLabel(string name);
void writeGoto(string name);
void writeIf(string name);
void writeCall(string fn_name, int n_args);
void writeFunction(string fn_name, int n_locals);
void writeReturn();
void op2write(string op);
int toInt(string s);
string extractItemFrom(string thisLine,string left, string right);
string extractItemFromRev(string thisLine,string left, string right);
string extractTag(string thisLine);
int extractIntegerConstant(string thisLine);
string extractStringConstant(string thisline);
string extractIdentifier(string thisLine);
string extractSymbol(string thisLine);
int extractHashNum(string thisLine);
int extractNumArg(string thisLine);
string extractVariableKind(string thisLine);
string extractVMfn_name(string thisLine);
bool contains(string, string);
bool contains(string, string, string);
bool contains_both(string, string, string);
//string getCurrLine();
//string getNextLine();
//void incFilePtr();
///
bool isExpressionBegin(std::string);
bool isExpressionEnd(std::string);

bool isParenthesesBegin(std::string);
bool isParenthesesEnd(std::string);

bool isSquareBracketBegin(std::string);
bool isSquareBracketEnd(std::string);

bool isStringConstant(std::string line);
//
bool isDoStatementBegin(std::string);
bool isDoStatementEnd(std::string);

bool isLetStatementBegin(std::string);
bool isLetStatementEnd(std::string);

bool isExpressionListBegin(std::string);
bool isExpressionListEnd(std::string);

bool isTermBegin(std::string);
bool isTermEnd(std::string);

bool isIdentifier(std::string);

bool isCallArrayBegin(std::string);
bool isCallArrayEnd(std::string);

bool isCallFunctionBegin(std::string);
bool isCallFunctionEnd(std::string);

bool isIntegerConstant(std::string);

bool isClassDefinitionBegin(std::string);
bool isClassDefinitionEnd(std::string);

bool isClassVarDecBegin(std::string line );
bool isClassVarDecEnd(std::string line );

bool isVarDecBegin(std::string line );
bool isVarDecEnd(std::string line );

bool isSubroutineDecBegin(std::string);
bool isSubroutineDecEnd(std::string);

bool isWhileStatementBegin(std::string);
bool isWhileStatementEnd(std::string);

bool isIfStatementBegin(std::string);
bool isIfStatementEnd(std::string);

typedef enum {VOID,CONSTRUCTOR,FUNCTION,METHOD}fnKind;
struct CurrFunctionKind{
	static fnKind IS_A;
	static unsigned int num_of_if;
	static unsigned int num_of_while;
};

class FileList{
private:
	static std::list<std::string> fileARR;
	static std::list<std::string>::iterator currLine;
	static	std::string class_fileName;
	static int class_Var_num;
	FileList(){}
	~FileList(){}
public:
	static string _getCurrLine();
	static string _getNextLine();
	static void _incFilePtr();
	static void _setClassVarNum();
	static void _setClassFileName();
	static int _getClassVarNum();
	static string _getClassFileName();
	static int _getNumVarInSubroutine();
	static void clearClassFileName();
	static void resetClassVarNum();
	static void pushBack(std::string line);
	static void initIterator();
	//	static list<string>::iterator getEnd(){ return fileARR.end();}
	//	static list<string>::iterator getEnd(){ return fileARR.end();}
	static bool atFileEnd();
};

#define getCurrLine() FileList::_getCurrLine()
#define getNextLine() FileList::_getNextLine()
#define incFilePtr() FileList::_incFilePtr()
#define setClassVarNum() FileList::_setClassVarNum()
#define setClassFileName() FileList::_setClassFileName()
#define getClassVarNum() FileList::_getClassVarNum()
#define getClassFileName() FileList::_getClassFileName()
#define getNumVarInSubroutine() FileList::_getNumVarInSubroutine()

#endif
