#include "linkedlist.h"

LinkedList::LinkedList()
{
    head_pointer = NULL;
    front_pointer = NULL;
    free_pointer = NULL;
}

void LinkedList::Init(int M, int C)
{
    Node* node_iterator = (Node*)malloc(M);
    
    head_pointer = node_iterator;
    front_pointer = node_iterator;
    
    int reach = 0;
    int key = 0;
    while(node_iterator->next != NULL) {
        node_iterator->key = key;
        node_iterator->value = 42;
        
        Node* next_node = (Node*)((char*)node_iterator + C);
        node_iterator->next = next_node;
        node_iterator = node_iterator->next;
        
        key++;
        
        //reach = reach + C;
        
        /* Notes for part 2
         
         char** hand_ptr;
            head_ptr = (char**)malloc(t*sizeof(char))
         head_tr[0] for(int i = 0; i < t; i++) {
         
         head_ptr[i] = char*)malloc(M/t)
         */
    }
    
    // handles last node
    node_iterator->key = key;
    node_iterator->value = 42;
    
    Node* next_node = (Node*)((char*)node_iterator + C);
    node_iterator->next = next_node;
    node_iterator = node_iterator->next;
    
}

void LinkedList::Destroy()
{
    free(head_pointer);
}

int LinkedList::Insert(int x, char* valueptr, int valuelen)
{
    
    if (free_pointer == NULL) free_pointer = head_pointer;
    
    Node* node_iterator = free_pointer;
    
    //if(*valueptr > valuelen) {
        (*node_iterator).value = x;
        (*node_iterator).value_len = valuelen;
        
        free_pointer = node_iterator->next;

    //}
     
     
     
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

void LinkedList::Delete(int x)
{
    Node* node_iterator = front_pointer;
    
    while(node_iterator->next != NULL) {
        if ((*node_iterator).value == x) {
            delete node_iterator;
        }
        node_iterator = node_iterator->next;
    }
}

Node* LinkedList::Lookup (int x)
{
    //Node* a; return a;
}

void LinkedList::PrintList ()
{

    Node* iterator = front_pointer;
    std::cout << "Node value length: " << (*iterator).value_len << std::endl;
    
    while(iterator->next != NULL) {
        std::cout << (*iterator).key << std::endl;
        std::cout << (*iterator).value << std::endl;
        iterator = iterator->next;
        //iterator->next = (Node*)((char*)iterator + iterator->next->value_len);
        
    }
    //std::cout << (*iterator).value << std::endl;
    
    
}
