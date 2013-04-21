//
//  VM_2_hack.c
//  vm_2_hack
//
//  Created by Derrick Ho on 12/18/12.
//  Copyright (c) 2012 Derrick Ho. All rights reserved.
//

#include "vm_2_hack.h"

char file_name[1024];
char function_name[1024];
//function definitions
void add_bootstrap(){
	//Adds the default places for SP
	printf("@256\n");
	printf("D=A\n");
	printf("@SP\n");
	printf("M=D\n");
	//call Sys.init with zero arguments
	call_f_n(SYS_INIT);
	//load system functions
	define_sys_call();
	define_sys_return();
	//define_sys_less_than();
	//define_sys_greater_than();
	//define_sys_equal();
	define_sys_LTGTEQ();
	define_sys_fn();
}
//deprecated
void define_sys_equal(){
	char * EQ_label = "Sys.Eq_IS_EQ";
	printf("(%s)\n", SYS_EQUAL);
	printf("@ARG\n");
	printf("A=M\n");
	printf("D=M\n");
	printf("A=A+1\n");
	printf("D=D-M\n");
	printf("@%s\n", TEMP_reg);
	printf("M=%d\n", HACK_TRUE);
	printf("@%s\n", EQ_label);
	printf("D;JEQ\n");
	printf("@%s\n", TEMP_reg);
	printf("M=%d\n", HACK_FALSE);
	printf("(%s)\n", EQ_label);
	push_TEMP("0");
	return_f("");
}
//deprecated
void define_sys_greater_than(){
	char * GT_label = "Sys.Gt_IS_GT";
	printf("(%s)\n", SYS_GREATER_THAN);
	printf("@ARG\n");
	printf("A=M\n");
	printf("D=M\n");
	printf("A=A+1\n");
	printf("D=D-M\n");
	printf("@%s\n", TEMP_reg);
	printf("M=%d\n", HACK_TRUE);
	printf("@%s\n", GT_label);
	printf("D;JGT\n");
	printf("@%s\n", TEMP_reg);
	printf("M=%d\n", HACK_FALSE);
	printf("(%s)\n", GT_label);
	push_TEMP("0");
	return_f("");
}
//deprecated 
void define_sys_less_than(){
	char * LT_label = "Sys.Lt_IS_LT";
	printf("(%s)\n", SYS_LESS_THAN);
	printf("@ARG\n");
	printf("A=M\n");
	printf("D=M\n");
	printf("A=A+1\n");
	printf("D=D-M\n");
	printf("@%s\n", TEMP_reg);
	printf("M=%d\n", HACK_TRUE);
	printf("@%s\n", LT_label);
	printf("D;JLT\n");
	printf("@%s\n", TEMP_reg);
	printf("M=%d\n", HACK_FALSE);
	printf("(%s)\n", LT_label);
	push_TEMP("0");
	return_f("");
}

