#include <iostream>
#include <fstream>
#include <bitset>

using namespace std;

unsigned long long pow_2(unsigned long long num){
 return 1ull << num;
}

string binary( unsigned int n, unsigned int length ) {
  string result("");
  
  while(n >= 1){
    if(n%2==1) result = "1" + result; 
    else result = "0" + result;
    n /= 2;
  }
  
   while(result.size() < length )
      result = "0" + result;
  
  return result;
}

string binary_string(unsigned long long size){
  string bitstring("");
  
  for(unsigned int i = 1; i < size; i++ ) 
    bitstring = "0" + bitstring;
  
  bitstring = bitstring + "1";

  return bitstring;
}

string binary_string_lshift(string bitstring){
  bitstring = bitstring.substr(1);
  return  bitstring + "0";
}


int main(){

  string decwidth;
  string fname;
  unsigned long long decw;
  ofstream outfile;
  unsigned long long dec_out;
  string bitstring;
  string sel;

  cout << "Enter the input width of the decoder: ";
  cin >> decwidth;
  cout << endl;

  decw = atoi(decwidth.c_str());
  fname = "decoder_"+decwidth+".vhd"; 
  dec_out = pow_2(decw);

  bitstring = binary_string(pow_2(decw));
  sel = binary_string(decw);

  outfile.open(fname.c_str());

  if(!outfile){
    cerr << "File was not created correctly";
    exit(-1);
  }
  
  outfile << "library IEEE;" << endl << "use IEEE.std_logic_1164.all;" 
	  << endl << endl
	  << "entity decoder" << decw << " is" << endl 
	  << "port(" << endl
	  << '\t' << "Sel : in std_logic_vector( " << decw - 1 
	  << " downto 0 );"
	  << endl << '\t' << "y : out std_logic_vector( " << pow_2(decw) - 1
	  << " downto 0 )" << endl << '\t' << ");" << endl 
	  << "end entity decoder" << decw <<";" << endl << endl;
  
  outfile << "architecture bhv of decoder" << decw << " is" << endl
	  << "begin" << endl
	  << "y <= ";

  for(unsigned int i = 0; i < dec_out+1; i++ ){
    outfile << "\"" << bitstring;


    if(i+1 == dec_out ){
      outfile << "\";";
      break;
    }
    else{
      outfile << "\" when Sel = \"" << binary(i,decw) 
	    << "\" else" << endl << "     ";
    }
  
    bitstring = binary_string_lshift(bitstring);
  }

  outfile << endl << "end architecture bhv;";

  outfile.close();

  return 0;
}
