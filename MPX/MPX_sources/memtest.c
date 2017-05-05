#include "ackerman.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include "my_allocator.h"

int main(int argc, char ** argv) {

    int n = 3;
    int m = 3;
    int c;
    char *block, *mem;
    extern char *optarg;
    
    while ((c = getopt (argc, argv, "n:m:")) != -1)
        switch (c)
    {
        case 'n':
            block = optarg;
            n = atoi(block);
            break;
        case 'm':
            mem = optarg;
            m = atoi(mem);
            break;
        default:
            printf("No values given. Using default values.\n");
            n = 3;
            m = 3;
            break;
    }

    printf("N value entered: %d, ",n);
    printf("M value entered: %d",m);
    
  // input parameters (basic block size, memory length)

    init_allocator(n,m);
    
  // init_allocator(basic block size, memory length)

  ackerman_main();

  // release_allocator()
}
