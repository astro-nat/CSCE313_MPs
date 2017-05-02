/* --------------------------------------------------------------------------- */
/* Developer: Natalie Cluck, Megan Fischer                                     */
/* Project: CSCE-313 Machine Problem #1                                        */
/*                                                                             */
/* File: ./MP1/linked_list2.cpp                                                */
/* --------------------------------------------------------------------------- */

/* --------------------------------------------------------------------------- */
/* Standard Library Includes                                                   */
/* --------------------------------------------------------------------------- */

#include <iostream>
#include <string.h>
#include <climits>

/* --------------------------------------------------------------------------- */
/* User Defined Includes                                                       */
/* --------------------------------------------------------------------------- */

#include "linkedlist2.h"

linked_list2::linked_list2()
{
    head_pointer = NULL;
    front_pointer = NULL;
    free_pointer = NULL;
    free_data_pointer = NULL;
    
    block_size = 0;
    mem_size = 0;
    max_data_size = 0;
    num_tiers = 0;
    setInitialized(NULL);
}

void linked_list2::Init(int M, int b, int t)
{
    //Check if Initialized
    if (initialized == true)
    {
        //std::cout << "\nThe list has already been initialized!" << std::endl;
        return;
    }
    
    //Memory Size
    if (M < b)
    {
        do
        {
            int new_memory_size = M;
        }
        
        while(M < b);
        
    }
    
    //Block Size
    else if (b < sizeof(node))
    {
        do
        {
            int new_block_size = b;
        }
        
        while(b < sizeof(node));
        
    }
    
    //Set Memory Size, Block Size, and Tiers
    mem_size = M;
    block_size = b;
    num_tiers = t;

    int number_of_blocks = M / b;

    //Maximum Data Size
    max_data_size = (block_size - sizeof(node));
    
    //Pointers for Tiers
    char* pointer_size = NULL;
    head_pointer = (char**) malloc(t*sizeof(pointer_size));
    
    for(int i = 0; i < t; i++)
    {
        head_pointer[i] = (char*) malloc(block_size*number_of_blocks);
    }
    
    char** tier_pointer = head_pointer;
    
    for(int i = 0; i < t; i++)
    {
        char* char_iterator = tier_pointer[i];
        node* node_iterator = reinterpret_cast<node*>(head_pointer[i]);
        
        for(int i = 0; i < number_of_blocks; i++)
        {
            node_iterator->value_len = -1;
            node_iterator->key = -1;
            
            if(i == (number_of_blocks - 1))
            {
                node_iterator->next = NULL;
            }
            
            else
            {
                char_iterator += block_size;
                node_iterator->next = reinterpret_cast<node*>(char_iterator);
                node_iterator = node_iterator->next;
            }
        }
    }
    
    free_data_pointer = new node*[t];
    free_pointer = new node*[t];
    front_pointer = new node*[t];
    
    for(int i = 0; i < t; i++)
    {
        free_data_pointer[i] = reinterpret_cast<node*>(head_pointer[i]);
        free_pointer[i] = NULL;
        front_pointer[i] = NULL;
    }
    
    setInitialized(true);
    
}

void linked_list2::Destroy()
{
    //Check if Destroyed
    if (initialized == false)
    {
        //std::cout << "\nThere is no list here to destroy!" << std::endl;
        return;
    }
    
    for(int i = 0; i < num_tiers; i++)
    {
        free(head_pointer[i]);
        head_pointer[i] = NULL;
        front_pointer[i] = NULL;
        free_pointer[i] = NULL;
        free_data_pointer[i] = NULL;
    }
    
    block_size = 0;
    mem_size = 0;
    max_data_size = 0;
    num_tiers = 0;
    
    free(head_pointer);
    head_pointer = NULL;
    front_pointer = NULL;
    free_pointer = NULL;
    free_data_pointer = NULL;
    
    initialized = false;
    
}

void linked_list2::Insert(int k, char * data_ptr, int data_len)
{
    if (Lookup(k) != NULL)
    {
        std::cout << "\nAn element with this key (" << k << ") already exists." << std::endl;
    }

    int tier = Find_tier(k);
        
    if(free_data_pointer[tier] != NULL)
    {
        free_data_pointer[tier]->key = k;
        free_data_pointer[tier]->value_len = data_len;
            
        char * data_pointer = reinterpret_cast<char*>(free_data_pointer[tier]);
        memcpy(data_pointer + sizeof(node), data_ptr, data_len);

        if (front_pointer[tier] == NULL)
        {
            front_pointer[tier] = free_data_pointer[tier];
            free_pointer[tier] = front_pointer[tier];
                
            if (free_data_pointer[tier]->next != NULL)
            {
                free_data_pointer[tier] = free_data_pointer[tier]->next;
            }
                
            else
            {
                free_data_pointer[tier] = NULL;
            }
                
            free_pointer[tier]->next = NULL;
            
        }
            
        else
        {

            free_pointer[tier]->next = free_data_pointer[tier];
            free_pointer[tier] = free_pointer[tier]->next;
            
            if (free_data_pointer[tier]->next != NULL)
            {
                free_data_pointer[tier] = free_data_pointer[tier]->next;
            }
                
            else
            {
                free_data_pointer[tier] = NULL;
            }
                
            free_pointer[tier]->next = NULL;
                
        }
    }
}

