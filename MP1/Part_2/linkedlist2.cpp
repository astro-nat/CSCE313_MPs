/* --------------------------------------------------------------------------- */
/* Developer: Natalie Cluck, Megan Fischer                                     */
/* Project: CSCE-313 Machine Problem #1                                        */
/*                                                                             */
/* File: ./MP1/linked_list2.cpp                                                */
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
    cout << "Constructor called" << endl;
}

// implement t
void linked_list2::Init(int M, int b, int t)
{
    cout << "Making the list homies" << endl;
    setBlockSize(b);
    setMemSize(M);
    setMaxDataSize(b);
    setNumTiers(t);
    
    head_pointer = (char**)malloc(t*sizeof(char*));
    free_pointer = (node**)malloc(t*sizeof(node*));
    front_pointer = (node**)malloc(t*sizeof(node*));
    
    for(int i = 0; i < t; i++) {
        head_pointer[i] = (char*)malloc(M/t);
        free_pointer[i] = (node*)head_pointer[i];
        front_pointer[i] = NULL;
    }
    
    //front_pointer = (node**)head_pointer[0];
    //free_pointer = (node**)head_pointer[0];
    
    /*
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
    cout << "Initialized aaaaw yeaaaaah" << endl;
}

void linked_list2::Destroy()
{
    cout << "Destorying the list" << endl;
    for(int i = 0; i < num_tiers; i++) {
        while(free_pointer[i] != NULL){
            free_pointer[i] = free_pointer[i]->next;
            free(free_pointer);
            free_pointer[i] = free_pointer[i];
        }
    }
    cout << "List destroyed!" << endl;
}

/* Insert an element into the list with a given key, given data element, and with a given length*/
void linked_list2::Insert (int k, char* data_ptr, int data_len)
{
    std::cout << "Inserting into list..." << std::endl;
    
    if(getInitialized()) {
        
        int i = 0;
        if(data_len < getBlockSize()) {
            
            //if(front_pointer[0] == NULL) {
                //front_pointer[0] == (node*)head_pointer[0];
                free_pointer[i]->key = k;
                free_pointer[i]->payload = data_ptr;
                free_pointer[i] = free_pointer[i]->next;
            }
        }
    
    
    
    /*
    if (getInitialized()) {
        if(data_len < getBlockSize()) {
            (*free_pointer)->key = k;
            (*free_pointer)->payload = data_ptr;
            (*free_pointer) = (*free_pointer)->next;
        }
        else {
            cout << "List is full." << endl;
        }
    }
     */

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
    cout << "Inserted into list yay" << endl;
}


int linked_list2::Delete(int delete_key)
{
    /*
    cout << "Deleting from list..." << endl;
    node* search = front_pointer[0];
    
    int i = 0;
    if(delete_key < num_tiers){
        while(i < delete_key) {
            search = front_pointer[i];
        }
    
        node temp_pointer = search[0];
        for(int i = 0; i < (mem_size/num_tiers); i++) {
            temp_pointer = search[i];
            temp_pointer.key = -1;
            temp_pointer.payload = "";
        }
        cout << "IT'S GONE SUCKAS" << endl;
        return delete_key;
    }
     */
    return 0;
}

/* Iterate through the list, if a given key exists, return the pointer to it's node */
/* otherwise, return NULL                                                           */
struct node* linked_list2::Lookup(int lookup_key)
{
    cout << "Looking up a key..." << endl;
    node* search = front_pointer[0];
    
    int i = 0;
    if(lookup_key < num_tiers) {
        while(i < lookup_key) {
            search = front_pointer[i];
        }
        cout << "FOUND IT" << endl;
        return search;
    }
    cout << "Ain't no key like that fam" << endl;
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

    cout << "Printing the list..." << endl;
    if(front_pointer != NULL) {
        
        //char** tier_iterator = head_pointer;
        node* list_iterator = front_pointer[0];
        
        for(int i = 0; i < num_tiers; i++) {
            list_iterator = front_pointer[i];
            
            while((list_iterator)->next != NULL) {
                std::cout << "Tier " << i << endl;
                std::cout << "Node: " << std::endl;
                std::cout << " - Key: " << (list_iterator)->key << std::endl;
                std::cout << " - Data: " << (list_iterator)->payload << std::endl;
                
                list_iterator = list_iterator->next;
                
            }

        }
        
        /*
        int i = 0;
        while(i < num_tiers) {
            
            list_iterator = (node*)head_pointer[i][0];
            
            while((list_iterator)->next != NULL) {
                std::cout << "Tier " << i << endl;
                std::cout << "Node: " << std::endl;
                std::cout << " - Key: " << (list_iterator)->key << std::endl;
                std::cout << " - Data: " << (list_iterator)->payload << std::endl;
            
                list_iterator = list_iterator->next;
            
            }
            
            i++;
        }
         */

    }
    
}

// WORK ON THIS LATER, THEN IMPLEMENT INSERT
int linked_list2::Find_tier(int key)
{
    int section = (mem_size/num_tiers);
    int count = 0;
    
    for(int i = 0; i < count; i++) {
        
    }
    //return head_pointer[key];
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
    num_tiers = new_num_tiers;
}

void linked_list2::setInitialized(bool new_initialized)
{
    initialized = new_initialized;
}

