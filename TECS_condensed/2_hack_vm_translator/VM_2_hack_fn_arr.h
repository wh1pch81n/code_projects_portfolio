//
//  VM_2_hack_fn_arr.h
//  vm_2_hack
//
//  Created by Derrick Ho on 12/18/12.
//  Copyright (c) 2012 Derrick Ho. All rights reserved.
//

#ifndef vm_2_hack_VM_2_hack_fn_arr_h
#define vm_2_hack_VM_2_hack_fn_arr_h

typedef struct {
	char * syntax;
	//enum fn_names fn_name;
	void(*fn_ptr)(char*);
}response;


response r[] = {
	{"not", not_op},	{"neg", neg_op},	{"and", and_op},	{"or", or_op},
	{"add", add_op},	{"sub", sub_op},	{"eq", eq_op},	{"gt", gt_op},	{"lt",  lt_op},
	{"push constant", push_CONST},	{"push local",  push_LCL},
	{"push argument", push_ARG },	{"push this",  push_THIS},
	{"push that", push_THAT},	{"pop local", pop_LCL},
	{"pop argument", pop_ARG},	{"pop this", pop_THIS  },
	{"pop that", pop_THAT },	{"push temp", push_TEMP },
	{"pop temp", pop_TEMP},	{"pop pointer", pop_POINTER},
	{"push pointer", push_POINTER},	{"push static", push_STATIC},
	{"pop static", pop_STATIC}, {"label", add_label}, {"if-goto", if_goto},
	{"goto",do_goto }, {"call", call_f_n}, {"function", function_f_k}, {"return",return_f}
};


#endif
