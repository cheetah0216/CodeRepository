#include <iostream>
using namespace std;

class Animal {
  public:
    Animal() { cout << "Animal()" << endl;}

    virtual void eat() { cout << "Animal::eat()" << endl; };
};

class Mammal: public virtual Animal {
  public:
    Mammal() { cout << "Mammal()" << endl;}

    virtual void breathe() { cout << "Mammal::breathe()" << endl; };
};

class WingedAnimal: public virtual Animal {
  public:
    WingedAnimal() { cout << "WingedAnimal" <<endl;}

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
