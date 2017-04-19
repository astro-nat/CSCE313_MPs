//
//  SafeBuffer.cpp
//
//
//  Created by Joshua Higginbotham on 11/4/15.
//
//

#include "SafeBuffer.h"
#include <string>
#include <queue>

SafeBuffer::SafeBuffer() {
	pthread_mutex_init(&m, NULL);
}

SafeBuffer::~SafeBuffer() {
    //delete m;
    //delete elements;
}

int SafeBuffer::size() {
    return elements.size();
}

void SafeBuffer::push_back(std::string str) {
    elements.push(str);
}

std::string SafeBuffer::retrieve_front() {
    elements.pop();
}
