project ongoing: started Dec 2012

hack_assembler:
	This takes as input the Hack assembly language (which was designed
	specifically by this book) and output the binary codes that would
	work on the Hack computer.

hack_vm_translator:
	The vm in this context is an intermediate language between a high level
	language and assembly.  It is meant to represent a generic computer
	that compilers will aim for.  The compiler creates generic vm commands
	and the vm translator take it in as input.  it outputs Hack assembly 
	code.  

	Theoretically, the VM translator can be modified to work for
	any computer hardware.  This shows the beauty of the VM paradime
	where all sorts of high level languages become ONE VM; freeing the
	high level parts from having to deal with low level stuff.  As long
	as both sides work with the VM, then each side can do their own thing
	without massively effecting the other.

hack_compiler:
	is still a work in progress
