#!/usr/bin/python
import sys
from class_symbol_table import *
from tag_as import *
#############
class Cup: # a cup is a global container that stores one thing kind of like a global variable
	item = ""
	def __init__(self):
		return
class jPar:
	line_num = 0
	def __init__(self, fileName):
		self.SymTableStack = ListOfSymbolTables()
		self.class_name = "" #name of the class module that we are currently parsing
		self.tabDepth = 0
		self.parenthesisDepth = 0
		self.curlyBracesDepth = 0
		self.isDoingFunction = False
		self.fileArr1 = open(fileName, "r")
		self.fileArr2 = open(fileName, "r")
		self.fileArr2.readline() #this will make fileArr2 = fileArr1 +1
		self.currLine = ""
		self.nextLine = ""
		self.incFilePtr()
		#
		self.compileClass()
	def EOF(self):
		if(self.getCurrLine() == ""):
			return True
		else:
			return False
	def extract_id_tag(self, line=""):
		#return line.replace("<identifier>", "").replace("</identifier>", "").replace("<keyword>", "").replace("</keyword>", "").strip()
		return line[line.find("> ")+2:line.find(" </")].strip()
	def add_to_end_of_id(self,line="", tag=""):
		return line.replace("</identifier>", "</identifier>(%s)" %(tag))
	def currLineHas(self, tokenType, keyWord):
		if(self.getCurrLine().find(tokenType) != -1 and self.getCurrLine().find(keyWord) != -1):
			return True
		return False
	def nextLineHas(self, tokenType, keyWord):
		if(self.getNextLine().find(tokenType) != -1 and self.getNextLine().find(keyWord) != -1):
			return True
		return False
	def getNextLine(self):
		return self.nextLine
	def getCurrLine(self):
		return self.currLine
	def incFilePtr(self):
		self.currLine = self.fileArr1.readline()
		self.nextLine = self.fileArr2.readline()
		jPar.line_num += 1
	def compileClass(self):
		if ( self.EOF() == True):#premature exit
			error("premature exit when compiing class")
		elif( self.getCurrLine().strip() == "<tokens>" ):#start of class
			print "<class>"
			self.incFilePtr()
			self.tabDepth += 1
			self.compileClass()
		elif( self.getCurrLine().strip() == "</tokens>"):#end of class
			self.tabDepth -= 1
			print "</class>"
			self.incFilePtr()
			return
		else: #process intermediate files
			if ( self.currLineHas("<keyword>", "class") == True):
				self.printCurrTokenAndIncrement()
				if( self.currLineHas("<identifier>", "</identifier>") == True):
					self.class_name = self.getCurrLine()#saving the name of the class currently being defined
					self.class_name = self.class_name.replace("<identifier>", "").replace("</identifier>", "").strip()
					self.currLine = self.currLine.replace("</identifier>", "</identifier>(class#def)")  #class type is given its name
					#error(self.class_name);
					self.printCurrTokenAndIncrement()
					self.compileStatements()
					self.compileClass()
				else:
					error("expected class name")
			elif (self.currLineHas("<keyword>", "function") == True):
				#fill with stuff
				self.compileSubroutine()
				
				#error("non class functions not implemented yet")
			else:
				#self.printCurrToken()
				error("expected class declaration123")		
	def compileClassVarDec(self):
		#compiles a static declaration or s field
		#declaration
		
		if(self.EOF() == True):
			error("compile class var probs")
		elif( self.currLineHas("<keyword>", "field") == True):
			self.printMSG_w_tabs("<classVarDec>")
			self.incTabDepth()
			self.printCurrTokenAndIncrement()
			SymbolRow.s_name = "" #clear SymbolRow before using
			SymbolRow.s_kind = "field"
			SymbolRow.s_type = ""
		elif( self.currLineHas("<keyword>", "static") == True):
			self.printMSG_w_tabs("<classVarDec>")
			self.incTabDepth()
			self.printCurrTokenAndIncrement()
			SymbolRow.s_name = "" #clear SymbolRow before using
			SymbolRow.s_kind = "static"
			SymbolRow.s_type = ""
		elif( self.currLineHas("<symbol>", " ; ") == True):
			#reset static variables
			SymbolRow.s_kind = ""
			SymbolRow.s_type = ""
			SymbolRow.s_name = ""
			self.printCurrTokenAndIncrement()
			self.decTabDepth()
			self.printMSG_w_tabs("</classVarDec>")
			#self.SymTableStack.print_list_of_Symbol_Tables()
			return
		else:
			if(SymbolRow.s_type == ""):
				SymbolRow.s_type = self.extract_id_tag(self.currLine)
				if(self.currLineHas("<identifier>", "</identifier>") == True):
					self.currLine = self.add_to_end_of_id( self.currLine, "class#used") # a variable of a user defined type
			elif(SymbolRow.s_name == ""):
				SymbolRow.s_name = self.extract_id_tag(self.currLine)
				#self.SymTableStack.addEntryToCurrScope(SymbolRow.s_name, SymbolRow.s_type, SymbolRow.s_kind)
				self.SymTableStack.addEntryToCurrScope(SymbolRow)
				if(self.currLineHas("<identifier>", "</identifier>") == True):
					#search SymTableStack for a specific identifier and return the #
					self.currLine = self.add_to_end_of_id(self.currLine,"%s#def#%s#%s"%(SymbolRow.s_kind,
																								SymbolRow.s_type,
																								self.SymTableStack.findDataWithFormating(SymbolRow.s_name)))
			elif(self.currLineHas("<symbol>", " , ") == True):
				SymbolRow.s_name = "" # clear name if there is a comma but keep the kind and type
			self.printCurrTokenAndIncrement()
		self.compileClassVarDec()
	def compileSubroutine(self):
		#compiles a complete method, function, or
		#constructor
		if(self.EOF() == True):
			error("subroutine probs")
		elif(self.currLineHas("<keyword>", "constructor") == True or
			self.currLineHas("<keyword>", "function") == True or
			self.currLineHas("<keyword>", "method") == True	):
			self.printMSG_w_tabs("<subroutineDec>")
			self.incTabDepth()
			self.printCurrTokenAndIncrement()
			SymbolRow.s_name = ""#initialize SymbolRow
			SymbolRow.s_kind = "subroutine"
			SymbolRow.s_type = ""
		elif(self.currLineHas("<symbol>", " ( ") == True):
			SymbolRow.s_name = "" #clear SymbolRow when finished using it
			SymbolRow.s_kind = ""
			SymbolRow.s_type = ""
			self.compileParameterList()
		elif(self.currLineHas("<symbol>", " { ") == True):
			self.printMSG_w_tabs("<subroutineBody>")
			self.incTabDepth()
			self.SymTableStack.increaseScope()
			self.compileStatements()
			self.SymTableStack.decreaseScope()
			self.decTabDepth()
			self.printMSG_w_tabs("</subroutineBody>")
			self.decTabDepth()
			self.printMSG_w_tabs("</subroutineDec>")
			return
		else:
			if(SymbolRow.s_type == ""):
				#set type
				if(self.currLineHas("<keyword>", "</keyword>")): #primative type
					SymbolRow.s_type = self.extract_id_tag(self.getCurrLine())
				elif(self.currLineHas("<identifier>", "</identifier>")):#user defined type
					SymbolRow.s_type = self.extract_id_tag(self.getCurrLine())
					self.currLine = self.add_to_end_of_id(self.currLine, "class#used");
			elif(SymbolRow.s_name == ""):
				#set variable name
				if(self.currLineHas("<identifier>", "</identifier>")):
					self.currLine = self.add_to_end_of_id(self.currLine, "subroutine#def#%s"%(self.class_name))#used when a function returns a user defined type
			#error("check %s" % (self.currLine.strip()))
			self.printCurrTokenAndIncrement()
		self.compileSubroutine()
	def compileParameterList(self):
		#compiles a (possibly empty) parameter list,
		#not including the enclosing "()".
		if (self.EOF() == True):
			error( "param error on line: %d" % (line_num))
		elif(self.currLineHas("<symbol>", " ( ") == True	):
			SymbolRow.s_name = ""
			SymbolRow.s_type = ""
			SymbolRow.s_kind = "argument"
			self.printCurrTokenAndIncrement()
			self.printMSG_w_tabs( "<parameterList>")
			self.incTabDepth()
		elif(self.currLineHas("<symbol>", " ) ") == True ):
			SymbolRow.s_name = ""
			SymbolRow.s_type = ""
			SymbolRow.s_kind = ""
			self.decTabDepth()
			self.printMSG_w_tabs( "</parameterList>")
			self.printCurrTokenAndIncrement()
			
			return
		else:
			if(self.currLineHas("<keyword>", "</keyword>")):
				SymbolRow.s_type = self.extract_id_tag(self.getCurrLine())
			elif(self.currLineHas("<identifier>", "</identifier>")):
				if(SymbolRow.s_type == ""): #type not a default type so it must be a user defined type
					SymbolRow.s_type = self.extract_id_tag(self.getCurrLine())
				else: #type is already defined, so it must be variable name
					SymbolRow.s_name = self.extract_id_tag(self.getCurrLine())
					#self.SymTableStack.addEntryToCurrScope(SymbolRow.s_name, SymbolRow.s_type, SymbolRow.s_kind) # add argument-kind variables to symbol table.
					self.SymTableStack.addEntryToCurrScope(SymbolRow)
					self.currLine = self.add_to_end_of_id(self.currLine,"%s#def#%s#%s"%(SymbolRow.s_kind,
																									SymbolRow.s_type,
																									self.SymTableStack.findDataWithFormating(SymbolRow.s_name)))
			elif(self.currLineHas("<symbol>", " , ")): #clear name and type to prepare for next argument in parameter list
				SymbolRow.s_name = ""
				SymbolRow.s_type = ""
			self.printCurrTokenAndIncrement()
		self.compileParameterList()
	def compileVarDec(self):
		#compiles 'var' declaration
		if(self.EOF() == True):
			error("varDec claires war")
		elif(self.currLineHas("<keyword>", "var") == True):
			self.printMSG_w_tabs("<varDec>")
			self.incTabDepth()
			self.printCurrTokenAndIncrement()
			SymbolRow.s_name = "" #clear SymbolRow before use
			SymbolRow.s_kind = "var"
			SymbolRow.s_type = ""
		elif(self.currLineHas("<symbol>", " ; ") == True):
			self.printCurrTokenAndIncrement()
			self.decTabDepth()
			self.printMSG_w_tabs("</varDec>")
			SymbolRow.s_name = "" #clear SymbolRow when done
			SymbolRow.s_kind = ""
			SymbolRow.s_type = ""
			return
		else:
			if(SymbolRow.s_type == ""): #set type
				if(self.currLineHas("<keyword>", "</keyword>")):
					SymbolRow.s_type = self.extract_id_tag(self.getCurrLine())
				elif(self.currLineHas("<identifier>", "</identifier>")):
					SymbolRow.s_type = self.extract_id_tag(self.getCurrLine())
					self.currLine = self.add_to_end_of_id(self.currLine, "class#used" )
			elif(SymbolRow.s_name == ""):#set variable name then add to SymTableStack then print id with tags
				if(self.currLineHas("<identifier>", "</identifier>")):
					SymbolRow.s_name = self.extract_id_tag(self.getCurrLine())
