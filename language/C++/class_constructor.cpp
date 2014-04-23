#include <iostream>
#include <stdio.h>
using namespace std;

class Book {
  public:
    Book(const string &str = "", double num = 0.0):
      isbn(str),price(num) { cout << "Book::init" << endl; }
    Book(const Book &book):
      isbn(book.isbn),price(book.price) { cout << "Book::copy" << endl; }
    Book& operator=(const Book &book)
    {
      cout << "Book::=" << endl;
      isbn = book.isbn;
      price = book.price;
      return *this;
    }

  private:
    string isbn;
    double price;
};

class MyTest {
  public:
  /*MyTest(const Book &book):
    books(book),num(0.0) { cout << "Mytest::init:" << endl; }*/
  
  MyTest():
    books("0-990-09",2.2),num(0.0) { cout << "Mytest::()" << endl; }
  
  
  MyTest(const Book &book)
  {
    cout << "Mytest::init" << endl;
    books = book;
    num = 0.0;
  }
  

  private:
    Book books;
    double num;
};

int main()
{
  string isbn("9-999-9999");
  cout << "create book===" << endl;
  Book book(isbn,1.1);
  cout << "create test===" << endl;
  MyTest test(book);
  cout << "create test1===" << endl;
  MyTest test1;

  int arr4[2][2][2][2];
  return 0;
}
