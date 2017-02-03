#ifndef _LinkedList_h_
#define _LinkedList_h_

#include <iostream>
#include <string>
#include <climits>
#include <cstring>

struct Node {
    
    int key;
    int value;
    int value_len;
    
    Node* next;
    
    Node() {}
};

class LinkedList {
private:
    // ???
    Node* head_pointer;
    Node* front_pointer;
    Node* free_pointer;
    
    int list_size;
    
public:
    LinkedList();
    
    void Init(int M, int C);
    
    void Destroy();
    
    int Insert(int x, char* valueptr, int valuelen);
    
    void Delete(int x);
    
    Node* Lookup(int x);
    
    void PrintList();
};

#endif
