@256
D=A
@SP
M=D
@_Sys.init_0
D=A
@R13
M=D
@Sys.init
D=A
@R15
M=D
@0
D=A
@SysCall.init
0;JMP
(_Sys.init_0)
(SysCall.init)
@R14
M=D
@R13
D=M
@SP
A=M
M=D
@SP
M=M+1
@LCL
D=M
@SP
A=M
M=D
@SP
M=M+1
@ARG
D=M
@SP
A=M
M=D
@SP
M=M+1
@THIS
D=M
@SP
A=M
M=D
@SP
M=M+1
@THAT
D=M
@SP
A=M
M=D
@SP
M=M+1
@SP
D=M
@R14
D=D-M
@5
D=D-A
@ARG
M=D
@SP
D=M
@LCL
M=D
@R15
A=M
0;JMP
(SysReturn.init)
@LCL
D=M
@R5
M=D
A=D-A
D=M
@R5
M=D
@SP
AM=M-1
D=M
@ARG
A=M
M=D
@ARG
D=M+1
@SP
M=D
@LCL
AM=M-1
D=M
@THAT
M=D
@LCL
AM=M-1
D=M
@THIS
M=D
@LCL
AM=M-1
D=M
@ARG
M=D
@LCL
AM=M-1
D=M
@LCL
M=D
@R5
A=M
0;JMP
(SysLtGtEq.init)
@R6
M=D
@R7
M=-1
@SP
AM=M-1
D=M
A=A-1
D=M-D
@R8
M=D
@R5
D=M
@SysLtGtEq.LT
D;JLT
@SysLtGtEq.GT
D;JGT
(SysLtGtEq.EQ)
@R8
D=M
@SysLtGtEq.EQ_isTrue
D;JEQ
@R7
M=0
(SysLtGtEq.EQ_isTrue)
@SysLtGtEq.RET
0;JMP
(SysLtGtEq.LT)
@R8
D=M
@SysLtGtEq.LT_isTrue
D;JLT
@R7
M=0
(SysLtGtEq.LT_isTrue)
@SysLtGtEq.RET
0;JMP
(SysLtGtEq.GT)
@R8
D=M
@SysLtGtEq.GT_isTrue
D;JGT
@R7
M=0
(SysLtGtEq.GT_isTrue)
@SysLtGtEq.RET
0;JMP
(SysLtGtEq.RET)
@R7
D=M
@SP
A=M-1
M=D
@R6
A=M
0;JMP
(Main.fibonacci)
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
@2
D=A
@SP
A=M
M=D
@SP
M=M+1
@Main$SysLtGtEq.LT_0
D=A
@R5
M=-1
@SysLtGtEq.init
0;JMP
(Main$SysLtGtEq.LT_0)
@SP
AM=M-1
D=M
@Main.fibonacci$IF_TRUE
D;JNE
@Main.fibonacci$IF_FALSE
0;JMP
(Main.fibonacci$IF_TRUE)
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
@SysReturn.init
0;JMP
(Main.fibonacci$IF_FALSE)
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
@2
D=A
@SP
A=M
M=D
@SP
M=M+1
@SP
A=M-1
D=M
A=A-1
M=M-D
@SP
M=M-1
@Main_Main.fibonacci_1
D=A
@R13
M=D
@Main.fibonacci
D=A
@R15
M=D
@1
D=A
@SysCall.init
0;JMP
(Main_Main.fibonacci_1)
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
@1
D=A
@SP
A=M
M=D
@SP
M=M+1
@SP
A=M-1
D=M
A=A-1
M=M-D
@SP
M=M-1
@Main_Main.fibonacci_2
D=A
@R13
M=D
@Main.fibonacci
D=A
@R15
M=D
@1
D=A
@SysCall.init
0;JMP
(Main_Main.fibonacci_2)
@SP
A=M-1
D=M
A=A-1
M=M+D
@SP
M=M-1
@SysReturn.init
0;JMP
(Sys.init)
@4
D=A
@SP
A=M
M=D
@SP
M=M+1
@Sys_Main.fibonacci_0
D=A
@R13
M=D
@Main.fibonacci
D=A
@R15
M=D
@1
D=A
@SysCall.init
0;JMP
(Sys_Main.fibonacci_0)
(Sys.init$WHILE)
@Sys.init$WHILE
0;JMP
