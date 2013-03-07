#include <pthread.h>
#include "singleton.h"

Singleton* Singleton::m_pInstance = NULL;
int main(int argc, char ** argv)
{
//	Singleton::GetInstance();  
//    	Singleton::GetInstance();  
//    	Singleton::GetInstance();
//    	Singleton::GetInstance();  
//    	Singleton::GetInstance(); 
	
	Singleton::Release(); 

//带添加多线程
	int err;
	pthread_t tid1,tid2;
//	pthread_create();
	return 0;
}
