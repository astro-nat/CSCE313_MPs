/* 
    File: my_allocator.c

    Author: Natalie Cluck, Nicholas Wong
            Department of Computer Science
            Texas A&M University
    Date  : <date>

    Modified: 

    This file contains the implementation of the module "MY_ALLOCATOR".

*/

/*--------------------------------------------------------------------------*/
/* DEFINES */
/*--------------------------------------------------------------------------*/

    /* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* INCLUDES */
/*--------------------------------------------------------------------------*/

#include<stdlib.h>
#include <stdio.h>
#include "my_allocator.h"
#include <math.h>

/*--------------------------------------------------------------------------*/
/* DATA STRUCTURES */ 
/*--------------------------------------------------------------------------*/

    /* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* CONSTANTS */
/*--------------------------------------------------------------------------*/

struct header //24 bytes
{
    char marker; //1byte
    char* next; // 8bytes
    int block_sz; //4bytes
    int free_bit; //4 byte
};

char** free_list;
char* mem_pool;

int basic_block_sz;
int length;
int free_list_sz;
int header_sz=24;
int free_memory; //keeps track of available memory

/*--------------------------------------------------------------------------*/
/* FORWARDS */
/*--------------------------------------------------------------------------*/

    /* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* FUNCTIONS FOR MODULE MY_ALLOCATOR */
/*--------------------------------------------------------------------------*/

/* Don't forget to implement "init_allocator" and "release_allocator"! */
unsigned int init_allocator(unsigned int _basic_block_size,
                                         unsigned int _mem_size)
{
    // Don't run the initialization routine again if the mem array has already been set up
    if(initialized == true)
    {
        return 0;
    }
    
    // If the mem_size is greater than the block_size, return an error
    // Obviously, you can't fit a block that's larger than available memory
    if(_basic_block_size > _mem_size)
    {
        return 0;
    }
    
    // If the block size provided is smaller than the size of the header
    // struct, then return failure (0).  If there isn't enough room for
    // header, then there definitely isn't enough room to contain any data.
    if(_basic_block_size < sizeof(header))
    {
        return 0;
    }
    
    // Round block_size up to a power of two
    if(!isPowerOfTwo(_basic_block_size))
    {
        _basic_block_size = higher_two(_basic_block_size);
    }
    
    // Round mem_size up to a power of two
    if(!isPowerOfTwo(_mem_size))
    {
        _mem_size = higher_two(_mem_size);
    }
    
    // Set block and mem sizes
    basic_block_size = _basic_block_size;
    mem_size = _mem_size;
    
    // Setup memory array
    unsigned int block_power = _basic_block_size;
    int exponent = 0;
    while(block_power != 1)
    {
        block_power = block_power >> 1;
        
        exponent += 1;
    }
    block_power = exponent;
    
    unsigned int mem_power = _mem_size;
    exponent = 0;
    while(mem_power != 1)
    {
        mem_power = mem_power >> 1;
        
        exponent += 1;
    }
    mem_power = exponent;
    
    num_tiers = mem_power - block_power;
    
    // Allocate the header pointer
    void *memory = malloc(mem_size);
    
    head_pointer = (char*) memory;
    
    // Set up the first header structure
    header* primary_header = reinterpret_cast<header*>(memory);
    
    primary_header->next = NULL;
    primary_header->block_size = mem_size;
    primary_header->in_use = false;
    
    // Correctly set up the memory_array
    memory_array = new std::map<int, Addr>;
    for(int i=0; i<=num_tiers; i++)
    {
        int setup_power = 2 << (6 + i);
        memory_array->insert(std::pair<int, Addr>(setup_power, (Addr) NULL));
    }
    
    // The first block in the system will be the one just malloc'ed
    memory_array->at(mem_size) = memory;
    
    // The list is now properly initialized
    initialized = true;
}

void release_allocator()
{
    // If array isn't initialized, don't do anything
    if(initialized == false)
    {
        return;
    }
    
    // Mark all regions as unused
    for(int i=basic_block_size; i<mem_size; i = i * 2)
    {
        header *iterator = (header*) memory_array->at(i);
        
        while(true)
        {
            if(iterator == (header*) NULL)
            {
                break;
            }
            
            iterator->in_use = false;
            
            iterator = iterator->next;
        }
    }
    
    // Coalesce allocated memory regions back into one that can be freed.
    for(int i=basic_block_size; i<mem_size; i = i * 2)
    {
        header *iterator = (header*) memory_array->at(i);
        
        while(true)
        {
            if(iterator == (header*) NULL)
            {
                break;
            }
            
            header* buddy = (header*) find_unused_buddy((Addr) iterator);
            
            if(buddy != (header*) NULL)
            {
                // Combine the two blocks together
                combine_blocks((Addr) iterator, (Addr) buddy);
                
                // Reset the loop so that it goes through the ith tier again
                i = i >> 1;
                break;
            }
            
            iterator = iterator->next;
        }
    }
    
    // Actually free the head pointer
    free(head_pointer);
    
    // Also free the memory array
    free(memory_array);
    
    // Set everything to null
    head_pointer = NULL;
    memory_array = NULL;
    
    
    // Also set initialized = false to indicate that memory was freed.  
    initialized = false;
}


