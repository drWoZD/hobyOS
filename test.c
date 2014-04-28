#include <stdio.h>
int main()
{
  char* s1=0; 
  char* s2="2";
  void ** s = (void**)&s1;
  if (*s)
    printf("a\n");
  else
    printf("b\n");
}
