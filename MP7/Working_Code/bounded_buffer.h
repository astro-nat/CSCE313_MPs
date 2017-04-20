#ifndef _bounded_buffer_H_	// include file only once
#define _bounded_buffer_H_

#include "semaphore.h"
#include <pthread.h>
#include <string>
#include <queue>
using namespace std;

class bounded_buffer{

private:
	//pthread_mutex_t lock;
	semaphore lock;
	semaphore full;
	semaphore empty;
	int max;

public:
	bounded_buffer(int m);
	~bounded_buffer();
	void push(string s);
	string pop();
	std::queue<string> buff;	
};

#endif


