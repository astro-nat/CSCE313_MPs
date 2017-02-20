/* -------------------------------------------------------------------------- */
/* Developers: Natalie Cluck, Megan Fischer                                   */
/* Project: CSCE-313 Machine Problem #2                                       */
/*                                                                            */
/* File: ./mp3_part2.cpp                                                      */
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/* Standard Library Includes                                                  */
/* -------------------------------------------------------------------------- */

#include <stdlib.h>
#include <unistd.h>


int main()
{
    
    pid_t childProcess = fork();
    int success;
    
    pid_t success_value = waitpid(-1, &success, 0);
    
    if(childProcess == 0) {
        write(1, "Hello",6);
        
    }
    else if (success_value != 0) {
        write(1,"World!",8);
    }
    
    exit(0);
}