void define_sys_LTGTEQ(){
	printf("(%s)\n", SYS_LTGTEQ);
	printf("@%s\n", TEMP1); //save return addr into temp var
	printf("M=D\n");
	printf("@%s\n", TEMP2); //set boolean answer default true
	printf("M=%d\n", HACK_TRUE);
	printf("@SP\n"); //pop get top
	printf("AM=M-1\n");
	printf("D=M\n");
	printf("A=A-1\n"); //get top2
	printf("D=M-D\n"); // d = top2-top
	printf("@%s\n", TEMP3);
	printf("M=D\n");
	printf("@%s\n", TEMP0);
	printf("D=M\n");
	printf("@%s\n", SYS_LTGTEQ_LT);
	printf("D;JLT\n");
	printf("@%s\n", SYS_LTGTEQ_GT);
	printf("D;JGT\n");
	
	printf("(%s)\n", SYS_LTGTEQ_EQ);
	printf("@%s\n", TEMP3); //retrieve cond jump arg
	printf("D=M\n");
	printf("@%s\n", SYS_LTGTEQ_EQ_IS_TRUE);
	printf("D;JEQ\n");
	printf("@%s\n", TEMP2);
	printf("M=0\n");
	printf("(%s)\n", SYS_LTGTEQ_EQ_IS_TRUE);
	printf("@%s\n", SYS_LTGTEQ_RET);
	printf("0;JMP\n");	
	
	printf("(%s)\n", SYS_LTGTEQ_LT);
	printf("@%s\n", TEMP3); //retrieve cond jump arg
	printf("D=M\n");
	printf("@%s\n", SYS_LTGTEQ_LT_IS_TRUE);
	printf("D;JLT\n");
	printf("@%s\n", TEMP2);
	printf("M=0\n");
	printf("(%s)\n", SYS_LTGTEQ_LT_IS_TRUE);
	printf("@%s\n", SYS_LTGTEQ_RET);
	printf("0;JMP\n");	
	
	printf("(%s)\n", SYS_LTGTEQ_GT);
	printf("@%s\n", TEMP3); //retrieve cond jump arg
	printf("D=M\n");
	printf("@%s\n", SYS_LTGTEQ_GT_IS_TRUE);
	printf("D;JGT\n");
	printf("@%s\n", TEMP2);
	printf("M=0\n");
	printf("(%s)\n", SYS_LTGTEQ_GT_IS_TRUE);
	printf("@%s\n", SYS_LTGTEQ_RET);
	printf("0;JMP\n");

	printf("(%s)\n", SYS_LTGTEQ_RET);
	printf("@%s\n", TEMP2);
	printf("D=M\n");
	printf("@SP\n");
	printf("A=M-1\n");
	printf("M=D\n");
	printf("@%s\n", TEMP1);
	printf("A=M\n");
	printf("0;JMP\n");
	
}

/*a generic return subroutine part of the system functions.*/
void define_sys_return(){
	printf("(%s)\n", SYS_RETURN);
	
	printf("@LCL\n"); //FRAME is a temporaty variable.  frame is temp[0]
	printf("D=M\n");
	printf("@%s\n", TEMP_reg); //save LCL in temp[0]
	printf("M=D\n"); //temp[0] <- LCL
		
	//RET = *(FRAME-5)
	printf("A=D-A\n");
	printf("D=M\n");
	printf("@%s\n", TEMP_reg);
	printf("M=D\n");
	
	//*ARG = pop();  reposition the return value of the previous state
	printf("@SP\n");
	printf("AM=M-1\n");
	printf("D=M\n");
	printf("@ARG\n");
	printf("A=M\n");
	printf("M=D\n");
	
	//SP = ARG+1;  restore SP of the prev state
	printf("@ARG\n");
	printf("D=M+1\n");
	printf("@SP\n");
	printf("M=D\n"); //SP = ARG+1; end
	
	// THAT = *(FRAME-1) ;restore THAT of the prev state
	printf("@LCL\n");
	printf("AM=M-1\n"); //frame-1
	printf("D=M\n"); //*(frame-1)
	printf("@THAT\n");
	printf("M=D\n"); // THAT = *(FRAME-1); end
	
	// THIS = *(FRAME-2) ;restore THIS of the prev state
	printf("@LCL\n");
	printf("AM=M-1\n"); //frame-2
	printf("D=M\n"); //*(frame-2)
	printf("@THIS\n");
	printf("M=D\n"); // THIS = *(FRAME-2); end
	// ARG = *(FRAME-3) ;restore ARG of the prev state
	printf("@LCL\n");
	printf("AM=M-1\n"); //frame-3
	printf("D=M\n"); //*(frame-3)
	printf("@ARG\n");
	printf("M=D\n"); // ARG = *(FRAME-3); end
	// LCL = *(FRAME-4) ;restore LCL of the prev state
	printf("@LCL\n");
	printf("AM=M-1\n"); //frame-4
	printf("D=M\n"); //*(frame-4)
	printf("@LCL\n");
	printf("M=D\n"); // LCL = *(FRAME-4); end
	
	//goto RET ;goto return address specified by previous state
	printf("@%s\n", TEMP_reg);
	printf("A=M\n");
	printf("0;JMP\n");

}