#					self.SymTableStack.addEntryToCurrScope(SymbolRow.s_name, SymbolRow.s_type, SymbolRow.s_kind)
					self.SymTableStack.addEntryToCurrScope(SymbolRow)
					self.currLine = self.add_to_end_of_id(self.currLine,"%s#def#%s#%s"%(SymbolRow.s_kind,
																									SymbolRow.s_type,
																									self.SymTableStack.findDataWithFormating(SymbolRow.s_name)))
			elif(self.currLineHas("<symbol>", " , ")):#clear name another variable of the same type ie var int x,y,z;
				SymbolRow.s_name = ""
			self.printCurrTokenAndIncrement();
		self.compileVarDec()
	def compileStatements(self):
		#compiles a sequence of statements, not
		#including the enclosing "{}".
		if (self.EOF() == True):
			error("messed up on line")
		elif (self.currLineHas("<symbol>", " { ") == True):
			self.printCurrTokenAndIncrement()
		elif (self.currLineHas("<symbol>", " } ") == True):
			self.printCurrTokenAndIncrement()
			return
		else:
			if(self.currLineHas("<keyword>", "function") == True or
				self.currLineHas("<keyword>", "constructor") == True or
				self.currLineHas("<keyword>", "method") == True):
				self.SymTableStack.increaseScope() #increase scope before defining a function
				self.compileSubroutine()
				self.SymTableStack.decreaseScope() #decrease scope once function finishes
			elif(self.currLineHas("<keyword>", "var") == True):# should probably loop this until all vars are finished
				self.compileVarDec()
			elif(self.currLineHas("<keyword>", "field") == True or
				self.currLineHas("<keyword>", "static") == True):
				self.compileClassVarDec()
			elif( self.isStatement() == True):
				self.printMSG_w_tabs("<statements>")
				self.incTabDepth()
				while(self.isStatement() == True):
					if(self.currLineHas("<keyword>", "do") == True):
						self.compileDo()
					elif(self.currLineHas("<keyword>", "let") == True):
						self.compileLet()
					elif(self.currLineHas("<keyword>", "while") == True):
						self.SymTableStack.increaseScope()
						self.compileWhile()
						self.SymTableStack.decreaseScope()
					elif(self.currLineHas("<keyword>", "return") == True):
						self.compileReturn()
					elif(self.currLineHas("<keyword>", "if") == True):
						self.SymTableStack.increaseScope()
						self.compileIf()
						self.SymTableStack.decreaseScope()
					else:
						self.incFilePtr()
				self.decTabDepth()
				self.printMSG_w_tabs("</statements>")
			else:
				self.incFilePtr()
		self.compileStatements()
	def compileDo(self):
		#compiles function call
		if(self.EOF() == True):
			error("problem with do")
		elif(self.currLineHas("<keyword>", "do") == True): #start do
			self.printMSG_w_tabs("<doStatement>")
			self.incTabDepth()
			self.printCurrTokenAndIncrement()
		elif(self.currLineHas("<symbol>", " ; ") == True): #end do
			self.printCurrTokenAndIncrement()
			self.decTabDepth()
			self.printMSG_w_tabs("</doStatement>")
			return
		elif(self.isAJackFunctionCall()):
			self.encapsulateAsFunctionCall()
		else:
			self.printCurrTokenAndIncrement()
		self.compileDo()
	def compileLet(self):
		st = 0
		#states
		LET_DETECTED = 0
		LET_IDENTIFIER = 1
		LET_ARRAY = 2
		LET_EXPRESSION = 3
		LET_EXPECTED_ID = 4
		#
		while(True):
			if(st == LET_DETECTED):
				if(self.currLineHas("<keyword>", " let ")):
					self.printMSG_w_tabs("<letStatement>")
					self.incTabDepth()
					self.printCurrTokenAndIncrement() #print let
					if(self.isAJackArrayCall()):
						st = LET_ARRAY
					elif(self.currLineHas("<identifier>", "</identifier>") and
						self.nextLineHas("<symbol>", " = ")
						):
						st = LET_IDENTIFIER
					else:
						st = LET_EXPECTED_ID
				else:
					st = -1
			elif(st == LET_IDENTIFIER):
				self.currLine = tag_as_used_variable(self.SymTableStack, self.currLine)
				self.printCurrTokenAndIncrement() # print id
				st = LET_EXPRESSION
			elif(st == LET_ARRAY):
				self.encapsulateAsArrayCall()
				st = LET_EXPRESSION
			elif(st == LET_EXPRESSION):
				self.printCurrTokenAndIncrement()#print "="
				self.compileExpression()
				self.printCurrTokenAndIncrement()#print ";"
				self.decTabDepth()
				self.printMSG_w_tabs("</letStatement>")
				break
			elif(st == LET_EXPECTED_ID):
				error("expected an identifier between let and =")
			else:
				error("unknown state")
		return
