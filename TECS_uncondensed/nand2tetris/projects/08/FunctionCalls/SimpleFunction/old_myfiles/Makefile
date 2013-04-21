CXX = gcc
PATH_c = /Users/derrickho/Dropbox/Documents/XcodeProjects/vm_2_hack/vm_2_hack
VM_NAME = SimpleFunction
IN_FILE = ../$(VM_NAME).vm #input file name
OUT_FILE = ../$(VM_NAME).asm #output file name
EXE = ./VM_trans

help: 
	@echo ""
	@echo "**Displaying make options**"
	@echo "make		- Shows options"
	@echo "make run	- runs local program"
	@echo "make all	- Compiles then runs local program."
	@echo "make compile	- compiles files"
	@echo "make clean	- deletes produced files i.e. *.o *~ a.out"
	@echo ""


run: 
	($(EXE) $(IN_FILE)) > $(OUT_FILE) 

all:
	make compile && make run
compile: $(PATH_c)/main.o
	$(CXX) $(PATH_c)/main.o -o $(EXE)

clean: 
	rm -rf *.o *~ $(OUT_FILE) $(EXE)

#link all the liner files together
## transform bmp into a obj_data file with no page
############################
## list dependancies and create .o files
## the files on the right will be used to make the linker file on the left of the semicolon
#------------------------------------
main.o: $(PATH_c)/main.c
