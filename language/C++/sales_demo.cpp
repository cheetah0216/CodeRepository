#include <iostream>
using namespace std;

class Sales_item {
    friend istream& operator>> (istream&, Sales_item&);
    friend ostream& operator<< (istream&, Sales_item&);
  public:
    Sales_item(): units_sold(0), revenue(0.0) {}

    double avg_proce() const;
    bool same_isbn(const Sales_item &rhs) const;
    Sales_item& operator+=(const Sales_item&);

  private:
    string isbn;
    unsigned units_sold;
    double revenue;
};

double Sales_item::avg_proce() const
{
  if(units_sold)
    return revenue/units_sold;
  else 
    return 0;
}

bool Saled_item::same_isbn(const Sales_item &rhs) const
{
  return isbn == rhs.isbn;
}

Sales_item& Sales_item::operator+=(const Sales_item&)
{
  
}

Sales_item operator+(const Sales_item&, const Sales_item&)
{
}

int main()
{

  return 0;
}
