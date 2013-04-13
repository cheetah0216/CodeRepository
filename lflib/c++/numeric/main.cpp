#include <limits.h>
#include <stdio.h>

int main()
{
  const int min_int = INT_MIN;
  const int max_int = INT_MAX;
  printf("%d\n%d\n", min_int, max_int);
    
  int temp1 = -128;
  int temp2 = 64;
  int result = temp1%temp2;
  printf("%d\n",result);

  return 0;
}
