PARSER = /Users/derrickho/Dropbox/Documents/XcodeProjects/jackParser/jackParser.py
TOKEN =  /Users/derrickho/Dropbox/Documents/XcodeProjects/jackTokenizerModule/jackTokenizer.py
CODE_GEN = /Users/derrickho/Library/Developer/Xcode/DerivedData/jackCompilerPart2_cpp-bkabdqmvlbfvaiadukccqvsorndr/Build/Products/Debug/jackCompilerPart2_cpp
#BOOK_JACK_COMPILER = ../../../../tools/JackCompiler.sh
BOOK_JACK_COMPILER = /Users/derrickho/Dropbox/nand2tetris/tools/JackCompiler.sh
TARGET1 = ../Main
TARGET2 = ../Square
TARGET3 = ../SquareGame

MY_OUT_XML_t = tokenCMP
MY_OUT_XML_p = parseCMP

VM_NAME_1 = ./Main.vm
VM_NAME_2 = ./Square.vm
VM_NAME_3 = ./SquareGame.vm

FULLPATH = /Users/derrickho/Dropbox/nand2tetris/projects/10/test_vm_cmd_square/

run_and_compare: 
	@make GEN A B C; echo "\tDONE"

A:
	@python $(TOKEN) $(TARGET1).jack > $(MY_OUT_XML_t)_1.xml;
	@python $(PARSER) $(MY_OUT_XML_t)_1.xml > $(MY_OUT_XML_p)_1.xml;
	@($(CODE_GEN) $(MY_OUT_XML_p)_1.xml > $(VM_NAME_1)) 2>&1 ;  #STDERR send to terminal output. STDOUT sent to file
	@diff -w -B -y $(TARGET1).vm $(VM_NAME_1) >diff_report_1.txt # compare book compiler with my compiler
B:
	@python $(TOKEN) $(TARGET2).jack > $(MY_OUT_XML_t)_2.xml;
	@python $(PARSER) $(MY_OUT_XML_t)_2.xml > $(MY_OUT_XML_p)_2.xml;
	@($(CODE_GEN) $(MY_OUT_XML_p)_2.xml > $(VM_NAME_2)) 2>&1 ; #STDERR send to terminal output. STDOUT sent to file
	@diff -w -B -y $(TARGET2).vm $(VM_NAME_2) >diff_report_2.txt # compare book compiler with my compiler

C:
	@python $(TOKEN) $(TARGET3).jack > $(MY_OUT_XML_t)_3.xml;
	@python $(PARSER) $(MY_OUT_XML_t)_3.xml > $(MY_OUT_XML_p)_3.xml;
	@($(CODE_GEN) $(MY_OUT_XML_p)_3.xml > $(VM_NAME_3)) 2>&1 ; #STDERR send to terminal output. STDOUT sent to file
	@diff -w -B -y $(TARGET3).vm $(VM_NAME_3) >diff_report_3.txt # compare book compiler with my compiler
GEN:
	@$(BOOK_JACK_COMPILER) $(FULLPATH) #generate a compare VM with the book's jack compiler
clean:
	rm $(MY_OUT_XML_t)* $(MY_OUT_XML_p)* diff_report_* *.vm ../*.vm
