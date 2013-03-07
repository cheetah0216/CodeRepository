// Define your singleton class in this file
#include <iostream>
using namespace std;

class Singleton {
    public:
        static Singleton* GetInstance();
	static void Release();
    private:
        Singleton();
	static Singleton* m_pInstance;
};

Singleton::Singleton()  
{  
    cout << "This is Singleton's constructor." << endl;  
}  
  
Singleton* Singleton::GetInstance()  
{  
    if ( m_pInstance == NULL )  
    {  
        m_pInstance = new Singleton();
	cout << "This is Singleton's instance." << endl;    
    }  
    return m_pInstance;  
}  

void Singleton::Release()
{
   if( m_pInstance != NULL )
   {
	delete m_pInstance;
	cout << "delete Singleton's instance" << endl;
   }
}

