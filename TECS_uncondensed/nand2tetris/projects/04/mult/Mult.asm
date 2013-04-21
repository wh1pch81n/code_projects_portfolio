// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[3], respectively.)

// Put your code here.

(begin)
@2 //r2
M = 0; //sum = 0;
@0 //param x
D = M // Mem[r0] -> D
@3 // var "shiftedX"
M = D // save to variable "shiftedX"
@4 //var j
M = 1
(m_loop)
	//@4 //get var j
	//D = M
	//@16
	//D = D-A// D = j - 16
	@4
	D = M
	@end_m_loop
	D;JEQ // if j = 0 then jump to end_m_loop
	(start_if)
		@1 //arg y
		D = M
		@4
		D = D&M
		@end_if
		D;JEQ // if y&j = 0 then jump to end_if
		@2 // var sum
		D = M // put sum inside D
		@3 // M gets shifted_x
		D = D+M//sum = sum + shifted_x
		@2 
		M = D //save results into var sum
	(end_if)
	@3
	D = M 
	D = D + M // shiftedx += shiftedx
	M = D//save results into shiftedx
	@4 
	D = M
	M = D+ M // j <<= 1
	@m_loop
	0;JMP
(end_m_loop)

//terminate prog
(end)
@end
0;JMP










