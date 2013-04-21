// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input. 
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel. When no key is pressed, the
// program clears the screen, i.e. writes "white" in every pixel.

// Put your code here.

(init)
	@offset_v 
		M = 0					// *offset_v = 0
	@KBD 
		D = A-1				// D = KBD -1
	@endscreen_v 
		M = D					// *endscreen_v = D
	//@32767 
	//	D = -1					// set D to imediate value 32767
	@FILL_v 
		M = -1
		//M = D					// *FILL_v = 32767
	@cur_screen_v 
		M = 0					// *cur_screen_v = 0
(get_screen)
	@SCREEN
(add_offset)
		D = A					// D = SCREEN
	@offset_v 
		A = D + M			// A = SCREEN + *offset_v
		D = A
	@cur_screen_v 
		M = D					// *cur_screen_v = D
(set_data)
	
	@KBD
		D = M
		@NOTFILL
		D; JEQ
	@FILL_v 
		D = M					//D = *FILL_v
		@set_data_2
		0;JMP
	(NOTFILL)
		D = 0
	(set_data_2)
	@cur_screen_v			//address inside go to -> A
		A = M					//
		M = D					//*(Screen+offset) = fillnum
(within_range)
	@endscreen_v
		D = M					//D = *endscreen_v
	@cur_screen_v
		D = D - M			//D = *endscreen_v -*cur_screen_v
	@init
		D;JEQ
	@offset_v 
		M = M + 1
	@get_screen 
		0;JMP
(end)
@end
0;JMP