/*When the vm uses a call command, the call_f_n() is invoked.
 which then calls define_sys_call() which is a a generic way
 to back things up on the stack prior to jumping to a function
 */
void define_sys_call(){
	printf("(%s)\n", SYS_CALL);
	//back up num of arguments
	//	//save # of args;  aka R14 = n;
		printf("@%s\n", call_num_arg);
		printf("M=D\n");

	
	
	//Return addr is saved in R13; retrieve it and push return addr on stack.
	printf("@%s\n", call_ret_addr);
	printf("D=M\n");
	printf("@SP\n");
	printf("A=M\n");
	printf("M=D\n");
	printf("@SP\n");
	printf("M=M+1\n");
	
	//push LCL save the current "lcl" on the stack
	printf("@LCL\n");
	printf("D=M\n");
	printf("@SP\n");
	printf("A=M\n");
	printf("M=D\n");
	printf("@SP\n");
	printf("M=M+1\n");
	
	//push ARG save the current "arg" on the stack
	printf("@ARG\n");
	printf("D=M\n");
	printf("@SP\n");
	printf("A=M\n");
	printf("M=D\n");
	printf("@SP\n");
	printf("M=M+1\n");
	
	//push THIS save the current "this" on the stack
	printf("@THIS\n");
	printf("D=M\n");
	printf("@SP\n");
	printf("A=M\n");
	printf("M=D\n");
	printf("@SP\n");
	printf("M=M+1\n");
	
	//push THAT save the current "that" on the stack
	printf("@THAT\n");
	printf("D=M\n");
	printf("@SP\n");
	printf("A=M\n");
	printf("M=D\n");
	printf("@SP\n");
	printf("M=M+1\n");
	
	//ARG = SP-n-5 ; reposition ARG; n is stored in R14
	printf("@SP\n");
	printf("D=M\n");
	printf("@%s\n", call_num_arg);
	printf("D=D-M\n");
	printf("@5\n");
	printf("D=D-A\n");
	printf("@ARG\n");
	printf("M=D\n");

	//lcl = sp //reposition lcl
	printf("@SP\n");
	printf("D=M\n");
	printf("@LCL\n");
	printf("M=D\n"); //LCL = SP; end
	
	//goto fn;  the fn line number is stored in R15
	printf("@%s\n", call_fn_line);
	printf("A=M\n");
	printf("0;JMP\n");
}

/*Calling a function "f" after "n" arguments have been pushed on to the stack.
 breif: save current state then jump to the function's label.
 */
void call_f_n(char* args){
	static int rand_num= 0;
	char f[256]; char n[10];
	int i =	sscanf(args, "%s %s", f,n);//check if I got valid data
	switch (i ) {
		case 0: sprintf (f, "Sys.init");
		case 1: i = 0;
			break;
		default://this is the place a correct call will go. it has "i" arguments on the stack
			i = (int)strtoul(n , NULL, 10);
	}

	
	//push return-address using label decalred below
	char num[1024];
	sprintf(num , "%s_%s_%d", file_name,f, rand_num++); //function name appended with a number and prepended with filename
	//push_LABEL(num);
	
	//push label to R13  aka line number of return address saved to R13
	printf("@%s\n",num);
	printf("D=A\n");
	printf("@%s\n", call_ret_addr);
	printf("M=D\n");
		
	//save line number of function to jump to. aka R15 = @f
	printf("@%s\n", f);
	printf("D=A\n");
	printf("@%s\n", call_fn_line);
	printf("M=D\n");
	
	//	//save # of args;  aka R14 = n;
		printf("@%d\n", i);
		printf("D=A\n");

	//perform sys.call
	printf("@%s\n", SYS_CALL);
	printf("0;JMP\n");
	
	//declare "label" for the return address
	//add_label(num);
	char temp[1024];
	sscanf(num, "%s", temp);
	printf("(%s)\n", temp);
}
/*declaring a function "f" that has "k" local variables.
 Functions are usually defined after the bootstrap.
 The sys.init function should be the the last function (out of convention not necessity) */
