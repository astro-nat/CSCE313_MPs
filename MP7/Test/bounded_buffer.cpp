//
//  bounded_buffer.cpp
//  
//
//  Created by Joshua Higginbotham on 11/4/15.
//
//

#include "bounded_buffer.h"
#include "semaphore.h"
#include <string>
#include <queue>

bounded_buffer::bounded_buffer(int _capacity) {
    max = _capacity;
    full.set_val(0);
    empty.set_val(_capacity);
    lock.set_val(1);
}

bounded_buffer::~bounded_buffer(){
    
}

void bounded_buffer::push_back(std::string req) {
    empty.P();
    lock.P();
    buff.push(req);
    lock.V();
    full.V();
}

std::string bounded_buffer::retrieve_front() {
    full.P();
    lock.P();
    string t = buff.front();
    buff.pop();
    lock.V();
    empty.V();
    return t;
}

int bounded_buffer::size() {
    return max;
}