#		if(self.EOF() == True):
#			error("let probelsm")
#		elif( self.currLineHas("<keyword>", "let") == True):
#			self.printMSG_w_tabs("<letStatement>")
#			self.tabDepth += 1
#			self.printCurrTokenAndIncrement()
#			#clear global Cup
#			Cup.item = ""
#		elif(self.currLineHas("<symbol>", " = ") == True):
#			self.printCurrTokenAndIncrement()
#			self.compileExpression()
#		elif(self.currLineHas("<symbol>", " [ ") ):
#			self.printCurrTokenAndIncrement()
#			self.compileExpression()
#		elif( self.currLineHas("<symbol>", " ; ") == True):
#			self.printCurrTokenAndIncrement()
#			self.tabDepth -= 1
#			self.printMSG_w_tabs("</letStatement>")
#			return
#		else:0
#			#There should be an identifier variable here other wise it is an error
#			if(self.currLineHas("<identifier>", "</identifier")):
#				if(Cup.item == ""):
#					Cup.item = self.extract_id_tag(self.currLine)
#				str = self.SymTableStack.findDataWithFormating(Cup.item)
#				kind = self.SymTableStack.findKindInListOfSymbolTables(Cup.item)
#				self.currLine = "<identifier> %s </identifier>(%s_used)" %(str, kind)
#			self.printCurrTokenAndIncrement()
#		self.compileLet()
	def compileWhile(self):
		if(self.EOF() == True):
			error("while has problems")
		elif( self.currLineHas("<keyword>", "while") == True):
			self.incTabDepth()
			self.printMSG_w_tabs("<whileStatement>")
			self.incTabDepth()
			self.printCurrTokenAndIncrement()
		elif( self.currLineHas("<symbol>", " ( ") == True):
			self.printCurrTokenAndIncrement()
			self.compileExpression()
			self.printCurrTokenAndIncrement()
		elif( self.currLineHas("<symbol>", " { ") == True):
			self.compileStatements()
			self.decTabDepth()
			self.printMSG_w_tabs("</whileStatement>")
			self.decTabDepth()
			return
		else:
			self.printCurrTokenAndIncrement()
		self.compileWhile()
	def compileReturn(self):
		if(self.EOF() == True):
			error("return prob")
		elif(self.currLineHas("<keyword>", "return") == True):
			self.printMSG_w_tabs("<returnStatement>")
			self.incTabDepth()
			self.printCurrTokenAndIncrement()
		elif(self.currLineHas("<symbol>", " ; ") == True):
			self.printCurrTokenAndIncrement()
			self.decTabDepth()
			self.printMSG_w_tabs("</returnStatement>")
			return
		else:
			self.compileExpression()
		self.compileReturn()
	def compileIf (self):
		#compiles an 'if' statement, possibly with a
		#trailing 'else' clause.
		if(self.EOF() == True):
			error("if has problems")
		elif( self.currLineHas("<keyword>", "if") == True):
			self.incTabDepth()
			self.printMSG_w_tabs("<ifStatement>")
			self.incTabDepth()
			self.printCurrTokenAndIncrement()
		elif( self.currLineHas("<keyword>", "else") == True):
			self.printCurrTokenAndIncrement()
		elif( self.currLineHas("<symbol>", " ( ") == True):
			self.printCurrTokenAndIncrement()
			self.compileExpression()
			self.printCurrTokenAndIncrement()
		elif( self.currLineHas("<symbol>", " { ") == True):
			self.compileStatements()
			if( self.currLineHas("<keyword>", "else") == False):
				self.decTabDepth()
				self.printMSG_w_tabs("</ifStatement>")
				self.decTabDepth()
				return
		else:
			self.printCurrTokenAndIncrement()
		self.compileIf()
	def compileExpression(self):
		st = 0
		#States
		EXP_START_EXP = 0
		EXP_UNARY_SYMBOL = 1
		EXP_IDENTIFIER = 2
		EXP_OPERATOR_SYMBOL = 3
		EXP_END = 4
		EXP_STRINGCONST =5
		EXP_PARENTHESES = 8
		#
		while(True):
			if(st == EXP_START_EXP):
				self.printMSG_w_tabs("<expression>")
				self.incTabDepth()
				if( self.isAJackOperator(self.getCurrLine())):
					st = EXP_UNARY_SYMBOL
				elif( self.currLineHas("<identifier>", "</identifier>") or
					self.currLineHas("<integerConstant>", "</integerConstant>") or
					self.currLineHas("<keyword>", "</keyword>")):
					st = EXP_IDENTIFIER
				elif( self.currLineHas("<symbol>", " ( ")):
					st = EXP_PARENTHESES
				elif( self.currLineHas("<stringConstant>", "</stringConstant>")):
					st = EXP_STRINGCONST
				else:
					error("you dropped something weird in this expression")
			elif(st == EXP_END):
				self.decTabDepth()
				self.printMSG_w_tabs("</expression>")
				break
			elif(st == EXP_PARENTHESES):
				self.compileTerm()
				#st = EXP_END
				if(self.isAJackOperator(self.getCurrLine())):
					if(self.currLineHas("<symbol>", " ~ ")):
						error("The ~ is a unary operator")
					st = EXP_OPERATOR_SYMBOL
				elif(self.isAJackClosing_parentheses_semicolon_comma_or_squarebracket(self.getCurrLine())):
					st = EXP_END
				else:
					error("expected operator between identifiers [%s]"%(self.getCurrLine()))
				#
			elif(st == EXP_UNARY_SYMBOL):
				if(self.currLineHas("<symbol>", " ~ ") or self.currLineHas("<symbol>", " - ")):
					self.compileTerm()
				else:
					error("The only unary symbols allowed are ~ and - ")
				if(self.isAJackClosing_parentheses_semicolon_comma_or_squarebracket(self.getCurrLine())):
					st = EXP_END
				elif(self.isAJackOperator(self.getCurrLine())):
					if(self.currLineHas("<symbol>", " ~ ")):
						error("The ~ is a unary operator")
					st = EXP_OPERATOR_SYMBOL
				else:
					error("expected an operator symbol after Identifier")
			elif(st == EXP_IDENTIFIER):
				self.compileTerm()
				if(self.isAJackOperator(self.getCurrLine())):
					if(self.currLineHas("<symbol>", " ~ ")):
						error("The ~ is a unary operator")
					st = EXP_OPERATOR_SYMBOL
				elif(self.isAJackClosing_parentheses_semicolon_comma_or_squarebracket(self.getCurrLine())):
					st = EXP_END
				else:
					error("expected operator between identifiers [%s]"%(self.getCurrLine()))
			elif(st == EXP_OPERATOR_SYMBOL):
				self.printCurrTokenAndIncrement()
				if(self.currLineHas("<symbol>", " ~ ") or self.currLineHas("<symbol>", " - ")):
					st = EXP_UNARY_SYMBOL
				elif(self.currLineHas("<identifier>", "</identifier>") or
					self.currLineHas("<integerConstant>", "</integerConstant>")or
					self.currLineHas("<keyword>", "</keyword>")):
					st = EXP_IDENTIFIER
				elif(self.currLineHas("<symbol>", " ( ")):
					st = EXP_PARENTHESES
				else:
					error("expected identifier or unary operators after an Operand")
			elif(st == EXP_STRINGCONST):
				self.compileTerm()
				if(self.isAJackClosing_parentheses_semicolon_comma_or_squarebracket(self.getCurrLine())):
					st = EXP_END
				else:
					error("stringConstants may not be used with operators")
			else:
				error("reached an unknown state in compileExpression()")
		return
	def compileTerm(self):
		#compiles a "term".  This routine is faced with
		#a slightly difficulty when trying to decide
		#between some of the alternative parsing rules
		#Specifically, if the current token is an
		#identifier, the routine must distinguish between
		#a variable, an array entry, and a subroutine
		#call. A single look-ahead token, which may be
		#one of "[", "(", or "." suffices to distinuish
		#between the three possibilities. Any other
		#token is not part of this term and should not
		#be advanced over.
		
		self.printMSG_w_tabs("<term>")
		self.incTabDepth()
		
		if(self.isAJackFunctionCall()): 	#handle function
			self.encapsulateAsFunctionCall()
		elif(self.isAJackArrayCall()):	#handle array
			self.encapsulateAsArrayCall()
		elif(self.currLineHas("<symbol>", " ( ")):	#handle a nested expression
			self.printCurrTokenAndIncrement() # print " ( "
			self.compileExpression()
			self.printCurrTokenAndIncrement() # print " ) "
		elif(self.currLineHas("<symbol>", " ~ ") or self.currLineHas("<symbol>", " - ")):
			self.printCurrTokenAndIncrement() #print ~ or -
			self.compileTerm()
		elif(self.currLineHas("<identifier>", "</identifier>")):	#handle variables
			self.currLine = tag_as_used_variable(self.SymTableStack, self.getCurrLine())
			self.printCurrTokenAndIncrement()
		else:#handle everything else
			self.printCurrTokenAndIncrement()
		
		self.decTabDepth()
		self.printMSG_w_tabs("</term>")
		
