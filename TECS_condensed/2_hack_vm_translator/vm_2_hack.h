//
//  vm_2_hack.h
//  vm_2_hack
//
//  Created by Derrick Ho on 12/18/12.
//  Copyright (c) 2012 Derrick Ho. All rights reserved.
//

#ifndef vm_2_hack_vm_2_hack_h
#define vm_2_hack_vm_2_hack_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#define CONSTANT 0
#define HACK_FALSE 0
#define HACK_TRUE -1
#define call_ret_addr "R13"
#define call_num_arg "R14"
#define call_fn_line "R15"
#define TEMP_reg "R5"
#define TEMP_reg1 "R6"
#define TEMP0 "R5"
#define TEMP1 "R6"
#define TEMP2 "R7"
#define TEMP3 "R8"
#define TEMP4 "R9"
#define TEMP5 "R10"
#define TEMP6 "R11"
#define TEMP7 "R12"
#define STATIC_reg "R16"
#define SYS_CALL "SysCall.init"
#define SYS_RETURN "SysReturn.init"
#define SYS_LESS_THAN "SysLt.init"
#define SYS_GREATER_THAN "SysGt.init"
#define SYS_EQUAL "SysEq.init"
#define SYS_LTGTEQ "SysLtGtEq.init"
#define SYS_LTGTEQ_LT "SysLtGtEq.LT"
#define SYS_LTGTEQ_GT "SysLtGtEq.GT"
#define SYS_LTGTEQ_EQ "SysLtGtEq.EQ"
#define SYS_LTGTEQ_LT_IS_TRUE "SysLtGtEq.LT_isTrue"
#define SYS_LTGTEQ_GT_IS_TRUE "SysLtGtEq.GT_isTrue"
#define SYS_LTGTEQ_EQ_IS_TRUE "SysLtGtEq.EQ_isTrue"
#define SYS_LTGTEQ_RET "SysLtGtEq.RET"
#define SYS_INIT "Sys.init"
//
#define SYS_SUB "Sys.Sub"
#define SYS_add "Sys.Add"
#define SYS_or "Sys.Or"
#define SYS_and "Sys.And"
#define SYS_popThat "Sys.popThat"
#define SYS_popThis "Sys.popThis"
#define SYS_popArg "Sys.popArg"
#define SYS_popLcl "Sys.popLcl"
#define SYS_pushThat "Sys.pushThat"
#define SYS_pushThis "Sys.pushThis"
#define SYS_pushArg "Sys.pushArg"
#define SYS_pushLcl "Sys.pushLcl"
#define SYS_pushConst "Sys.pushConst"
#define SYS_popTemp "Sys.popTemp"
#define SYS_pushTemp "Sys.pushTemp"
#define SYS_pushPtr "Sys.pushPtr"
#define SYS_popPtr "Sys.popPtr"
#define SYS_popStatic "Sys.popStatic"
#define SYS_pushStatic "Sys.pushStatic"
#define SYS_if_goto "Sys.if_goto"

///
int line_cnt;//global thing

void not_op(char*);
void neg_op(char*);
void and_op(char*);
void or_op(char*);
void add_op(char*);
void sub_op(char*);
void eq_op(char*);
void gt_op(char*);
void lt_op(char*);

void push_CONST(char* num);
void push_LCL(char* offset);
void push_ARG(char* offset);
void push_THIS(char* offset);
void push_THAT(char* offset);
void pop_LCL(char* offset);
void pop_ARG(char* offset);
void pop_THIS(char* offset);
void pop_THAT(char* offset);

void push_TEMP(char* offset);
void pop_TEMP(char* offset);
void pop_POINTER(char* offset);
void push_POINTER(char* offset);
void push_STATIC(char* offset);
void pop_STATIC(char* offset);
void add_label(char* args);
void if_goto(char* args);
void do_goto(char* args);
void call_f_n(char* args);
void function_f_k(char* args);
void return_f(char* args);
void push_LABEL(char*args);
void add_bootstrap();
void define_sys_call();
void define_sys_return();
void define_sys_less_than();//deprecated
void define_sys_greater_than();//deprecated
void define_sys_equal();//deprecated 
void define_sys_LTGTEQ();

//system functions
void define_sub();//you should use register, call_ret_addr or R13 
void define_add();
void define_or();
void define_and();

void Sys_fn_save_val_to_reg(char* reg, char* value) ;
void Sys_fn_get_val_from_reg(char* reg, char* val);
void define_sys_fn();
#endif
