#include <stdio.h>
#include <math.h>
//#define MAX_N 50//000

int main( int argc, char** argv){
  if(argc != 2){
    printf("[./a.out] [max_n]");
	   return -1;
  }
  long int MAX_N = strtoul(argv[1], NULL, 10);
  long int x,y,z;
  for( x = 0; x < MAX_N; ++x){
    for( y = 0; y < MAX_N; ++y){
      z = x*x + y*y;
      printf("%ld = %ld^2 + %ld^2\n", z, x, y);
    }
  }
  
  printf("\n\ndone\n");
  return 0;
}
