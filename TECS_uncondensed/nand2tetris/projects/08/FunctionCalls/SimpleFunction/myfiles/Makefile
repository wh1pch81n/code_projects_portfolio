CXX = gcc
PATH_c = /Users/derrickho/Dropbox/Documents/XcodeProjects/vm_2_hack/vm_2_hack
VM_NAME = SimpleFunction
IN_FILE1 = ../$(VM_NAME).vm #input file name
IN_FILE2 = ../Sys.vm
OUT_FILE = ../$(VM_NAME).asm #output file name
EXE = ./VM_trans
DEPEND = $(PATH_c)/main.o $(PATH_c)/vm_2_hack.o 

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
	($(EXE) $(IN_FILE1) add_bootstrap) > $(OUT_FILE) ; ($(EXE) $(IN_FILE2)) >> $(OUT_FILE);

all:
	make compile && make run
compile: $(DEPEND)
	$(CXX) $(DEPEND) -o $(EXE)

clean: 
	rm -rf *.o *~ $(OUT_FILE) $(EXE)

#link all the liner files together
## transform bmp into a obj_data file with no page
############################
## list dependancies and create .o files
## the files on the right will be used to make the linker file on the left of the semicolon
#------------------------------------
main.o: $(PATH_c)/main.c $(PATH_c)/vm_2_hack_fn_arr.h
vm_2_hack_o: $(PATH_c)/vm_2_hack.h $(PATH_c)/vm_2_hack.c
