#include <iostream>
#include <set>
using namespace std;

class Item_base {
  public:
    Item_base(const string book = "", double sales_price = 0.0):
      isbn(book), price(sales_price) {}
    virtual ~Item_base() {}
    virtual Item_base* clone() const;

  public:
    string book() const { return isbn; }
    virtual double net_price(size_t n) const;

  private:
    string isbn;
  protected:
    double price;
};

Item_base* Item_base::clone() const
{
  return new Item_base(*this);
}

double Item_base::net_price(size_t n) const
{
  return n * price;
}

class Disc_item: public Item_base{
  public:
    Disc_item(const string &book = "", double sales_price = 0.0,
              size_t qty = 0, double disc_rate = 0.0):
      Item_base(book, sales_price), quantity(qty), discount(disc_rate) {}
    ~Disc_item() {}

  public:
    double net_price(size_t n) const = 0;

  protected:
    size_t quantity;
    double discount;
};

class Bulk_item: public Disc_item{
  public:
    Bulk_item(const string &book = "", double sales_price = 0.0,
              size_t qty = 0, double disc_rate = 0.0):
      Disc_item(book, sales_price, qty, disc_rate) {}
    ~Bulk_item() {}

  Bulk_item* clone() const;
  public:
    double net_price(size_t) const;
};

Bulk_item* Bulk_item::clone() const
{
  return new Bulk_item(*this);
}

double Bulk_item::net_price(size_t n) const
{
  if( n >= quantity )
    return n * (1-discount) * price;
  else
    return n * price;
}

class Sales_item {
  public:
  Sales_item():p(0), use(new size_t(1)) {}
  Sales_item(const Item_base& item): p(item.clone()), use(new size_t(1)) {}
  Sales_item(const Sales_item& item):p(item.p), use(item.use) { ++*use; }
  ~Sales_item() { decr_use(); }

  Sales_item& operator=(const Sales_item&);
  const Item_base* operator->() const;
  const Item_base& operator*() const;

  private:
    void decr_use();
  private:
    Item_base *p;
    size_t *use;

};

Sales_item& Sales_item::operator=(const Sales_item& rhs)
{
  ++*rhs.use;
  decr_use();
  p = rhs.p;
  use = rhs.use;
  return *this;
}

const Item_base* Sales_item::operator->() const
{
  if(p)
    return p;
  else
    throw logic_error("unbound Sales_item");
}

const Item_base& Sales_item::operator*() const
{
  if(p)
    return *p;
  else
    throw logic_error("unbound Sales_item");
}

void Sales_item::decr_use()
{
  if( --*use == 0 )  
  {
    delete p;
    delete use;
  }
}

inline bool compare(const Sales_item &lhs, const Sales_item &rhs)
{
  return lhs->book() < rhs->book();
}

class Basket{
  typedef bool (*Comp)(const Sales_item&, const Sales_item&);

  public:
    typedef multiset<Sales_item, Comp> set_type;
    typedef set_type::size_type size_type;
    typedef set_type::const_iterator const_iter;
    Basket(): items(compare) {}

  public:
    void add_item(const Sales_item&);
    size_type size(const Sales_item&) const;
    double total() const;

  private:
    multiset<Sales_item, Comp> items;
};

void Basket::add_item(const Sales_item& item)
{
  items.insert(item);
}

Basket::size_type Basket::size(const Sales_item& item) const
{
  return items.count(item);
}

double Basket::total() const
{
  double sum = 0.0;
  for(const_iter iter = items.begin();
      iter != items.end();
      iter = items.upper_bound(*iter))
  {
    sum += (*iter)->net_price(items.count(*iter));
  }
  return sum;
}

void print_total(ostream &os, const Item_base &item, size_t n)
{
  os << "ISBN: " << item.book() << "\tnumber sold: "
    << n << "\ttotal price: " << item.net_price(n) << endl;
}

void print_total(ostream &os, const Sales_item &item, size_t n)
{
  os << "ISBN: " << item->book() << "\tnumber sold: "
    << n << "\ttotal price: " << item->net_price(n) << endl;
}

void Bulk_test()
{
  cout << "Bulk_test:" << endl;
  Bulk_item bulk("0-201-82470-1", 50, 5, 0.19);
  print_total(cout, bulk, 6);
  print_total(cout, bulk, 4);
}

void Sales_handle_test()
{
  cout << "Sales_test:" << endl;
  Sales_item item(Bulk_item("0-201-82470-1", 50, 5, 0.19));
  print_total(cout, item, 6);
  print_total(cout, item, 4);
}

void Basket_test()
{
  cout << "Basket_test:" << endl;
  Sales_item item1(Bulk_item("0-201-82470-1", 50, 3, 0.20));
  Sales_item item2(Bulk_item("0-201-82470-1", 50, 3, 0.20));
  Sales_item item3(Bulk_item("0-201-82470-1", 50, 3, 0.20));
  print_total(cout, item1, 3);

  Sales_item item4(Bulk_item("0-201-82470-2", 30, 5, 0.20));
  Sales_item item5(Bulk_item("0-201-82470-2", 30, 5, 0.20));
  print_total(cout, item4, 2);

  Sales_item item6(Bulk_item("0-201-82470-3", 20, 5, 0.20));
  print_total(cout, item6, 1);

  Basket bas;
  bas.add_item(item1);
  bas.add_item(item2);
  bas.add_item(item3);
  bas.add_item(item4);
  bas.add_item(item5);
  bas.add_item(item6);
  cout << "total:" << bas.total() << endl;
}

int main()
{
  Bulk_test();
  Sales_handle_test();
  Basket_test();
  return 0;
}
