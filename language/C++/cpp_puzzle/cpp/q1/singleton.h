// Define your singleton class in this file
#include <iostream>
#include <pthread.h>
using namespace std;

class Locker  
{  
    public:  
    	inline Locker(){        pthread_mutex_init(&mutex,NULL);}  
    	inline ~Locker(){       pthread_mutex_destroy(&mutex);}  
    	inline void Lock(){     pthread_mutex_lock(&mutex);}  
    	inline void Unlock(){   pthread_mutex_unlock(&mutex);}  
    private:  
    	pthread_mutex_t mutex;  
}; 

class Singleton 
{
    public:
        static Singleton* GetInstance();
	static void Release();
    private:
        Singleton();
	static Singleton* m_pInstance;
	static Locker locker; 
};

Singleton::Singleton()  
{  
    cout << "This is Singleton's constructor." << endl;  
}  
  
Singleton* Singleton::GetInstance()  
{   
    if ( m_pInstance == NULL ) 
    {
	locker.Lock();
        if ( m_pInstance == NULL )  
        {  
            m_pInstance = new Singleton();
	    cout << "This is Singleton's instance." << endl;    
        }  
	locker.Unlock();
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

