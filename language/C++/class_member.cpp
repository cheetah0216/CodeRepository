class A{
  public:
    void printA_pub() {};
    int i_pub;
    
  protected:
    void printA_pro() {};
    int i_pro;

  private:
    void printA_pri() {};
    int i_pri;
};

class B: public A{
  public:
   int j; 
};

int main()
{
  B b1;
  b1.printA_pub();
  b1.printA_pri();
  b1.printA_pro();
  b1.i_pub;
  b1.i_pri;
  b1.i_pro;
}
