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
    
    setBlockSize(0);
    setMemSize(0);
    setMaxDataSize(0);
    setInitialized(NULL);
 
}


void linked_list::Init(int M, int b)
{
    
    if (!getInitialized()) {

        // sets sizes
        setBlockSize(b);
        setMemSize(M);
        setMaxDataSize(b - sizeof(node));
        
        // sets pointers
        setHeadPointer((char*)malloc(M));
        setFrontPointer((node*)getHeadPointer());
        setFreePointer((node*)getHeadPointer());
        setFreeDataPointer((node*)getHeadPointer());
        
        // points to free pointer
        node* node_iterator = getFreePointer();
        
        // initializes list
        for(int i = 0; i < M/b; i++){
            
            if(i == M/b - 1){
                node_iterator->next=NULL;
            }
            
            else{
                node_iterator->key = -2;
                node_iterator->value_len = 0;
                node_iterator->next = (node*)(b+(char*)node_iterator);
            }
            
            node_iterator = node_iterator->next;
        }
    }
    
    setInitialized(true);
}

void linked_list::Destroy()
{
    free(getHeadPointer());
}

/* Insert an element into the list with a given key, given data element, and with a given length*/
void linked_list::Insert (int k, char* data_ptr, int data_len)
{
    if(data_len < 0){
        std::cout << "Could not insert key " << k << ". Data length is less than 0." <<std::endl;
        return;
    }
    else if(data_len > getBlockSize() - sizeof(node)){
        std::cout << "Could not insert key " << k << ". Data length is too large." <<std::endl;
        return;
    }
    else if((getFreePointer()->next) == NULL){
        std::cout << "Could not insert key " << k <<". List full." << std::endl;
        return;
    }
    
    setFreeDataPointer(getFreePointer());
    
    while(true){
        
        // inserts node at free pointer
        if(getFreeDataPointer()->key < 0){
            
            getFreeDataPointer()->key = k;
            getFreeDataPointer()->value_len = data_len;
            
            std::memcpy( (char*)getFreeDataPointer()+(sizeof(node)),
                        data_ptr,
                        (getBlockSize()-sizeof(node)) );
            
            // moves free pointer
            setFreePointer(getFreeDataPointer()->next);
            
            return;
        }
        
        else if(getFreeDataPointer()->next = NULL){
            std::cout<< "Could not insert. End of list reached." <<std::endl;
            return;
        }
        else if (getFreeDataPointer() == getFreePointer()){
            
            setFreeDataPointer(getFreeDataPointer()->next);	
            
        }
    }

}


int linked_list::Delete(int delete_key)
{
    node* to_delete = Lookup(delete_key);
    
    if(to_delete == NULL){
        std::cout << "Could not delete key "<<delete_key<<". Not found." << std::endl;
        return 1;
    }

    node* search = getFrontPointer();
    
    if(search == getFrontPointer()){
        setFrontPointer(getFrontPointer()->next);
    }
    
    while(search->next != to_delete){
        search = search->next;
    }
    
    search->next = to_delete->next;
    
    return 0;
    
}

/* Iterate through the list, if a given key exists, return the pointer to it's node */
/* otherwise, return NULL                                                           */
struct node* linked_list::Lookup(int lookup_key)
{
    
    //std::cout<< "Looking for key: "<<lookup_key<<std::endl;
    node* search = getFrontPointer();
     
    int n = getMemSize()/getBlockSize();
     
    for(int i = 0; i < n; i++){
        
        if(search == NULL){
            
            std::cout<<"Key not found in list: "<< lookup_key << std::endl;
            return NULL;
        }
        else if(search->key == lookup_key){
            return search;
        }
            
        search = search->next;
    }
    
}

/* Prints the list by printing the key and the data of each node */
void linked_list::PrintList()
{
    node* node_iterator = getFrontPointer();
    
    while(node_iterator->next > 0){
        
        std::cout << "Node: " << std::endl;
        std::cout << " - Key: " << node_iterator->key << std::endl;
        std::cout << " - Data: " << node_iterator->value_len << std::endl;
        node_iterator = node_iterator->next;
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

