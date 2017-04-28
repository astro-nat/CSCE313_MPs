/* --------------------------------------------------------------------------- */
/* Developer: Natalie Cluck, Megan Fischer                                     */
/* Project: CSCE-313 Machine Problem #1                                        */
/*                                                                             */
/* File: ./MP1/Part_2/main.cpp                                                 */
/* --------------------------------------------------------------------------- */

/* --------------------------------------------------------------------------- */
/* Standard Library Includes                                                   */
/* --------------------------------------------------------------------------- */

#include <stdlib.h>
#include <string.h>
#include <string.h>

/* --------------------------------------------------------------------------- */
/* User Defined Includes                                                       */
/* --------------------------------------------------------------------------- */

#include "linkedlist2.h"
#include <ctype.h>
#include <unistd.h>

int main(int argc, char ** argv)
{
    int b;
    int M;
    int t;
    int c;
    char *block, *mem, *tiers;
    extern char *optarg;
    
    while ((c = getopt (argc, argv, "b:s:t:")) != -1)
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
        case 't':
            tiers = optarg;
            t = atoi(tiers);
            break;
        default:
            printf("No values given. Using default values.\n");
            b = 128;
            M = b * 16;
            t = 4;
            break;
    }
    
    char buf [1024];
    memset (buf, 1, 1024);		// set each byte to 1
    
    char * msg = "a sample message";
    
    // Instantiate the tiered list class
    linked_list2 *test_list = new linked_list2;
    
    test_list->Init(M, b, t); // initialize
    // test operations
    int testnums [] = {0, 1<<29 , (1<<29) + 5 , 50, (1<<30) + 5, (1<<30) - 500};
    int i = 0;
    printf("before inserting\n");
    test_list->Insert(1, "abc", 80);
    test_list->Insert(3, "kkk", 78);
    // some sample insertions
    
    for (i=0; i< 2; i ++)
    {
        test_list->Insert (testnums [i], buf, 50);   // insert 50 bytes from the buffer as value for each of the insertions
    }
    
    test_list->PrintList();
    
    // end test operations	
    test_list->Destroy();
}
