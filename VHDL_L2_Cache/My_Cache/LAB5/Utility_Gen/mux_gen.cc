#include <iostream>
#include <fstream>

using namespace std;

int bitvectorsize(int size){
  int numbits(0);
  while(size != 1){ size /= 2; numbits++;}
  return numbits;
}

string binary( unsigned long n, int length )
{
  char     result[ (sizeof( unsigned long ) * 8) + 1 ];
  unsigned index  = sizeof( unsigned long ) * 8;
  result[ index ] = '\0';

  do result[ --index ] = '0' + (n & 1);
  while (n >>= 1);
  
  string pad = result + index;

  while(pad.size()< length )
    pad = "0" + pad;

  return pad;
}

int main() {

  string muxsize;
  string fname;
  int muxt;
  ofstream outfile; 
  
  cout << "Enter the size of the mux: ";
  cin >> muxsize; 
  cout << endl;
  
  muxt = atoi(muxsize.c_str()); 
  fname = "mux_"+muxsize+"_1.vhd";
  
  outfile.open(fname.c_str());
  
  if(!outfile){
    cerr << "File was not created correctly";
    exit(-1);
  }

  outfile << "library IEEE;" << endl << "use IEEE.std_logic_1164.all;" 
	  << endl << endl
	  << "entity mux" << muxsize << "v1 is" << endl
	  << "port(" << endl;

  for( unsigned int i = 0; i < muxt; i++ )
    outfile << '\t' << "d" << i << ": in std_logic;" << endl;
  
  outfile << '\t' << "y : out std_logic;" << endl << '\t' 
	  << "s : in std_logic_vector( " << bitvectorsize(muxt) - 1
	  << " downto 0 )" << endl << ");" 
	  << endl << "end mux" << muxsize << "v1;" << endl << endl; 

  outfile << "architecture bhv of mux" << muxsize << "v1 is" << endl
	  << "begin" << endl << endl;

  outfile << "with s select" << endl << endl
	  << "y <=    ";
  
  int bitsize = bitvectorsize(muxt);

  for( unsigned int i = 0; i < muxt; i++ ){
    outfile << "d" << i << " when " << "\""
	    << binary(i,bitsize) << "\"," << endl << '\t';
  }

  outfile << "'0' when others;" << endl << endl
	  << "end bhv;";

  outfile.close();

  return 0;
}
