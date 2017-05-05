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
unsigned int round(unsigned int _length)
{
    unsigned int mem;
    
    if(_length < 32)
        return mem = 32;
    
    unsigned int power = ceil(log2(_length));
    mem = pow (2, power);
    
    return mem;
}

unsigned int init_allocator(unsigned int _basic_block_size,unsigned int _length){
    _length = round(_length);
    _basic_block_size = round(_basic_block_size);
    
    free_list_sz = log2(_length) - log2(_basic_block_size) + 2;
    basic_block_sz = _basic_block_size;
    length=_length;
    free_memory=length;
    
    if((mem_pool = (char*) malloc(length)) == NULL)
    {
        printf("Request to allocate memory failed!");
        return 1;
    }
    if((free_list = (char**) malloc(free_list_sz)) == NULL)
    {
        printf("Request to allocate memory failed!");
        free(mem_pool);
        return 1;
    }
    
    ((header*) mem_pool) -> marker = 'Z';
    ((header*) mem_pool) -> next = 0;
    ((header*) mem_pool) -> block_sz = _length;
    ((header*) mem_pool) -> free_bit = 0; // 0 means block is available, 1 means it is unavailable
    
    free_list[0] = mem_pool;
    
    int i= 1;
    while (i != free_list_sz){
        if(i == 3) ++i; // free_list[3] is special for some unknown reason, therefore we must leave it unchanged
        
        free_list[i] = NULL;
        ++i;
    }
}

int release_allocator(){
    free(mem_pool);
    free(free_list);
    return 0;
}

Addr my_malloc(unsigned int _length) {
  /* This preliminary implementation simply hands the call over the 
     the C standard library! 
     Of course this needs to be replaced by your implementation.
  */
    int user_length = round(_length+header_sz);
    
    if(user_length > free_memory) // if there is not enough memory available, return NULL and print error message
    {
        printf("Requested memory not available!\n");
        return NULL;
    }
    
    int i = log2(length) - log2(user_length); // calculate required index for free_list
    if(i >= 3) ++i; //DO NOT TOUCH free_list[3]
    
    int n = i;
    
    //print();
    
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
