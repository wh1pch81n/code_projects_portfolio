from class_symbol_table import *
def clean_line(line=""):
	return line[line.find("> ")+2:line.find(" </")].strip()

def tag_as_used_implicit_variable(L=ListOfSymbolTables(), line=""):
	key = clean_line(line)
	name = L.findDataWithFormating(key)
	type = L.findTypeInListOfSymbolTables(key)
	kind = L.findKindInListOfSymbolTables(key)
	return "%s(%s#%s#%s#%s#%s)\n"%(line.strip(), kind, "used", type, name, "implicit")

def tag_as_used_variable(L=ListOfSymbolTables(), line=""):
	key = clean_line(line)
	name = L.findDataWithFormating(key)
	type = L.findTypeInListOfSymbolTables(key)
	kind = L.findKindInListOfSymbolTables(key)
	return "%s(%s#%s#%s#%s)\n"%(line.strip(), kind, "used", type, name)

def tag_as_used_implicit_class(L=ListOfSymbolTables(), line=""):
	return "%s(class#used#implicit)\n"%(line.strip())

def tag_as_used_subroutine(L=ListOfSymbolTables(), line="", type="", kind=""):
	return "%s(subroutine#used#%s#%s)\n"%(line.strip(), type, kind)