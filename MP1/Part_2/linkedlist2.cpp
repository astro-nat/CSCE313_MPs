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
}

// implement t
void linked_list2::Init(int M, int b, int t)
{
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
    
    setInitialized(true);
}

void linked_list2::Destroy()
{
    for(int i = 0; i < num_tiers; i++) {
        
        node* list_iterator = front_pointer[i];
        if(list_iterator != NULL) {
            list_iterator = list_iterator->next;
            free(list_iterator);
            list_iterator = list_iterator;
        }
    }
}

/* Insert an element into the list with a given key, given data element, and with a given length*/
void linked_list2::Insert (int k, char* data_ptr, int data_len)
{
    //std::cout << "Inserting " << k << " into list..." << std::endl;
    if(getInitialized()) {
        int i = Find_tier(k);
        //cout << "Tier number: " << i << endl;
        if(data_len < getBlockSize()) {
            if(front_pointer[i] == NULL) {
                //cout << "Front pointer is NULL" << endl;
                front_pointer[i] = (node*)head_pointer[i];
                free_pointer[i] = front_pointer[i];
            }
            else {
                //cout << "Front pointer is NOT NULL!" << endl;
                front_pointer[i] = (node*)head_pointer[i];
                free_pointer[i] = front_pointer[i];
            }
            if(free_pointer[i] != NULL) {
                //cout << "Free pointer NOT NULL" << endl;
                free_pointer[i]->key = k;
                //std::cout << " - Key: " << free_pointer[i]->key << std::endl;
                free_pointer[i]->payload = data_ptr;
                //std::cout << " - Data: " << free_pointer[i]->payload << std::endl;
                free_pointer[i] = free_pointer[i]->next;
            }
            //else {
                //cout << "LIST IS FULL" << endl;
            //}
        }
        //else{
            //cout << "Block size not big enough" << endl;
        //}
    }

    //cout << "Inserted into list yay" << endl << endl;
}


int linked_list2::Delete(int delete_key)
{
    
     //cout << "Deleting from list..." << endl;
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
         
         return delete_key;
     
     }
    
    return 0;
}

/* Iterate through the list, if a given key exists, return the pointer to it's node */
/* otherwise, return NULL                                                           */
struct node* linked_list2::Lookup(int lookup_key)
{
    //cout << "Looking up a key..." << endl;
    node* search = front_pointer[0];
    
    int i = 0;
    if(lookup_key < num_tiers) {
        while(i < lookup_key) {
            search = front_pointer[i];
        }
        //cout << "FOUND IT" << endl;
        return search;
    }
    return NULL;
    
}

/* Prints the list by printing the key and the data of each node */
void linked_list2::PrintList()
{
    node* list_iterator;
    if(front_pointer != NULL) {
        for(int i = 0; i < num_tiers; i++) {
            std::cout << "Tier " << i << endl;

            if(front_pointer[i] != NULL) {
                list_iterator = front_pointer[i];
                while(front_pointer[i] != NULL) {
                    std::cout << "Node: " << std::endl;
                    std::cout << " - Key: " << list_iterator->key << std::endl;
                    std::cout << " - Data: " << list_iterator->payload << std::endl;
                    list_iterator = list_iterator->next;
                }
                list_iterator = list_iterator->next;
            }
    
        }
    }

}

/* Divides INT_Max by num_tiers to determine min and max values for each tier */
int linked_list2::Find_tier(int key)
{
    int section = (2147483647/num_tiers);
    int j;
    for(int j = 0; j < num_tiers; j++) {
        if(key >= j*section && key < (j+1)*section) {
            return j;
        }
    }
    
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
