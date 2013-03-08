#include "singleton.h"

Singleton* Singleton::m_pInstance = NULL;
Locker Singleton::locker;

void * thr_fn1(void *arg)
{
    cout << "this is thread 1!" << endl;
    for( int i =0 ; i < 20; i++)
    	Singleton::GetInstance();  
    return ((void*)1);
}

void * thr_fn2(void *arg)
{
    cout << "this is thread 2!" << endl;
    for( int i =0 ; i < 20; i++)
    	Singleton::GetInstance(); 
    return ((void*)1);
}

int main(int argc, char ** argv)
{
//	Singleton::GetInstance();  
//    	Singleton::GetInstance();  
//    	Singleton::GetInstance();
//    	Singleton::GetInstance();  
//    	Singleton::GetInstance(); 
	
	Singleton::Release(); 

	pthread_t tid1,tid2;
	pthread_create(&tid1, NULL, thr_fn1,NULL);
	pthread_create(&tid2, NULL, thr_fn2,NULL);
	sleep(1);
	return 0;
}
