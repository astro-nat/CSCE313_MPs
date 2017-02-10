/* --------------------------------------------------------------------------- */
/* Developer: Natalie Cluck, Megan Fischer                                  */
/* Project: CSCE-313 Machine Problem #1                                        */
/*                                                                             */
/* File: ./MP1/linked_list2.cpp                                                 */
/* --------------------------------------------------------------------------- */

#include "linkedlist2.h"

using namespace std;

/* Constructor */
linked_list2::linked_list2()
{
    head_pointer = NULL;
    front_pointer = NULL;
    free_pointer = NULL;
    free_data_pointer = NULL;
}

// implement t
void linked_list2::Init(int M, int b, int t)
{
    /*
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
     */
    
    setInitialized(true);
}

void linked_list2::Destroy()
{
    /*
    while(free_pointer != NULL){
        free_pointer = free_pointer->next;
        free(free_pointer);
        free_pointer = free_pointer;

    }
     */
}

/* Insert an element into the list with a given key, given data element, and with a given length*/
void linked_list2::Insert (int k, char* data_ptr, int data_len)
{
    /*
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
     */
}


int linked_list2::Delete(int delete_key)
{
    /*
    node* search = front_pointer;
    
    while(search->next) {
        if ((*search).key == delete_key) {
            (*search).key = -1;
            (*search).payload = "";
            return delete_key;
        }
        search = search->next;
    }
     */
    return delete_key;
}

/* Iterate through the list, if a given key exists, return the pointer to it's node */
/* otherwise, return NULL                                                           */
struct node* linked_list2::Lookup(int lookup_key)
{
    /*
    node* search = front_pointer;
    
    while(search->next) {
        if ((*search).key == lookup_key) {
            return search;
        }
        search = search->next;
    }
     */
    return NULL;
}

/* Prints the list by printing the key and the data of each node */
void linked_list2::PrintList()
{
    /* IMPORTANT NOTE!
     *
     * In order for the script that will grade your assignment to work
     * (i.e. so you get a grade higher than a 0),
     * you need to print out each member of the list using the format below.
     * Your print list function should be written as a while loop that prints
     * the tier of the list and then each node underneath it.
     * the following four lines exactly for each node and nothing else.  If
     * you have any difficulties, talk to your TA and he will explain it further.
     *
     * The output lines that you should use are provided so that you will know
     * exactly what you should output.
     */
    // Do this for every tier
    // std::cout << "Tier " << <TIER NUMBER GOESHERE> << std::endl;
    
    // Do this for every node
    //std::cout << "Node: " << std::endl;
    //std::cout << " - Key: " << <KEY GOES HERE!> << std::endl;
    //std::cout << " - Data: " << <KEY GOES HERE!> << std::endl;
    
    /* Short example:
     *   - Assume a list with two tiers each with two elements in each tier.
     *     the print out would appear as follows
     *
     * Tier 0
     * Node:
     *  - Key: 1
     *  - Data: Hello
     * Node:
     *  - Key: 2
     *  - Data: World!
     * Tier 1
     * Node:
     *  - Key: 3
     *  - Data: Hello
     * Node:
     *  - Key: 4
     *  - Data: World!
     *
     * ^^ Your output needs to exactly match this model to be counted as correct.
     * (With the exception that the values for key and data will be different
     * depending on what insertions you perform into your list.  The values provided
     * here are for pedagogical purposes only)
     */

    /*
    if(front_pointer != NULL) {
        
        node* node_iterator = front_pointer;
        
        while(node_iterator->next != NULL) {
            std::cout << "Node: " << std::endl;
            std::cout << " - Key: " << (*node_iterator).key << std::endl;
            std::cout << " - Data: " << (*node_iterator).payload << std::endl;
            
            node_iterator = node_iterator->next;
            
        }

    }
     */
    
}

int linked_list2::Find_tier(int key)
{
    // IMPLEMENET THIS
    return key;
}

/* Getter Functions */
char** linked_list2::getHeadPointer()
{
    return head_pointer;
}

node** linked_list2::getFrontPointer()
{
    return front_pointer;
}

node** linked_list2::getFreePointer()
{
    return free_pointer;
}

node** linked_list2::getFreeDataPointer()
{
    return free_data_pointer;
}

int linked_list2::getBlockSize()
{
    return block_size;
}

int linked_list2::getMemSize()
{
    return mem_size;
}

int linked_list2::getMaxDataSize()
{
    return max_data_size;
}

bool linked_list2::getInitialized()
{
    return initialized;
}

/* Setter Functions */
void linked_list2::setHeadPointer(char **new_pointer)
{
    head_pointer = new_pointer;
}

void linked_list2::setFrontPointer(node** new_pointer)
{
    front_pointer = new_pointer;
}

void linked_list2::setFreePointer(node** new_pointer)
{
    free_pointer = new_pointer;
}

void linked_list2::setFreeDataPointer(node** new_pointer)
{
    free_data_pointer = new_pointer;
}

void linked_list2::setBlockSize(int new_block_size)
{
    block_size = new_block_size;
}

void linked_list2::setMemSize(int new_mem_size)
{
    mem_size = new_mem_size;
}

void linked_list2::setMaxDataSize(int new_max_data_size)
{
    max_data_size = new_max_data_size;
}

void linked_list2::setNumTiers(int new_num_tiers){
    
}

void linked_list2::setInitialized(bool new_initialized)
{
    initialized = new_initialized;
}