#		self.printMSG_w_tabs("<term>")
#		self.incTabDepth()
#		while(True):
#			if(self.EOF() == True):
#				error("terminal illness")
#			elif( self.currLineHas("<symbol>", " ( ") == True): #probably a function call
#				if(self.isDoingFunction == False):
#					self.printCurrTokenAndIncrement()
#					self.compileExpression()
#					self.printCurrTokenAndIncrement()
#				else: #probably a function
#					self.isDoingFunction = False
#					self.printCurrTokenAndIncrement()
#					self.compileExpressionList()
#					self.printCurrTokenAndIncrement()
#				break
#			elif( self.currLineHas("<symbol>", " [ ")):
#				self.printCurrTokenAndIncrement()
#				self.compileExpression()
#				self.printCurrTokenAndIncrement()
#			elif( self.currLineHas("<symbol>", " ) ") == True or
#				 self.currLineHas("<symbol>", " ] ") == True or
#				 self.currLineHas("<symbol>", " ; ") == True  or
#				 self.currLineHas("<symbol>", " , ") == True  or
#				 self.currLineHas("<symbol>", " + ") == True  or
#				 self.currLineHas("<symbol>", " - ") == True  or#todo modify term so that it handles unary properly
#				 self.currLineHas("<symbol>", " * ") == True  or
#				 self.currLineHas("<symbol>", " / ") == True  or
#				 self.currLineHas("<symbol>", " = ") == True  or
#				 self.currLineHas("<symbol>", " | ") == True  or
#				 self.currLineHas("<symbol>", " &amp; ") == True  or
#				 self.currLineHas("<symbol>", " &lt; ") == True  or
#				 self.currLineHas("<symbol>", " &gt; ") == True  ):
#				break
#			elif( self.currLineHas("<symbol>", " ~ ")):
#				self.printCurrTokenAndIncrement()
#				self.compileTerm()
#			elif(self.isAJackFunctionCall()):
#				self.encapsulateAsFunctionCall()
#			elif(self.isAJackArrayCall()):
#				self.encapsulateAsArrayCall()
#			else:
#				
##				if( self.currLineHas("<symbol>", " . ") == True):
##					self.isDoingFunction = True
#			
#				self.printCurrTokenAndIncrement()
#				
#		self.decTabDepth()
#		self.printMSG_w_tabs("</term>")
#		return
	def compileExpressionList(self):
		#compiles a (possibly empty) comma-separated
		# list of expressions.
		num_of_arg = 0
		self.printMSG_w_tabs("<expressionList>")
		self.incTabDepth()
		while(True):
			if(self.currLineHas("<symbol>", " ) ")):
				break
			if(self.currLineHas("<symbol>", " ,")):
				self.printCurrTokenAndIncrement()
			else:
				self.compileExpression()
				num_of_arg += 1
		self.decTabDepth()
		self.printMSG_w_tabs("</expressionList>")
		return num_of_arg
	def isStatement(self):
		if(self.currLineHas("<keyword>", "do") == True or
			self.currLineHas("<keyword>", "let") == True or
			self.currLineHas("<keyword>", "while") == True or
			self.currLineHas("<keyword>", "return") == True or
			self.currLineHas("<keyword>", "if") == True ):
			return True
		else:
			return False
	def incTabDepth(self):
		self.tabDepth += 1
	def decTabDepth(self):
		self.tabDepth -= 1
	def insertTab(self):
		str = ""
		for i in range(0, self.tabDepth):
			str += "  "
		return str
	def printMSG_w_tabs(self, msg=""):
		print "%s%s" %(self.insertTab(), msg)
	def printCurrToken(self):
		print "%s%s" % (self.insertTab(), self.getCurrLine().strip())
	def printCurrTokenAndIncrement(self):
		#print "%s%s_%d" % (self.insertTab(), self.getCurrLine().strip(), jPar.line_num)
		print "%s%s" % (self.insertTab(), self.getCurrLine().strip())
		self.incFilePtr()
	"""When a function call is detected it will wrap it with a tag.  This is to help
	make it easier to detect what function calls in the code generation stage.
	"""
			#if look-ahead find "."
			#		if it is in the symbol table then tag like a normal variable but add implicit.
			#		otherwise treat the identifier as the Class name that contains the function.
			#				The function should appear after the "."
			#		set a temp variable that will hold the TYPE of the implicit parameter
			
			#if look-ahead finds "("
			#		if no implicit parameter is specified, assume that the function belongs to the current class_name
			#		if there is an implicit parameter then give it a subroutine tag postpended with the TYPE

	def encapsulateAsFunctionCall(self): #this thing could be responsible for a re-write of the "compileDo" function
		implicit_parameter_type = ""
		function_name = ""
		st = 0
		#STATES:
		EAFC_INIT = 0
		EAFC_NOT_FN_CALL = 1
		EAFC_SEARCH_SYMBOL_TABLE = 2
		EAFC_NAME_IN_SYMBOL_TABLE = 3
		EAFC_NAME_NOT_IN_SYMBOL_TABLE = 4
		EAFC_INTERNAL_METHOD_CALL = 5
		EAFC_HANDLE_METHOD = 6
		EAFC_HANDLE_FUNCTION = 7
		EAFC_FINISH = 8
		#
		while(True):
			if( st == EAFC_INIT):
				if( self.isAJackFunctionCall()):
					if(self.nextLineHas("<symbol>", " . ")):# an external method call
						st = EAFC_SEARCH_SYMBOL_TABLE
					if(self.nextLineHas("<symbol>", " ( ")):# either a function or internal method
						st = EAFC_INTERNAL_METHOD_CALL
				else:
					st = EAFC_NOT_FN_CALL
			elif( st == EAFC_SEARCH_SYMBOL_TABLE):
				if(self.SymTableStack.findDataWithFormating(self.extract_id_tag(self.currLine))== ""):
					st = EAFC_NAME_NOT_IN_SYMBOL_TABLE
				else:
					st = EAFC_NAME_IN_SYMBOL_TABLE
			elif(st == EAFC_NAME_IN_SYMBOL_TABLE):
				implicit_parameter_type	= self.SymTableStack.findTypeInListOfSymbolTables(self.extract_id_tag(self.currLine))
				self.printMSG_w_tabs("<callFunction>(%s)"%(implicit_parameter_type))
				self.incTabDepth()
				self.currLine = tag_as_used_implicit_variable(self.SymTableStack, self.currLine)
				self.printCurrTokenAndIncrement() #prints the variable name
				self.printCurrTokenAndIncrement() #prints the "."
				st = EAFC_HANDLE_METHOD
				
			elif(st == EAFC_NAME_NOT_IN_SYMBOL_TABLE):
				implicit_parameter_type = self.extract_id_tag(self.currLine) #assume this is a class function
				self.printMSG_w_tabs("<callFunction>(%s)"%(implicit_parameter_type))
				self.incTabDepth()
				self.currLine = tag_as_used_implicit_class(self.SymTableStack, self.currLine)
				self.printCurrTokenAndIncrement() #prints the class
				self.printCurrTokenAndIncrement() #prints the "."
				st = EAFC_HANDLE_FUNCTION
			elif(st == EAFC_INTERNAL_METHOD_CALL):
				implicit_parameter_type = self.class_name
				self.printMSG_w_tabs("<callFunction>(%s)"%(implicit_parameter_type))
				self.incTabDepth()
				st = EAFC_HANDLE_METHOD
			elif(st == EAFC_HANDLE_METHOD):
				#label method and tag as a method
				#function names should not be in the symbol table
				if(self.SymTableStack.findDataWithFormating(self.extract_id_tag(self.currLine))== ""):
					if(self.nextLineHas("<symbol>", " ( ")):#lookahead confirms function call
						self.currLine = tag_as_used_subroutine(self.SymTableStack, self.currLine,
													implicit_parameter_type, "method")
						function_name = clean_line(self.getCurrLine())
						self.printCurrTokenAndIncrement() #prints function name
						st = EAFC_FINISH
					else:
						st = EAFC_NOT_FN_CALL
				else:
					st = EAFC_NOT_FN_CALL
			elif(st == EAFC_HANDLE_FUNCTION):
				#label function name and tag as a function
				#function names should not be in the symbol table
				if(self.SymTableStack.findDataWithFormating(self.extract_id_tag(self.currLine))== ""):
					if(self.nextLineHas("<symbol>", " ( ")):#lookahead confirms function call
						self.currLine = tag_as_used_subroutine(self.SymTableStack, self.currLine,
															   implicit_parameter_type, "function")
						function_name = clean_line(self.getCurrLine())
						self.printCurrTokenAndIncrement()
						st = EAFC_FINISH
					else:
						st = EAFC_NOT_FN_CALL
				else:
					st = EAFC_NOT_FN_CALL
			elif(st == EAFC_FINISH):
				#handel expression list here
				self.printCurrTokenAndIncrement() #print "("
				num_arg_from_ex = self.compileExpressionList()
				self.printCurrTokenAndIncrement() #print ")"
				self.decTabDepth()
				self.printMSG_w_tabs("</callFunction>(%s.%s##num_arg#%d)"%(implicit_parameter_type, function_name ,num_arg_from_ex))
				break #out of loop and return
			elif( st == EAFC_NOT_FN_CALL):
				error("expected a function call here")
			else:
				error("found unknown state EAFC")
		return
	def encapsulateAsArrayCall(self):
		st = 0
		#states
		EAAC_CONFIRM_ARRAY = 0
		EAAC_PROBLEMS = 1
		EAAC_HANDLE_ARRAY = 2
		#
		while(True):
			if(st == EAAC_CONFIRM_ARRAY):
				if(self.isAJackArrayCall()):
					st = EAAC_HANDLE_ARRAY
				else:
					st = EAAC_PROBLEMS
			elif(st == EAAC_HANDLE_ARRAY):
				self.printMSG_w_tabs("<callArray>")
				self.incTabDepth()
				self.currLine = tag_as_used_variable(self.SymTableStack, self.currLine)
				self.printCurrTokenAndIncrement()#array var name
				self.printCurrTokenAndIncrement()# " [ "
				self.compileExpression()
				self.printCurrTokenAndIncrement()# " ] "
				self.decTabDepth()
				self.printMSG_w_tabs("</callArray>")
				break #out and go back to what it was doing earlier
			elif(st == EAAC_PROBLEMS):
				error("expected an array call")
			else:
				error("found unknown state EAAC")
		return
	""" Checks if a function call is happening.  If there is a "." or a "(" found in the look
		ahead then it is probably a function call.  
	"""
	def isAJackFunctionCall(self):
		if(self.currLineHas("<identifier>", "</identifier>")):
			if(self.nextLineHas("<symbol>", " . ")):# an external method call
				return True
			if(self.nextLineHas("<symbol>", " ( ")):# either a function or internal method
				return True
		return False
	def isAJackArrayCall(self):
		if(self.currLineHas("<identifier>", "</identifier")):
			if(self.nextLineHas("<symbol>", " [ ")):
				return True
		return False
	def isAJackOperator(self, line):
		if(self.currLineHas("<symbol>", " + ") or
			self.currLineHas("<symbol>", " - ") or
			self.currLineHas("<symbol>", " * ") or
			self.currLineHas("<symbol>", " / ") or
			self.currLineHas("<symbol>", " ~ ") or
			self.currLineHas("<symbol>", " = ") or
			self.currLineHas("<symbol>", " | ") or
			self.currLineHas("<symbol>", " &amp; ") or
			self.currLineHas("<symbol>", " &lt; ") or
			self.currLineHas("<symbol>", " &gt; ")):
			return True
		else:
			return False
	def isAJackClosing_parentheses_semicolon_comma_or_squarebracket(self,line):
		if(self.currLineHas("<symbol>", " ) ") or
			self.currLineHas("<symbol>", " ; ") or
			self.currLineHas("<symbol>", " , ") or
			self.currLineHas("<symbol>", " ] ")):
			return True
		else:
			return False
#################################



def error(msg):
	print "%s %d" % (msg, jPar.line_num)
	sys.exit(1)

def start_prog():
	jPar_var = jPar(sys.argv[1])

if __name__ == "__main__":
	start_prog()


