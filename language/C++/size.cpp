#include <iostream>
using namespace std;

struct test{
  int i;
  int j;
  int k;
};

int main()
{
  test arr[10];
  int size = &arr[8] - &arr[3];

  return 0;
}
