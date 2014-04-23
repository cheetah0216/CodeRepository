#include <iostream>
using namespace std;

void PrintState()
{
  cout << cin.rdstate() << endl;
}

void StateValues()
{
  cout << "goodbit: " << ios::goodbit << endl;
  cout << "badbit: " << ios::badbit << endl;
  cout << "eofbit: " << ios::eofbit << endl;
  cout << "failbit: " << ios::failbit << endl;
}

void SetBit(ios::iostate state)
{
  cin.setstate(state);
  PrintState();
}

void ClearBit(ios::iostate state)
{
  cin.clear(state);
  PrintState();
}

int main()
{
  cout << "********* staus values: " << endl;
  StateValues();

  cout << "******** clear status: " << endl;
  cout << "clear():Set error state flags" << endl;
  cout << "clear goodbit: ";
  ClearBit(ios::goodbit);
  cout << "clear badbit: ";
  ClearBit(ios::badbit);
  cout << "clear eofbit: ";
  ClearBit(ios::eofbit);
  cout << "clear failbit: ";
  ClearBit(ios::failbit);
  cout << "clear eofbit | badbit: ";
  ClearBit(ios::eofbit | ios::failbit);
  cout << "clear badbit | eofbit | failbit: ";
  ClearBit(ios::badbit | ios::eofbit | ios::failbit);

  cout << "********* set status: " << endl;
  cout << "setstate(): clear(rdstate()|state);" << endl;
  cin.clear();
  cout << "set goodbit: ";
  SetBit(ios::goodbit);
  cout << "set badbit: ";
  SetBit(ios::badbit);
  cout << "set eofbit: ";
  SetBit(ios::eofbit);
  cout << "set failbit: ";
  SetBit(ios::failbit);
  cout << "set badbit | eofbit | failbit: ";
  SetBit(ios::badbit | ios::eofbit | ios::failbit);

  return 0;
}
