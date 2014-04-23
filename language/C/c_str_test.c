#include <stdio.h>
#include <string.h>

void main()
{
  char str1[3] = "3 \0";
  char str2[3] = "3\0";

  int i = strcmp(str1,str2);
  printf("%d\n",i);

  char buf[20];
  strcpy(buf, "xcui");
  strcat(buf,".");

  printf("%s\n",buf);
}

