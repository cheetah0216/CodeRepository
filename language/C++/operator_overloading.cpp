#include <iostream>
using namespace std;

class Sales_item {
    friend istream& operator>> (istream&, Sales_item&);
    friend ostream& operator<< (ostream&, const Sales_item&);
    friend inline bool operator== (const Sales_item&,const Sales_item&);
  public:
    Sales_item(): units_sold(0), revenue(0.0) {}
    ~Sales_item() {}

    double avg_price() const;
    bool same_isbn(const Sales_item &rhs) const;
    Sales_item& operator+=(const Sales_item&);
    Sales_item& operator=(const Sales_item&);

  private:
    string isbn;
    unsigned units_sold;
    double revenue;
};

double Sales_item::avg_price() const
{
  if(units_sold)
    return revenue/units_sold;
  else 
    return 0;
}

bool Sales_item::same_isbn(const Sales_item &rhs) const
{
  return isbn == rhs.isbn;
}

Sales_item& Sales_item::operator+=(const Sales_item& rhs)
{
  units_sold += rhs.units_sold;
  revenue += rhs.revenue;
  return *this;
}

Sales_item& Sales_item::operator=(const Sales_item& rhs)
{
  isbn = rhs.isbn;
  units_sold = rhs.units_sold;
  revenue = rhs.revenue;
  return *this;
}

Sales_item operator+(const Sales_item& lhs, const Sales_item& rhs)
{
  Sales_item ret(lhs);
  ret += rhs;
  return ret;
}

inline bool operator== (const Sales_item& lhs, const Sales_item& rhs)
{
  return lhs.units_sold == rhs.units_sold 
    && lhs.revenue == rhs.revenue
    && lhs.same_isbn(rhs);
}

inline bool operator!= (const Sales_item& lhs, const Sales_item& rhs)
{
  return !(lhs == rhs);  
}

ostream& operator<< (ostream& out, const Sales_item& s)
{
  out << s.isbn << "\t" << s.units_sold << "\t" << 
    s.revenue << "\t" << s.avg_price();
  return out;
}

istream& operator>> (istream& in, Sales_item& s)
{
  double price = 0.0;
  in >> s.isbn >> s.units_sold >> price;
  if (in)
    s.revenue = s.units_sold * price;
  else 
    s = Sales_item();
  return in;
}

void test_add()
{
  //input: 0-021-78345-X 3 20.00
  //input: 0-021-78345-X 2 25.00
  //output: 0-021-78345-X 5 110 22
  Sales_item item1, item2;
  cin >> item1 >> item2;
  cout << item1 + item2 << endl;
}

void test()
{
  Sales_item total, trans;
  if( cin >> total )
  {
    while( cin >> trans )
    {
      if (total.same_isbn(trans))
        total = total + trans;
      else
      {
        cout << total << endl;
        total = trans;
      }
    }
    cout << total << endl;
  }
  else
  {
    cout << "No date?!" << endl;
  }
}

int main()
{
  //test_add();
  test();
  return 0;
}
