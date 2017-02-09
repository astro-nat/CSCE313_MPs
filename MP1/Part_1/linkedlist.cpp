/* --------------------------------------------------------------------------- */
/* Developer: Natalie Cluck, Megan Fischer                                  */
/* Project: CSCE-313 Machine Problem #1                                        */
/*                                                                             */
/* File: ./MP1/linked_list.cpp                                                 */
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
    setBlockSize(b);
    setMemSize(M);
    setMaxDataSize(b);
    
    //cout << "Storing memory of size " << M << endl;
    node* node_iterator = (node*)malloc(M);
    
    //cout << "Setting front pointer to memory allocation address" << endl;
    front_pointer = node_iterator;
    
    //cout << "Setting free pointer to memory allocation address" << endl;
    free_pointer = node_iterator;
    
    //cout << "Setting head pointer to memory allocation address" << endl;
    head_pointer = (char*)node_iterator;
    
    int key = 0;
    int reach = 1;
    
    while(reach <= M/b) {
        //cout << "Setting key and value of current iterator" << endl;
        (*node_iterator).key = key;
        (*node_iterator).payload = "Gonna earn that A";
        
        //cout << "Allocating space for next node" << endl;
        node* next_node = (node*)((char*)node_iterator + getBlockSize());
        
        //cout << "Setting iterator's next to new node" << endl;
        node_iterator->next = next_node;
        
        //cout << "Moving iterator to next node" << endl;
        node_iterator = node_iterator->next;
        
        key++;
        reach++;
    }
    
    setInitialized(true);
}

void linked_list::Destroy()
{
    while(free_pointer != NULL){
        free_pointer = free_pointer->next;
        free(free_pointer);
        free_pointer = free_pointer;

    }
}

/* Insert an element into the list with a given key, given data element, and with a given length*/
void linked_list::Insert (int k, char* data_ptr, int data_len)
{
    if (getInitialized()) {
        //cout << "Data ptr: " << data_len << endl;
        //cout << "Block size: " << getBlockSize() << endl;
        
        if(data_len < getBlockSize()){
            (*free_pointer).key = k;
            (*free_pointer).payload = data_ptr;
            free_pointer = free_pointer->next;
        }
        else {
            //cout << "List is full." << endl;
        }
    }
    else {
        //cout << "List doesn't exist." << endl;
    }
}


int linked_list::Delete(int delete_key)
{
    node* search = front_pointer;
    
    while(search->next) {
        if ((*search).key == delete_key) {
            (*search).key = -1;
            (*search).payload = "";
            return delete_key;
        }
        search = search->next;
    }
    return delete_key;
}

/* Iterate through the list, if a given key exists, return the pointer to it's node */
/* otherwise, return NULL                                                           */
struct node* linked_list::Lookup(int lookup_key)
{
    node* search = front_pointer;
    
    while(search->next) {
        if ((*search).key == lookup_key) {
            return search;
        }
        search = search->next;
    }
    return NULL;
}

/* Prints the list by printing the key and the data of each node */
void linked_list::PrintList()
{
    if(front_pointer != NULL) {
        
        node* node_iterator = front_pointer;
        
        while(node_iterator->next != NULL) {
            std::cout << "Node: " << std::endl;
            std::cout << " - Key: " << (*node_iterator).key << std::endl;
            std::cout << " - Data: " << (*node_iterator).payload << std::endl;
            
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
