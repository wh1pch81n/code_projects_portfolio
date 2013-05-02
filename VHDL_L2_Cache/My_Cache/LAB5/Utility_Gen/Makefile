CXX = g++

all:

mux:
	$(CXX) mux_gen.cc -o mux
	./mux

decoder:
	$(CXX) decoder_gen.cc -o decoder
	./decoder

clean:
	\rm -rf *.vhd *~ mux decoder