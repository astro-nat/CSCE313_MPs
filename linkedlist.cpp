#include "linkedlist.h"

LinkedList::LinkedList()
{
    
}

void LinkedList::Init(int M, int C)
{
    Node* node_iterator = (Node*)malloc(M);
    
    head_pointer = node_iterator;
    front_pointer = node_iterator;
    free_pointer = NULL;
    
    int reach = 0;
    int key = 0;
    while(reach <= M/C) {
        node_iterator->key = key;
        node_iterator->value = 42;
        
        Node* next_node = (Node*)((char*)node_iterator + C);
        node_iterator->next = next_node;
        node_iterator = node_iterator->next;

        reach = reach + C;
    }
}

void LinkedList::Destroy()
{
    delete head_pointer;
}

int LinkedList::Insert(int x, char* valueptr, int valuelen)
{
    /*
    if (free_pointer == NULL) free_pointer = head_pointer;
    Node* new_node = new Node;
    new_node->value = x;
    valuelen = new_node->value_len;
    
    if(*valueptr > sizeof(new_node)) {
        free_pointer = new_node + sizeof(new_node);
    }
    /*
    Node* node_ptr = (Node*)buffer;
    node->value = x;
    node_ptr++;
    
    FP = FP + valuelen;
    
    int* temp = (int*) valueptr;
    (*temp) = x;
    for(int i = 0; i < valuelen; i++) {
        temp++;
    }
    */
    return 0;
}

void LinkedList::Delete(int x) {}
Node* LinkedList::Lookup (int x) { Node* a; return a; }
void LinkedList::PrintList ()
{
    Node* iterator = head_pointer;
    std::cout << "Node total length: " << (*iterator).value_len << std::endl;
    
    while(iterator->next != NULL) {
        std::cout << (*iterator).value << std::endl;
        //iterator->next = (Node*)((char*)iterator + iterator->next->value_len);
        iterator = iterator->next;
    }
    
}
