@0
D=A
@SP
A=M
M=D
@SP
M=M+1
@22222//end_push constant( 0    )
@SP
AM=M-1
D=M
@LCL
A=M
M=D
@22222//end_pop local( 0        // initialize sum = 0)
(LOOP_START)
@22222//end_label( LOOP_START)
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
@22222//end_push argument( 0    )
@LCL
D=M
@0
A=D+A
D=M
@SP
A=M
M=D
@SP
M=M+1
@22222//end_push local( 0)
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
@LCL
A=M
M=D
@22222//end_pop local( 0	   // sum = sum + counter)
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
@22222//end_pop argument( 0     // counter--)
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
@LOOP_START // If counter > 0, goto LOOP_START
D;JGT
@22222//end_if-goto( LOOP_START // If counter > 0, goto LOOP_START)
@LCL
D=M
@0
A=D+A
D=M
@SP
A=M
M=D
@SP
M=M+1
@22222//end_push local( 0)
