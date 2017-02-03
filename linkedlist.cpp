/* --------------------------------------------------------------------------- */
/* Developer: Andrew Kirfman, Margaret Baxter                                  */
/* Project: CSCE-313 Machine Problem #1                                        */
/*                                                                             */
/* File: ./MP1/linked_list.cpp                                                 */
/* --------------------------------------------------------------------------- */

/* --------------------------------------------------------------------------- */
/* User Defined Includes                                                       */
/* --------------------------------------------------------------------------- */

#include "linkedlist.h"

using namespace std;

/* Constructor */
linked_list::linked_list()
{
    head_pointer = NULL;
    front_pointer = NULL;
    free_pointer = NULL;
    free_data_pointer = NULL;
}


void linked_list::Init(int M, int b)
{
    cout << "Storing memory of size " << M << endl;
    node* node_iterator = (node*)malloc(M);
    
    cout << "Setting front pointer to memory allocation address" << endl;
    front_pointer = node_iterator;
    
    cout << "Setting free pointer to memory allocation address" << endl;
    free_pointer = node_iterator;
    
    cout << "Setting head pointer to memory allocation address" << endl;
    head_pointer = (char*)node_iterator;
    
    int key = 0;
    int reach = 0;
    while(reach < M/b) {
        cout << "Setting key and value of current iterator" << endl;
        (*node_iterator).key = key;
        (*node_iterator).value_len = 42;
        
        cout << "Allocating space for next node" << endl;
        node* next_node = (node*)((char*)node_iterator + b);
        
        cout << "Setting iterator's next to new node" << endl;
        node_iterator->next = next_node;
        
        cout << "Moving iterator to next node" << endl;
        
        node_iterator = node_iterator->next;
        key++;
        reach = reach + b;
        cout << "Reach: " << reach << endl;
    }
    
    setInitialized(true);
}

void linked_list::Destroy()
{
   
}

/* Insert an element into the list with a given key, given data element, and with a given length*/
void linked_list::Insert (int k, char* data_ptr, int data_len)
{
    if (getInitialized()) {
        cout << "Data ptr: " << sizeof(data_ptr) << endl;
        if(sizeof(data_ptr) > sizeof(data_len)){
            (*free_pointer).key = k;
            (*free_pointer).value_len = data_len;
            free_pointer = free_pointer->next;
        }
        else {
            cout << "List is full." << endl;
        }
    }
}


int linked_list::Delete(int delete_key)
{
    
}

/* Iterate through the list, if a given key exists, return the pointer to it's node */
/* otherwise, return NULL                                                           */
struct node* linked_list::Lookup(int lookup_key)
{
    
}

/* Prints the list by printing the key and the data of each node */
void linked_list::PrintList()
{
    if(front_pointer != NULL) {
        
        node* node_iterator = front_pointer;
        
        while(node_iterator->next != NULL) {
            std::cout << "Node: " << std::endl;
            std::cout << " - Key: " << (*node_iterator).key << std::endl;
            std::cout << " - Data: " << (*node_iterator).value_len << std::endl;
            
            node_iterator = node_iterator->next;
            
        }

    }
    
    // USE THIS FORMAT
    //std::cout << "Node: " << std::endl;
    //std::cout << " - Key: " << <KEY GOES HERE!> << std::endl;
    //std::cout << " - Data: " << <KEY GOES HERE!> << std::endl;
}

/* Getter Functions */
char* linked_list::getHeadPointer()
{
    return head_pointer;
}

node* linked_list::getFrontPointer()
{
    return front_pointer;
}

node* linked_list::getFreePointer()
{
    return free_pointer;
}

node* linked_list::getFreeDataPointer()
{
    return free_data_pointer;
}

int linked_list::getBlockSize()
{
    return block_size;
}

int linked_list::getMemSize()
{
    return mem_size;
}

int linked_list::getMaxDataSize()
{
    return max_data_size;
}

bool linked_list::getInitialized()
{
    return initialized;
}

/* Setter Functions */
void linked_list::setHeadPointer(char *new_pointer)
{
    head_pointer = new_pointer;
}

void linked_list::setFrontPointer(node* new_pointer)
{
    front_pointer = new_pointer;
}

void linked_list::setFreePointer(node* new_pointer)
{
    free_pointer = new_pointer;
}

void linked_list::setFreeDataPointer(node* new_pointer)
{
    free_data_pointer = new_pointer;
}

void linked_list::setBlockSize(int new_block_size)
{
    block_size = new_block_size;
}

void linked_list::setMemSize(int new_mem_size)
{
    mem_size = new_mem_size;
}

void linked_list::setMaxDataSize(int new_max_data_size)
{
    max_data_size = new_max_data_size;
}

void linked_list::setInitialized(bool new_initialized)
{
    initialized = new_initialized;
}



/*#include "linkedlist.h"

LinkedList::LinkedList()
{
    head_pointer = NULL;
    front_pointer = NULL;
    free_pointer = NULL;
}

void LinkedList::Init(int M, int C)
{
    Node* node_iterator = (Node*)malloc(M);
    
    head_pointer = (char*)node_iterator;
    front_pointer = node_iterator;
    
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
 
    }
    
    // handles last node
    /*
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
    
    if (free_pointer == NULL) free_pointer = front_pointer;
    
    Node* node_iterator = free_pointer;
    
    std::cout << "Value ptr: " << sizeof(valueptr) << std::endl;
    if(sizeof(valueptr) > sizeof(valuelen)) {
        (*node_iterator).value = x;
        (*node_iterator).value_len = valuelen;
        
        free_pointer = node_iterator->next;

    }
     
     
     
    
    Node* node_ptr = (Node*)buffer;
    node->value = x;
    node_ptr++;
    
    FP = FP + valuelen;
    
    int* temp = (int*) valueptr;
    (*temp) = x;
    for(int i = 0; i < valuelen; i++) {
        temp++;
    }
    
    return 0;
}

void LinkedList::Delete(int x)
{
    
    Node* node_iterator = front_pointer;
    
    if (node_iterator == head_pointer) front_pointer = front_pointer->next;
    
    while(node_iterator->next != NULL) {
        if ((*node_iterator).value == x) {
            //delete node_iterator;
        }
        node_iterator = node_iterator->next;
    }
}

Node* LinkedList::Lookup (int x)
{
    Node* node_iterator = front_pointer;
    
    while(node_iterator->next != NULL) {
        if ((*node_iterator).value == x) {
            return node_iterator;
        }
    }
    
    return NULL;
}

void LinkedList::PrintList ()
{
    
    Node* iterator = front_pointer;
    std::cout << "Node value length: " << (*iterator).value_len << std::endl;
    
    while(iterator->next != NULL) {
        std::cout << "Node: " << std::endl;
        std::cout << " - Key: " << (*iterator).key << std::endl;
        std::cout << " - Data: " << (*iterator).value << std::endl;
        iterator = iterator->next;
        //iterator->next = (Node*)((char*)iterator + iterator->next->value_len);
        
    }
    
}*/
