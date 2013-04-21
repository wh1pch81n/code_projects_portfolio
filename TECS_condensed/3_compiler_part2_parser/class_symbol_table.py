class SymbolRow:
	s_name = ""
	s_kind = ""
	s_type = ""
	def __init__(self):
		return

###################
class SymbolTable(dict):
	def __init__(self):
		self.static_n = 0
		self.field_n = 0
		self.var_n = 0
		self.argument_n = 0
		#self.dictionary = dict()
		return
	def addEntry(self, name="", type="", kind=""):
		number = 0
		if(kind == "static"):
			number = self.static_n
			self.static_n += 1
		elif(kind == "field"):
			number = self.field_n
			self.field_n += 1
		elif(kind == "var"):
			number = self.var_n
			self.var_n += 1
		elif(kind == "argument"):
			number = self.argument_n
			self.argument_n += 1
		else:
			error("can't figure out kind")
		#self.dictionary[name] = (type, kind, number)
		self[name] = (type,kind, number)
		return
	def getTypeOf(self, name=""):#returns the type of the variable as string
		return str(self[name][0])
	def getKindOf(self, name=""):#returns the kind of the variable as a string
		return str(self[name][1])
	def getHashOf(self, name=""):#returns the num of the variable as a string
		return str(self[name][2])
	def print_symbolTable(self):
		for i in self:
			print "%-15s %-15s %-9s %-3s" %(i, self.getTypeOf(i), self.getKindOf(i), self.getHashOf(i) )
class ListOfSymbolTables:
	def __init__(self):
		self.a_list_of_symbolTables = [SymbolTable()]
		self.scope_n = 0
	def increaseScope(self):#increases scope depth by one
		self.scope_n += 1
		self.a_list_of_symbolTables.append(SymbolTable())
	def decreaseScope(self):#decreses scope depth by one
		if(self.scope_n == 0):
			return
		else:
			self.scope_n -= 1
			self.a_list_of_symbolTables.pop()
#	def addEntryToCurrScope(self, name="", type="", kind=""):
#		self.a_list_of_symbolTables[self.scope_n].addEntry(name, type, kind)
	def addEntryToCurrScope(self, S_row= SymbolRow()):
		self.a_list_of_symbolTables[self.scope_n].addEntry(S_row.s_name, S_row.s_type, S_row.s_kind)
	def print_list_of_Symbol_Tables(self):
		for i in self.a_list_of_symbolTables:
			print "[%d]-------->" %(self.a_list_of_symbolTables.index(i))
			i.print_symbolTable()
	"""Will search for a specific key in the list of symbol tables.
		it will start the search at the tail and if it doesn't find it it will go one
		step towards the head.  If it doesn't find the key then the identifier
		will be assumed to be a function name
		
		Return: <name>_<scope#>_<Symtable#>
		"""
	def findDataWithFormating(self, name=""):
		str = ""
		for i in reversed(self.a_list_of_symbolTables):
			if( name in i):
				str = "%s_%d_%s" % ( name, self.a_list_of_symbolTables.index(i), i.getHashOf(name) )
				break
		#if(str == ""):
		#	error("variable \"%s\" not declared in scope" %(name))
		return str
	"""Will search for specific key in the list of symbols.
		If it finds it it will return the kind as a string
		otherwise it will return an empty string"""
	def findKindInListOfSymbolTables(self, name=""):
		str = ""
		for i in reversed(self.a_list_of_symbolTables):
			if( name in i):
				str = "%s" % ( i.getKindOf(name) )
				break
		return str
	"""
		Will search for a specific key in the list of symbols.
		If it finds it it will return the type as a string
		otherwise it will return an empty string
	"""
	def findTypeInListOfSymbolTables(self, name=""):
		str = ""
		for i in reversed(self.a_list_of_symbolTables):
			if( name in i):
				str = "%s" % ( i.getTypeOf(name) )
				break
		return str
###################
