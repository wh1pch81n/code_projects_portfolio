/*
name: Derrick Ho
email: dho006@ucr.edu
project description: two functions that can reverse strings
*/
#include <stdio.h>
#include <string.h>
void string_reverse1(char *string) 
{ 
  int left = 0;
  int right = strlen(string) -1;
  for( ; left < right; ++left, --right){
    string[left] ^= string[right];
    string[right] ^= string[left];
    string[left] ^= string[right];
  }
}


char *string_reverse2(const char *string)
{
  char * d_arr = strdup( string);
  string_reverse1( d_arr);
  return d_arr;
}

int main(int argc, char ** argv){
  char str[]= "hello world";
  printf("%s\n",str);
  string_reverse1(str);
  printf("%s\n", str);
  char str2[] = "derrick";
  printf("%s\n", str2);
  char * str3 = string_reverse2(str2);
  printf("%s\n", str3);
  free(str3);
  printf("done\n");
  return 0;
}
