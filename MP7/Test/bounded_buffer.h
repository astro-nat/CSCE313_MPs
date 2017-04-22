//
//  bounded_buffer.hpp
//  
//
//  Created by Joshua Higginbotham on 11/4/15.
//
//

#ifndef bounded_buffer_h
#define bounded_buffer_h

#include <stdio.h>
#include <queue>
#include <string>
#include <pthread.h>
#include "semaphore.h"

class bounded_buffer {
	
    semaphore lock;
    semaphore full;
    semaphore empty;
    int max;
    
public:
    bounded_buffer(int _capacity);
    ~bounded_buffer();
    void push_back(std::string str);
    std::string retrieve_front();
    int size();
    std::queue<string> buff;
};

#endif /* bounded_buffer_h */
