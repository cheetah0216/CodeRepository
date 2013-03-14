#include "B.hpp"
#include "stdio.h"

class A {
	public:
		A(int sz){sz_=sz;v=new B[sz_];}
		A(){v=NULL;sz_=0;}
		~A() {delete[] v;}

		virtual void Show() {printf("I have %d B.", sz_);}

	private:
		B *v;
		int sz_;
};

class C: public A{
	public:
		C(int num):A(){num_=num;}
		~C(){}
		void Show() {printf("I'm C, so I don't have B.");}
	private:
		int num_;
};
