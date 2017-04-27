/* --------------------------------------------------------------------------- */
/* Developer: Natalie Cluck, Megan Fischer                                     */
/* Project: CSCE-313 Machine Problem #1                                        */
/*                                                                             */
/* File: ./MP1/Part_1/main.cpp                                                 */
/*                                                                             */
/* NOTE: Input:                                                                */
/*         > g++ -std=c++11 *.cpp -o testlist                                  */
/*         > ./testlist -b 128 -s 1408 -t 4                                    */
/* --------------------------------------------------------------------------- */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "linkedlist.h"
#include <ctype.h>
#include <unistd.h>

int main(int argc, char ** argv)
{
    
    int b = 128;
    int M = b * 11;
    int c;
    char *block, *mem;
    extern char *optarg;
    
    while ((c = getopt (argc, argv, "b:s:")) != -1)
        switch (c)
    {
        case 'b':
            block = optarg;
            b = atoi(block);
            break;
        case 's':
            mem = optarg;
            M = atoi(mem);
            break;
        default:
            printf("No values given. Using default values.\n");
            b = 128;
            M = b*11;
            break;
    }
    
    char buf [1024];
    memset (buf, 1, 1024);		// set each byte to 1
    
    char * msg = "a sample message";
    
    linked_list* test_list = new linked_list();
    
    test_list->Init(M,b); // initialize
    
    // test operations
    int testnums [] = {100, 5, 200, 7, 39, 25, 400, 50, 200, 300};
    int i = 0;
    
    // some sample insertions
    for (i=0; i< 10; i ++)
    {
        test_list->Insert(testnums [i], buf, 50);   // insert 50 bytes from the buffer as value for each of the insertions
    }
    
    // This Insert should fail
    test_list->Insert (150, buf, 200);
    
    test_list->PrintList ();
    test_list->Delete (7);
    test_list->Insert (13, msg, strlen(msg)+1);		// insertion of strings, copies the null byte at the end
    test_list->Delete (55);
    test_list->Insert (15, "test msg", 8);
    test_list->Delete (3);
    test_list->PrintList ();
    
    // a sample lookup operations that should return null, because it is looking up a non-existent number
    node* kv = test_list->Lookup (3);
    if (kv)
    {
        std::cout << "Key = " << kv->key << ", Value Len = " << kv->value_len << std::endl;
    }
    
    // end test operations	
    test_list->Destroy ();
    
}

