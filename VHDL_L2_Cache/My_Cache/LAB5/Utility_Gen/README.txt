The programs will generate a mux and decoder vhdl code. The make file will 
compile and run the program.

Makefile commands

make mux
Will compile mux_gen.cpp, create an executable called mux, and run it.
The program will ask for the num inputs to the mux.

make decoder
Will compile decoder_gen.cpp, create an executable called decoder, and run it.
The program will ask for the bit width of the signal input to the decoder.

make clean
Will delete every file except the Makefile, decoder_gen.cpp and mux_gen.