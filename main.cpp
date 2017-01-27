/********************************************************************************
 
 Notes:
 
 Console: testlist -b <blocksize> -s <memsize>
 -b <blocksize> | Defines the basic block size, b, in bytes. Default = 128 bytes
 -s <memsize>   | Defines size of memory allocated in bytes. Default = 512 kB
 
 Scenarios to accout for:
 – Deleting non-existent keys from the list.
 – Trying to insert keys after the given memory is full.
 – Trying to insert values that do not fit in the payload section.
 
 
 ********************************************************************************/


#include "LinkedList.h"

using namespace std;

// THIS CODE IS COPIED DIRECTLY FROM THE SUPPLIED SAMPLE CODE
// SHOULD UPDATE BY DUE DATE 2/5
int main(int argc, char ** argv)
{
    int b = 128;
    int M = b * 11;  // so we have space for 11 items
    
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
