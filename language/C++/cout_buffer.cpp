#include <iostream>
#include <cstdio>
using namespace std;

void cout_buffer_test()
{
  //expected output: 123454950515253
  //actual output: 149250351452553
  //cout行缓冲具体看编译器怎么实现
  int num;
  while( (num=getchar()) != '\n' )
  {
    putchar(num);
    cout << num;
  }
}

int main()
{
  cout_buffer_test();
  return 0;
}