void function_f_k(char* args){
	static int  unknown_num = 0;
	char f[256]; char n[10];
	int i =	sscanf(args, "%s %s", f,n);//check if I got valid data
	switch (i ) {
		
		case 0: sprintf (f, "(%s_%d)", "UNNAMED_FN", unknown_num++);
		case 1: i = 0;
			break;
		default://this is the place a correct call will go. it has "i" arguments on the stack
			i = (int)strtoul(n , NULL, 10);
	}
	//set global string "function_name" to properly prepend labels
	strcpy(function_name, f );
	//add_label(f);//declare a label for the function start point;
	char temp[1024];
	sscanf(f, "%s", temp);
	printf("(%s)\n", temp);
	int k;//k= number of local variables initialized all to zero ;
	for (k = 0; k < i ; ++k) {push_CONST("0");}
}

/*return from a function and restore previous state*/
void return_f(char* args){
	printf("@%s\n", SYS_RETURN);
	printf("0;JMP\n");
}

/*conditional jump:
 The top of the stack gets placed in D.
 if D equals zero do not jump to label; just do next instruction.
 if D is greater or less than zero, jump to label
 */
void if_goto(char* arg){
	char left[1024];
	sscanf(arg, "%1023s", left);
	printf("@SP\n");
	printf("AM=M-1\n");
	printf("D=M\n");
	
	printf("@%s$%s\n", function_name, left);
	printf("D;JNE\n");
}
/*unconditional jump:
 set the A register to hold the label name.
 Do the unconditional jump;
 */
void do_goto(char* arg){
	char left[1024];
	sscanf(arg, "%1023s", left);
	printf("@%s$%s\n", function_name, left);
	printf("0;JMP\n");
}

/*
 the label is prepended with the name of the function calling it.
 i.e. 
 (inside function screen.rect it makes a label if_true0)
 label <function name>$<labelname>
 label screen.rect$if_true0
 */
void add_label(char* arg){
	char temp[1024];
	sscanf(arg, "%s", temp);
	printf("(%s$%s)\n", function_name, temp);
}

void push_STATIC(char* offset){
	printf("@STATIC_%s.%d\n", file_name,(int)strtoul(offset, NULL, 10) );
	printf("D=M\n");
	printf("@SP\n");
	printf("AM=M+1\n");//AM=M+1
	printf("A=A-1\n");//A=A-1
	printf("M=D\n");//M=D
}
void pop_STATIC(char* offset){
	printf("@SP\n");
	printf("AM=M-1\n");
	printf("D=M\n");
	printf("@STATIC_%s.%d\n", file_name, (int)strtoul(offset, NULL, 10));

	printf("M=D\n");
}

/*pop element from stack and save it in THIS register.  AKA save it in R3*/
void pop_POINTER(char* offset){
	int temp = ((int)strtoul(offset, NULL, 10))%2;//evens for THIS, odds for THAT
	printf("@SP\n");
	printf("AM=M-1\n");
	printf("D=M\n");
	printf("@%s\n", (temp)?"THAT": "THIS");
	printf("M=D\n");
}
/*take value inside THIS and put it on stack*/
void push_POINTER(char* offset){
	int temp = ((int)strtoul(offset, NULL, 10))%2;//evens for THIS, odds for THAT
	printf("@%s\n", (temp)?"THAT": "THIS" );
	printf("D=M\n");
	printf("@SP\n");
	printf("AM=M+1\n");
	printf("A=A-1\n");
	printf("M=D\n");
}

