#include<iostream>
using namespace std;

class A
{
};

class B:public A
{
public:
    void fun(B&obj)
    {
        A obj1 = (A)obj;
    }
};

class C:protected A
{
public:
    void fun(C&obj)
    {
        A obj1 = (A)obj;
    }
};

class D:private A
{
public:
    void fun(D&obj)
    {
        A obj1 = (A)obj;
    }
};

class E:public B
{
public:
    void fun(B&obj)
    {
        A obj1 = (A)obj;
    }
    void fun(E&obj)
    {
        A obj1 = (A)obj;
    }
};

class F:public C
{
    public:
    void fun(C&obj)
    {
        A obj1 = (A)obj;
    }
    void fun(F&obj)
    {
        A obj1 = (A)obj;
    }
};

//从private继承类派生的类不能转换为基类。
class H:public D
{
public:
    void fun(D&obj)
    {
        A obj1 = (A)obj; //‘A’是‘D’不可访问的基类 
    }
    void fun(H&obj)
    {
        A obj1 = (A)obj; //‘A’是‘H’不可访问的基类
    }
};

int main()
{
    A *pb, *pc, *pe, *pd, *pf, *ph;
     
    pb = new B; //public 
    pc = new C; //protected                ‘A’是‘C’不可访问的基类 
    pd = new D; //private                  ‘A’是‘D’不可访问的基类
    pe = new E; //public + public          
    pf = new F; //protected + public       ‘A’是‘F’不可访问的基类
    ph = new H; //private + public         ‘A’是‘H’不可访问的基类

    return 0;
}
