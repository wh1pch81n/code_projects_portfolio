#!/usr/bin/python
import sys
class pair:
	def __init__(self, tokenType="", token=""):
		self.tokenType = tokenType
		self.token = token
	def print_pair(self):
		print "[ %s, %s]" % (self.tokenType, self.token)

class jTok:
	def __init__(self,fileName):
		#constants
		self.enum_KEYWORD = 0;
		self.enum_SYMBOL = 1;
		self.enum_IDENTIFIER = 2;
		self.enum_INT_CONST = 3;
		self.enum_STRING_CONST = 4;
		#other
		self.isMultiLineComment = False
		self.fileArr = open(fileName, "r")
		self.tokenList = []
		for i in self.fileArr:
			if ( i.strip() != ""):
				self.determine_token_type( i.strip() )
		#for j in self.tokenList:
		#	j.print_pair()
	def tokenListString(self):
		str = ""
		str += "<tokens>\n"
		for j in self.tokenList:
			str += "<" + j.tokenType + "> "
			str += j.token
			str += " </" + j.tokenType +">\n"
		str += "</tokens>"
		return str 
	def isLetter(self, var=''):
		if( ord(var) >= ord('A') and  ord(var) <= ord('Z')):
			return True
		elif( ord(var) >= ord('a') and ord(var) <= ord('z')):
			return True
		elif(var== '_'):
			return True
		else:
			return False
	def isNum(self, val=''):
		if( ord(val) >= ord('0') and ord(val) <= ord('9')):
			return True
		else:
			return False
	def isSymbol(self, val=''):
		if ( val == '{' or val == '}' or
			val == '(' or val == ')' or
			val == '[' or val == ']' or
			val == '.' or val == ',' or
			val == ';' or
			val == '+' or val == '-' or
			val == '*' or val == '/' or
			val == '&' or val == '|' or
			val == '<' or val == '>' or
			val == '=' or val == '~'
			):
			return True
		else:
			return False
	def isKeyword(self, var=""):
		if( var == "class" or
			var == "method" or
			var == "function" or
			var == "constructor" or
			var == "int" or
			var == "boolean" or
			var == "char" or
			var == "void" or
			var == "var" or
			var == "static" or
			var == "field" or
			var == "let" or
			var == "do" or
			var == "if" or
			var == "else" or
			var == "while" or
			var == "return" or
			var == "true" or
			var == "false" or
			var == "null" or
			var == "this"	):
			return True
		else:
			return False
	
	def determine_token_type(self, line):
		#every token found in the line will be pushed to a list of pairs
		left = 0
		right = 0
		
		while(left < len(line)):
			#check if this is part of a multi line comment
			if(self.isMultiLineComment == True):
				if ( line.find( "*/", left ) != -1):
					self.isMultiLineComment = False
					left = 2 + line.find( "*/", left)
					right = left
					continue
				else:
					return
			#check if it is a "//" type comment
			if( line[left] == '/'):
				if( line[left+1] == '/'):
					return
				if( line[left+1] == '*'):
					self.isMultiLineComment = True 
					left = left + 2
					right = left
					continue
			#check if it is a keyword or identifier
			if( self.isLetter(line[left]) == True):
				while( self.isLetter(line[right]) == True):
					right += 1
				while( self.isNum( line[right]) == True):
					right += 1
				substr = line[left:right]
				if( self.isKeyword(substr) == True):
					self.tokenList.append(pair("keyword", substr))
				else: #isIdentifier
					self.tokenList.append(pair( "identifier", substr))
			#check if it is a symbol
			elif( self.isSymbol(line[left]) == True):
				if (line[left] == '<'):
					self.tokenList.append(pair("symbol", "&lt;"))
				elif(line[left] == '>'):
					self.tokenList.append(pair("symbol", "&gt;"))
				elif(line[left] == '&'):
					self.tokenList.append(pair("symbol", "&amp;"))
				else:
					self.tokenList.append(pair("symbol", line[left]))
				right += 1
			#check if it is a number
			elif( self.isNum(line[left]) == True):
				while(self.isNum(line[right]) == True):
					right += 1
				self.tokenList.append(pair("integerConstant", line[left:right]))
			#check if it is a string
			elif( line[left] == '\"'):
				right += 1
				while(line[right] != '\"'):
					right += 1
				right += 1
				self.tokenList.append(pair("stringConstant", line[left+1:right-1]))
			#check if it is a space or tab
			elif( line[left] == ' ' or line[left] == '\t'):
				right += 1
			#otherwise is is an unknown bit
			else:
				self.tokenList.append(pair("Xx_unknown_xX", line[left]))
				right += 1
			#move left to the beginning of next token
			left = right
		return
def start_prog():
	if ( len(sys.argv) == 2):
		jTok_v = jTok(sys.argv[1])# read in jack file
		print jTok_v.tokenListString()
#	elif (len(sys.argv) == 3) :
#		jTok_v = jTok(sys.argv[1])# read in jack file
#		#save Token xml to file
#		myTokenFile = open("tokenCMP.xml", "w")
#		myTokenFile.write( jTok_v.tokenListString() )
#		myTokenFile.close()
#		#get their token file
#		theirTokenFile = open(sys.argv[2], "r")
#		myTokenFile = open("tokenCMP.xml", "r")
#		for i in range(0, len(theirTokenFile)):
#			print theirTokenFile[i]
	else:
		print "need 2 arguments"
		print "python <prog_name> <fileName>"
if __name__ == "__main__":
	start_prog();