/*The different between TEMP and (LCL,ARG,THIS,THAT) is the level of inderaction
 @LCL will give number 1  if you dereference it with M you will get the base address
 of the LCL array.  Dereference it again to get the array value
 i.e.
 @LCL //is like a pointer to a pointer
 *@LCL //gives pointer to array
 (*@LCL)[0] // gives value in array
 
 TEMP is part of RAM so it is NOT a pointer to a pointer.  Think of it as an array
 @TEMP //pointer to first element of array
 @TEMP[0] // get value of array
 */
void push_TEMP(char* offset){
	char * str;
	switch ((int)strtoul(offset, NULL, 10)) {
		case 7: str = TEMP7;
			break;
		case 6: str = TEMP6;
			break;
		case 5: str = TEMP5;
			break;
		case 4: str = TEMP4;
			break;
		case 3: str = TEMP3;
			break;
		case 2: str = TEMP2;
			break;
		case 1: str = TEMP1;
			break;			
		default: str = TEMP0;
			break;
	}
	printf("@%s\n", str   );
	printf("D=M\n");
	printf("@SP\n");
	printf("AM=M+1\n");
	printf("A=A-1\n");
	printf("M=D\n");
	
}
void pop_TEMP(char* offset){
	printf("@SP\n");
	printf("AM=M-1\n");
	printf("D=M\n");
	char * str;
	switch ((int)strtoul(offset, NULL, 10)) {
		case 7: str = TEMP7;
			break;
		case 6: str = TEMP6;
			break;
		case 5: str = TEMP5;
			break;
		case 4: str = TEMP4;
			break;
		case 3: str = TEMP3;
			break;
		case 2: str = TEMP2;
			break;
		case 1: str = TEMP1;
			break;
		default: str = TEMP0;
			break;
	}
	printf("@%s\n", str   );
	printf("M=D\n");
}
/*This will push a number on to the stack*/
void push_CONST(char* num){
	printf("@%d\n", (int)strtoul(num, NULL, 10)); //add constant num to A-reg
	printf("D=A\n");
	printf("@SP\nAM=M+1\n");//address of SP saved in A-reg
	printf("A=A-1\n");
	printf("M=D\n");//put constant num at M[SP]

}

/*This will produce in HACK a "@<label>
 The assembler will interpret this as a label
 assuming that its (<label>) counter part is present.
 
 The assembler will replace the label with the line number
 that the label is located at.
 */
void push_LABEL(char* args){
	printf("@%s\n", args); //add label name to A-reg
	printf("D=A\n");
	printf("@SP\nA=M\n");//address of SP saved in A-reg
	printf("M=D\n");//put constant num at M[SP]
	printf("@SP\nM=M+1\n");
}

void push_LCL(char* offset){
	printf("@LCL\n");
	printf("A=M\n");
	int i; for(i = 0; i < (int)strtoul(offset, NULL, 10); ++i) printf("A=A+1\n");
	printf("D=M\n");
	printf("@SP\n");
	printf("AM=M+1\n");//AM=M+1
	printf("A=A-1\n");//A=A-1
	printf("M=D\n");

}
void push_ARG(char* offset){
	printf("@ARG\n");
	printf("A=M\n");
	int i; for(i = 0; i < (int)strtoul(offset, NULL, 10); ++i) printf("A=A+1\n");
	printf("D=M\n");
	printf("@SP\n");
	printf("AM=M+1\n");//AM=M+1
	printf("A=A-1\n");//A=A-1
	printf("M=D\n");

}
void push_THIS(char* offset){
	printf("@THIS\n");
	printf("A=M\n");
	int i; for(i = 0; i < (int)strtoul(offset, NULL, 10); ++i) printf("A=A+1\n");
	printf("D=M\n");
	printf("@SP\n");
	printf("AM=M+1\n");//AM=M+1
	printf("A=A-1\n");//A=A-1
	printf("M=D\n");

}
void push_THAT(char* offset){
	printf("@THAT\n");
	printf("A=M\n");
	int i; for(i = 0; i < (int)strtoul(offset, NULL, 10); ++i) printf("A=A+1\n");
	printf("D=M\n");
	printf("@SP\n");
	printf("AM=M+1\n");//AM=M+1
	printf("A=A-1\n");//A=A-1
	printf("M=D\n");
}