int linked_list2::Delete(int delete_key)
{
    int tier = Find_tier(delete_key);
        
    if (front_pointer[tier] != NULL)
    {
        node* delete_node = Lookup(delete_key);
        
        if (delete_node == NULL)
        {
            std::cout << "\nA node with the key to be deleted: " << delete_key << " does not exist." << std::endl;
        }
            
        char * delete_position = reinterpret_cast<char*>(delete_node);
        memset(delete_position + sizeof(node), '\0', (block_size - sizeof(node)));
            
        delete_node->key = 0;
        delete_node->value_len = -1;
            
        if (delete_node == front_pointer[tier])
        {
            if (delete_node->next != NULL)
            {
                front_pointer[tier] = delete_node->next;
            }
                
            else
            {
                front_pointer[tier] = NULL;
                free_pointer[tier] = NULL;
            }
        }
            
        else
        {
            struct node* prev_node = front_pointer[tier];
                
            while(prev_node->next != delete_node)
            {
                prev_node = prev_node->next;
            }
                
            if (delete_node->next != NULL)
            {
                prev_node->next = delete_node->next;
            }
                
            else
            {
                prev_node->next = NULL;
            }
        }
            
        delete_node->next = free_data_pointer[tier];
        free_data_pointer[tier] = delete_node;
        
    }

    return 0;
    
}

node* linked_list2::Lookup(int lookup_key)
{
    int tier = Find_tier(lookup_key);
    
    node* iteration_pointer = front_pointer[tier];
    
    if (iteration_pointer == NULL)
    {
        return NULL;
    }
    
    while(true)
    {
        if (iteration_pointer->key == lookup_key)
        {
            return iteration_pointer;
        }
        
        if (iteration_pointer->next == NULL)
        {
            return NULL;
        }
        
        iteration_pointer = iteration_pointer->next;
        
    }
    
    return NULL;
    
}

void linked_list2::PrintList ()
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
    //std::cout << "Contents of the linked list:" << std::endl;
    
    for (int i = 0; i < num_tiers; i++)
    {
        node *iteration_pointer = front_pointer[i];
        
        if (iteration_pointer != NULL)
        {
            std::cout << "Tier " << i << std::endl;
            while(true)
            {
                std::cout << "Node: " << std::endl;
                std::cout << " - Key: " << iteration_pointer->key << std::endl;
                std::cout << " - Data: " << iteration_pointer->value_len;
                
                char * data_pointer = reinterpret_cast<char*>(iteration_pointer);
                data_pointer = data_pointer + sizeof(node);
                
                for (int i = 0; i < iteration_pointer->value_len; i++)
                {
                    std::cout << *(data_pointer);
                    data_pointer += 1;
                }
                
                std::cout << std::endl;
                if(iteration_pointer->next == NULL)
                {
                    break;
                }
                
                iteration_pointer = iteration_pointer->next;
                
            }
        }
    }
}

int linked_list2::Find_tier(int key)
{
    int tier_size = INT_MAX/num_tiers;
    
    for (int i = 1; i < num_tiers + 1; i++)
    {
        if(i == num_tiers)
        {
            return num_tiers - 1;
        }
        
        if(key < tier_size * i)
        {
            return (i - 1);
        }
    }
    
    return -1;
    
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

int linked_list2::getNumTiers()
{
    return num_tiers;
}

bool linked_list2::getInitialized()
{
    return initialized;
}

/* Setter Functions */
void linked_list2::setHeadPointer(char** new_head_pointer)
{
    head_pointer = new_head_pointer;
}

void linked_list2::setFrontPointer(node** new_front_pointer)
{
    front_pointer = new_front_pointer;
}

void linked_list2::setFreePointer(node** new_free_pointer)
{
    free_pointer = new_free_pointer;
}

void linked_list2::setFreeDataPointer(node** new_free_data_pointer)
{
    free_data_pointer = new_free_data_pointer;
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

void linked_list2::setNumTiers(int new_num_tiers)
{
    num_tiers = new_num_tiers;
}

void linked_list2::setInitialized(bool new_initialized)
{
    initialized = new_initialized;
}
