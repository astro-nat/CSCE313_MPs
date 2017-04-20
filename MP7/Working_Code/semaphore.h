#ifndef _semaphore_H_	// include file only once
#define _semaphore_H_

#include <pthread.h>
#include <string>
using namespace std;

class semaphore{
	
private:
	int count;
	pthread_mutex_t mut;
	pthread_cond_t cond; //the wait queue

public:
	semaphore();
	~semaphore();
	void set_val(int i);
	void P();	
	void V();
	
};

#endif
