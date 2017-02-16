/* -------------------------------------------------------------------------- */
/* Developers: Natalie Cluck, Megan Fischer                                   */
/* Project: CSCE-313 Machine Problem #3                                       */
/*                                                                            */
/* File: ./mp3_part5.cpp                                                      */
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/* Standard Library Includes                                                  */
/* -------------------------------------------------------------------------- */

#include <stdlib.h>
#include <unistd.h>


int main()
{
    
    pid_t childProcess;
    pid_t parentProcess;
    int success;
    
    pid_t success_value = waitpid(-1, &success, 0);
    
    if(fork() == 0) {
        write(1,"World!\n",8);
    }
    else if (success_value != 0) {
        write(1, "Hello ",7);
    }
    
    exit(0);
}

