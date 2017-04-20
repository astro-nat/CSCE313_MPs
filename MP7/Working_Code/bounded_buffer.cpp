#include <cstdlib>
#include <string>
#include <iostream>
#include "semaphore.h"
#include "bounded_buffer.h"
using namespace std;


	bounded_buffer::bounded_buffer(int m) { 
		max = m;
		//pthread_mutex_init(&lock, NULL);
		full.set_val(0);
		empty.set_val(m);
		lock.set_val(1);
	}
	
	
	bounded_buffer::~bounded_buffer()  {
		//pthread_mutex_destroy(&lock);
	}
	
	
	void bounded_buffer::push(string s)  {
		//printf("[%s] %d\n", __FUNCTION__, __LINE__);
		empty.P();
		//printf("[%s] %d\n", __FUNCTION__, __LINE__);
		
		//pthread_mutex_lock(&lock);
		lock.P();
		
		//printf("[%s] %d\n", __FUNCTION__, __LINE__);
		buff.push(s);
		//printf("[%s] %d\n", __FUNCTION__, __LINE__);
		
		//pthread_mutex_unlock(&lock);
		lock.V();
		
		//printf("[%s] %d\n", __FUNCTION__, __LINE__);
		full.V();
		//printf("[%s] %d\n", __FUNCTION__, __LINE__);
	}
	
	
	string bounded_buffer::pop()  {
		full.P();
		//pthread_mutex_lock(&lock);
		lock.P();
		string temp = buff.front();
		buff.pop();
		//pthread_mutex_unlock(&lock);
		lock.V();
		empty.V();
		
		return temp;
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
