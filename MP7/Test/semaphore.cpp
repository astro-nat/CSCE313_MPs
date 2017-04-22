#include "semaphore.h"
#include <iostream>
using namespace std;


	semaphore::semaphore()  { 
		pthread_mutex_init(&mut, NULL);
		pthread_cond_init(&cond, NULL);
	}


	semaphore::~semaphore()  {
		pthread_mutex_destroy(&mut);
		pthread_cond_destroy(&cond);
	}
	

	void semaphore::set_val(int i)  {
		count = i;
	}
	

	void semaphore::P()  {
		pthread_mutex_lock(&mut);
		count--;		
		if(count<0)  {
			pthread_cond_wait(&cond, &mut);
		}
		pthread_mutex_unlock(&mut);
	}
	

	void semaphore::V()  {
		pthread_mutex_lock(&mut);
		count++;
		if(count<= 0)  {
			pthread_cond_signal(&cond);
		}
		pthread_mutex_unlock(&mut);
	}
	
	
	
	
	