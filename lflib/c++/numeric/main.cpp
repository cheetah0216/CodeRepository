#include <limits.h>
#include <stdio.h>

#define MAX_NUMERIC_PIECE (1<<30)
#define MAX_NUMERIC_PIECE1 (1<<31)

int main()
{
  const int min_int = INT_MIN;
  const int max_int = INT_MAX;
  printf("%d\n%d\n", min_int, max_int);
    
  int temp1 = -128;
  int temp2 = 64;
  int result = temp1%temp2;
  printf("%d\n",result);

  double max = MAX_NUMERIC_PIECE * (double)MAX_NUMERIC_PIECE - 1.0;
  double max1 = MAX_NUMERIC_PIECE1 * (double)MAX_NUMERIC_PIECE1 - 1.0;

  printf("%d\n", sizeof(double));
  printf("%f\n", max);
  printf("%f\n", max1);
  return 0;
}
