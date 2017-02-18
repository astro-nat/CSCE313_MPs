/* -------------------------------------------------------------------------- */
/* Developers: Natalie Cluck, Megan Fischer                                   */
/* Project: CSCE-313 Machine Problem #2                                       */
/*                    
/* Implements the command pipeline ”ls -la | tr [a-zA-Z0-9] a”. 
/*  Use any combination of
/* fork, exec, wait, read, and write necessary to create this functionality.
/*  Note: the parent process must be the one to output the data to the console.
/*
/* File: ./mp2_part7.cpp                                                      */
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/* Standard Library Includes                                                  */
/* -------------------------------------------------------------------------- */

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#include <iostream>

char *cmd1[] = { "/bin/ls -la", 0 };
//char *cmd2[] = { "/usr/bin/tr [a-zA-Z0-9a]", 0 };

int main()
{
    
    int fd[2], nbytes;
    //pid_t childpid;
    //pid_t parentpid;
    
    char string[] = "ls -la";
    char readbuffer[80];
    
    pipe(fd);
    
    if(fork() == 0) { // child writes to pipe
        
        close(fd[0]);
        
        dup(fd[1]);
        close(fd[1]);
        
        //execl(cmd1[0],(char*)NULL);
        
        write(fd[1], cmd1[0], strlen(cmd1[0])+1);
        //write(fd[1], cmd2[0], strlen(cmd2[0])+1);
        
        
        exit(0);
    }
    else { // parent reads from pipe
        
        close(fd[1]);
        
        nbytes = read(fd[0], readbuffer, sizeof(readbuffer));
        
        std::cout << readbuffer << std::endl;
        execl(readbuffer, (char*)NULL);
        write(1, readbuffer, nbytes);
        
        //execvp(cmd1[0],cmd1);
        
    }

    exit(0);
}

