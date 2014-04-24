#include <iostream>

class A{
  public:
    A() { std::cout << "1"; }
    ~A() { std::cout << "2"; }
    void Print() { std::cout << "3"; }
};

class B:public A{
  public:
    B() { std::cout << "4"; }
    virtual ~B() { std::cout << "5"; }
    virtual void Print() { std::cout << "6"; }
};

class C:public B{
  public:
    C() { std::cout << "7"; }
    virtual ~C() { std::cout << "8"; }
    virtual void Print() { std::cout << "9"; }
};

int main()
{
  A* a = new B();
  a->Print();
  B* b = new C();
  b->Print();
  delete b;
  delete a;

  return 0;
}
