#include <iostream>

class Sales_item {
  public:
    Sales_item() {}
    Sales_item(std::string &book):
        isbn(book),units_sold(0),revenue(0.0) {}

    int same_isbn(const Sales_item & item) { return item.isbn == isbn; }

  private:
    //static const std:string fliu = "CPP";
    std::string isbn;
    int units_sold;
    double revenue;

  public:
    //static const int fliu = 24;
    static const char fliu = 'C';
};

const char Sales_item::fliu;
int main()
{
  std::string null_book = "9-999-9999";
  Sales_item item;
  int result =  -1;
  result = item.same_isbn(null_book);
  std::cout << result << std::endl;
  std::cout << Sales_item::fliu << std::endl;
  return 0;
}
