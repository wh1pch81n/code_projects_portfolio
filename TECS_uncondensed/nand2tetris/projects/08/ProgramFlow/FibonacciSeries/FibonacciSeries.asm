@ARG
D=M
@1
A=D+A
D=M
@SP
A=M
M=D
@SP
M=M+1
@22222//end_push argument( 1)
@SP
AM=M-1
D=M
@THIS
A=A+1
M=D
@22222//end_pop pointer( 1           // that = argument[1])
@0
D=A
@SP
A=M
M=D
@SP
M=M+1
@22222//end_push constant( 0)
@SP
AM=M-1
D=M
@THAT
A=M
M=D
@22222//end_pop that( 0              // first element = 0)
@1
D=A
@SP
A=M
M=D
@SP
M=M+1
@22222//end_push constant( 1)
@SP
AM=M-1
D=M
@THAT
A=M
A=A+1
M=D
@22222//end_pop that( 1              // second element = 1)
@ARG
D=M
@0
A=D+A
D=M
@SP
A=M
M=D
@SP
M=M+1
@22222//end_push argument( 0)
@2
D=A
@SP
A=M
M=D
@SP
M=M+1
@22222//end_push constant( 2)
@SP
A=M-1
D=M
A=A-1
M=M-D
@SP
M=M-1
@22222//end_sub()
@SP
AM=M-1
D=M
@ARG
A=M
M=D
@22222//end_pop argument( 0          // num_of_elements -= 2 (first 2 elements are set))
(MAIN_LOOP_START)
@22222//end_label( MAIN_LOOP_START)
@ARG
D=M
@0
A=D+A
D=M
@SP
A=M
M=D
@SP
M=M+1
@22222//end_push argument( 0)
@SP
AM=M-1
D=M
@COMPUTE_ELEMENT // if num_of_elements > 0, goto COMPUTE_ELEMENT
D;JGT
@22222//end_if-goto( COMPUTE_ELEMENT // if num_of_elements > 0, goto COMPUTE_ELEMENT)
@END_PROGRAM        // otherwise, goto END_PROGRAM
0;JMP
@22222//end_goto( END_PROGRAM        // otherwise, goto END_PROGRAM)
(COMPUTE_ELEMENT)
@22222//end_label( COMPUTE_ELEMENT)
@THAT
D=M
@0
A=D+A
D=M
@SP
A=M
M=D
@SP
M=M+1
@22222//end_push that( 0)
@THAT
D=M
@1
A=D+A
D=M
@SP
A=M
M=D
@SP
M=M+1
@22222//end_push that( 1)
@SP
A=M-1
D=M
A=A-1
M=M+D
@SP
M=M-1
@22222//end_add()
@SP
AM=M-1
D=M
@THAT
A=M
A=A+1
A=A+1
M=D
@22222//end_pop that( 2              // that[2] = that[0] + that[1])
@THIS
D=A
@1
A=D+A
D=M
@SP
A=M
M=D
@SP
M=M+1
@22222//end_push pointer( 1)
@1
D=A
@SP
A=M
M=D
@SP
M=M+1
@22222//end_push constant( 1)
@SP
A=M-1
D=M
A=A-1
M=M+D
@SP
M=M-1
@22222//end_add()
@SP
AM=M-1
D=M
@THIS
A=A+1
M=D
@22222//end_pop pointer( 1           // that += 1)
@ARG
D=M
@0
A=D+A
D=M
@SP
A=M
M=D
@SP
M=M+1
@22222//end_push argument( 0)
@1
D=A
@SP
A=M
M=D
@SP
M=M+1
@22222//end_push constant( 1)
@SP
A=M-1
D=M
A=A-1
M=M-D
@SP
M=M-1
@22222//end_sub()
@SP
AM=M-1
D=M
@ARG
A=M
M=D
@22222//end_pop argument( 0          // num_of_elements--)
@MAIN_LOOP_START
0;JMP
@22222//end_goto( MAIN_LOOP_START)
(END_PROGRAM)
@22222//end_label( END_PROGRAM)