Addr my_malloc(unsigned int _length) {
  /* This preliminary implementation simply hands the call over the 
     the C standard library! 
     Of course this needs to be replaced by your implementation.
  */
    int user_length = _length+header_sz;
    
    if(user_length > free_memory) // if there is not enough memory available, return NULL and print error message
    {
        printf("Requested memory not available!\n");
        return NULL;
    }
    
    int i = log2(length) - log2(user_length); // calculate required index for free_list
    if(i >= 3) ++i; //DO NOT TOUCH free_list[3]
    
    int n = i;
    
    print_list();
    
    while(free_list[i] == NULL)
    {
        --n;
        
        if(n == 3) --n; //skip free_list[3]
        
        if(free_list[n] != NULL)
        {
            while((((header*) free_list[n]) -> block_sz) != user_length)
            {
                if(n == 0) // if we are at free_list[0], do this
                {
                    free_list[n+1] = free_list[n]; // move memory block into next tier in free_list
                    free_list[n] = NULL;
                    ++n;
                    
                    ((header*) free_list[n]) -> next = free_list[n] + (((header*) free_list[n]) -> block_sz)/2; //alter header of
                    ((header*) free_list[n]) -> block_sz = (((header*) free_list[n]) -> block_sz)/2;			//first block of memory
                    
                    ((header*) (((header*) free_list[n]) -> next)) -> marker = 'Z'; // include header for second block of memory
                    ((header*) (((header*) free_list[n]) -> next)) -> next = 0;
                    ((header*) (((header*) free_list[n]) -> next)) -> block_sz = ((header*) free_list[n]) -> block_sz;
                    ((header*) (((header*) free_list[n]) -> next)) -> free_bit = 0;
                }
                else // otherwise do this. This code is similar to the above code.
                {
                    if(n == 2) // because we must leave free_list[3] unchanged
                    {
                        free_list[n+2] = free_list[n];
                        free_list[n] = ((header*) free_list[n]) -> next;
                        n+=2;
                    }
                    else
                    {
                        free_list[n+1] = free_list[n];
                        free_list[n] = ((header*) free_list[n]) -> next;
                        ++n;
                    }
                    
                    ((header*) free_list[n]) -> next = free_list[n] + (((header*) free_list[n]) -> block_sz)/2;
                    ((header*) free_list[n]) -> block_sz = (((header*) free_list[n]) -> block_sz)/2;
                    
                    ((header*) (((header*) free_list[n]) -> next)) -> marker = 'Z';
                    ((header*) (((header*) free_list[n]) -> next)) -> next = NULL;
                    ((header*) (((header*) free_list[n]) -> next)) -> block_sz = ((header*) free_list[n]) -> block_sz;
                    ((header*) (((header*) free_list[n]) -> next)) -> free_bit = 0;
                }
            }
        }
    }
    
    free_memory-=(((header*) free_list[i]) -> block_sz); // subtract memory to be allocated to user from free_memory
    
    ((header*) free_list[i]) -> free_bit = 1;	// change free_bit to 1, meaning it is unavailable
    char* address = free_list[i] + header_sz;	// store the address to be returned to the user
    free_list[i] = ((header*) free_list[i]) -> next; // free_list[i] will now point to the available block of memory,
    // there will be no pointer to the allocated memory block 
    // since it is now unavailable,
    // this must be reversed in my_free()
    
    return address;
}

int my_free(Addr _a) {
  /* Same here! */
    free(_a);
    
    return 0;
}

void print_list(){
    int i= 0;
    printf("\n\n=========");
    while (i != free_list_sz){
        printf("\n FreeList: %d : %p", i, free_list[i]);
        ++i;
    }
    printf("\n=========\n\n");
}

Addr buddy_address(Addr block_address){

}

bool split_block(Addr start_address){
  return true;;
}

bool combine_blocks(Addr start_address1, Addr start_address2){
  return true;;
}
