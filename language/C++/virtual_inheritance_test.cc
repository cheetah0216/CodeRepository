#include <iostream>
using namespace std;

class Animal {
  public:
    virtual void eat() { cout << "Animal::eat()" << endl; };
};

class Mammal: public  Animal {
  public:
    virtual void breathe() { cout << "Mammal::breathe()" << endl; };
};

class WingedAnimal: public virtual Animal {
  public:
    virtual void flap() { cout << "WingedAnimal::flap()" <<endl; };
};
 
class Bat: public Mammal, public WingedAnimal {
};

int main() {
    Bat b;
    b.breathe();
    b.flap();
    b.eat();
    Animal &a = b;
}