void pop_LCL(char* offset){
	printf("@SP\n");
	printf("AM=M-1\n");
	printf("D=M\n");
	printf("@LCL\n");
	printf("A=M\n");
	int i; for(i = 0; i < (int)strtoul(offset, NULL, 10); ++i) printf("A=A+1\n");
	printf("M=D\n");
}

void pop_ARG(char* offset){
	printf("@SP\n");
	printf("AM=M-1\n");
	printf("D=M\n");
	printf("@ARG\n");
	printf("A=M\n");
	int i; for(i = 0; i < (int)strtoul(offset, NULL, 10); ++i) printf("A=A+1\n");
	printf("M=D\n");
}

void pop_THIS(char* offset){
	printf("@SP\n");
	printf("AM=M-1\n");
	printf("D=M\n");
	printf("@THIS\n");
	printf("A=M\n");
	int i; for(i = 0; i < (int)strtoul(offset, NULL, 10); ++i) printf("A=A+1\n");
	printf("M=D\n");
}

void pop_THAT(char* offset){
	printf("@SP\n");
	printf("AM=M-1\n");
	printf("D=M\n");
	printf("@THAT\n");
	printf("A=M\n");
	int i; for(i = 0; i < (int)strtoul(offset, NULL, 10); ++i) printf("A=A+1\n");
	printf("M=D\n");
}
void not_op(char* i){
	printf("@SP\n");
	printf("A=M-1\n");
	printf("M=!M\n");
}
void neg_op(char* i){
	printf("@SP\n");
	printf("A=M-1\n");
	printf("M=-M\n");
}
void define_and(){
	//title
	printf("(%s)\n", SYS_and);
	// save ret addr
	Sys_fn_save_val_to_reg(call_ret_addr, "D");
	
	//marrow
	printf("@SP\n");
	printf("AM=M-1\n");
	printf("D=M\n");
	printf("A=A-1\n");
	printf("M=M&D\n");
	//jump back
	Sys_fn_get_val_from_reg(call_ret_addr, "A");
	printf("0;JMP\n");

}
void and_op(char* i){
	static int line_num = 0;
	char temp[1024];
	sprintf(temp, "%s$%s_%d",  file_name, SYS_and,line_num++);
	printf("@%s\n",temp);//make ret addr
	printf("D=A\n");//save ret addr to d
	printf("@%s\n", SYS_and);//jump to op
	printf("0;JMP\n");
	printf("(%s)\n", temp);//label of ret_addr
}
void define_or(){
	//title
	printf("(%s)\n", SYS_or);
	// save ret addr
	Sys_fn_save_val_to_reg(call_ret_addr, "D");
	
	//marrow
	printf("@SP\n");
	printf("AM=M-1\n");
	printf("D=M\n");
	printf("A=A-1\n");
	printf("M=M|D\n");

	//jump back
	Sys_fn_get_val_from_reg(call_ret_addr, "A");
	printf("0;JMP\n");

}
void or_op(char* i){
	static int line_num = 0;
	char temp[1024];
	sprintf(temp, "%s$%s_%d",  file_name, SYS_or,line_num++);
	printf("@%s\n",temp);//make ret addr
	printf("D=A\n");//save ret addr to d
	printf("@%s\n", SYS_or);//jump to op
	printf("0;JMP\n");
	printf("(%s)\n", temp);//label of ret_addr
}
void define_add(){
	//title
	printf("(%s)\n", SYS_add);
	// save ret addr
	Sys_fn_save_val_to_reg(call_ret_addr, "D");
	
	//marrow
	printf("@SP\n");
	printf("AM=M-1\n");
	printf("D=M\n");
	printf("A=A-1\n");
	printf("M=M+D\n");
	//jump back
	Sys_fn_get_val_from_reg(call_ret_addr, "A");
	printf("0;JMP\n");
}
void add_op(char* i){
	static int line_num = 0;
	char temp[1024];
	sprintf(temp, "%s$%s_%d",  file_name, SYS_add,line_num++);
	printf("@%s\n",temp);//make ret addr
	printf("D=A\n");//save ret addr to d
	printf("@%s\n", SYS_add);//jump to op
	printf("0;JMP\n");
	printf("(%s)\n", temp);//label of ret_addr
}
void define_sub(){
	//title
	printf("(%s)\n", SYS_SUB);
	// save ret addr
	Sys_fn_save_val_to_reg(call_ret_addr, "D");
	
	//marrow
	printf("@SP\n");
	printf("AM=M-1\n");
	printf("D=M\n");
	printf("A=A-1\n");
	printf("M=M-D\n");
	
	//jump back
	Sys_fn_get_val_from_reg(call_ret_addr, "A");
	printf("0;JMP\n");
}
void sub_op(char* i){
	static int line_num = 0;
	char temp[1024];
	sprintf(temp, "%s$%s_%d",  file_name, SYS_SUB,line_num++);
	printf("@%s\n",temp);//make ret addr
	printf("D=A\n");//save ret addr to d
	printf("@%s\n", SYS_SUB);//jump to op
	printf("0;JMP\n");
	printf("(%s)\n", temp);//label of ret_addr
}
void eq_op(char* i){
//	char temp [1024];
//	sprintf(temp , "%s %d",SYS_EQUAL,2);
//	call_f_n(temp );

	static int line_num = 0;
	char temp [1024];
	sprintf(temp, "%s$%s_%d", file_name ,SYS_LTGTEQ_EQ, line_num++);
	printf("@%s\n", temp);
	printf("D=A\n");
	printf("@%s\n", TEMP0);
	printf("M=%d\n", 0);
	printf("@%s\n", SYS_LTGTEQ);
	printf("0;JMP\n");
	printf("(%s)\n", temp);
}
void gt_op(char* i){
//	char temp [1024];
//	sprintf(temp , "%s %d",SYS_GREATER_THAN,2);
//	call_f_n(temp );
	
	static int line_num = 0;
	char temp [1024];
	sprintf(temp, "%s$%s_%d", file_name ,SYS_LTGTEQ_GT, line_num++);
	printf("@%s\n", temp);
	printf("D=A\n");
	printf("@%s\n", TEMP0);
	printf("M=%d\n", 1);
	printf("@%s\n", SYS_LTGTEQ);
	printf("0;JMP\n");
	printf("(%s)\n", temp);
}
void lt_op(char* i){
//	char temp [1024];
//	sprintf(temp , "%s %d",SYS_LESS_THAN,2);
//	call_f_n(temp );
	static int line_num = 0;
	char temp [1024];
	sprintf(temp, "%s$%s_%d", file_name ,SYS_LTGTEQ_LT, line_num++);
	printf("@%s\n", temp);
	printf("D=A\n");
	printf("@%s\n", TEMP0);
	printf("M=%d\n", -1);
	printf("@%s\n", SYS_LTGTEQ);
	printf("0;JMP\n");
	printf("(%s)\n", temp);
}

//use this for the System functions.
//system functions are stack pop and push operations
// and all so basic alu operations like add, or, etc
void Sys_fn_save_val_to_reg(char* reg, char* value) //use to save ret val
{
	printf("@%s\n", reg);
	printf("M=%s\n", value);
}
void Sys_fn_get_val_from_reg(char* reg, char* val) //use to retrieve ret val
{
	printf("@%s\n", reg);
	printf("%s=M\n", val);
}
//a function that calls all the other system functions.
void define_sys_fn(){
	//system functions
	define_sub();//you should use register, call_ret_addr or R13
	define_add();
	define_or();
	define_and();
}
