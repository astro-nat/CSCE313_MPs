/* -------------------------------------------------------------------------- */
/* Developers: Natalie Cluck, Megan Fischer                                   */
/* Project: CSCE-313 Machine Problem #2                                       */
/*                                                                            */
/* File: ./mp2_part4.cpp                                                      */
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/* Standard Library Includes                                                  */
/* -------------------------------------------------------------------------- */

#include <stdlib.h>
#include <unistd.h>


int main()
{
    
    char *const argsList[] = {"/bin/ls", "-la", NULL};
    execvp("ls", argsList);
    
    exit(0);
}

