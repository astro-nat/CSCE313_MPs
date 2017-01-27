#ifndef _LinkedList_h_
#define _LinkedList_h_

#include <iostream>
#include <string>
#include <climits>
#include <cstring>

struct Node {
    Node* next;
};

class LinkedList {
private:
    // ???
    Node* head;
    Node* free;
public:
    LinkedList();
    
    void Init(int M, int C);
    
    void Destroy();
    
    int Insert(int x, char* valueptr, int valuelen);
    
    void Delete(int x);
    
    char* Lookup(int x);
    
    void PrintList();
};

#endif
