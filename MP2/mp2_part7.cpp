/* -------------------------------------------------------------------------- */
/* Developers: Natalie Cluck, Megan Fischer                                   */
/* Project: CSCE-313 Machine Problem #3                                       */
/*                    
/* Implements the command pipeline ”ls -la | tr [a-zA-Z0-9] a”. 
/*  Use any combination of
/* fork, exec, wait, read, and write necessary to create this functionality.
/*  Note: the parent process must be the one to output the data to the console.
/*
/* File: ./mp3_part7.cpp                                                      */
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/* Standard Library Includes                                                  */
/* -------------------------------------------------------------------------- */

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#include <iostream>

char *cmd1[] = { "/bin/ls", "-al", "/", 0 };
char *cmd2[] = { "/usr/bin/tr", "a-z", "A-Z", "a", 0 };

int main()
{
    
    int fd[2], nbytes;
    //pid_t childpid;
    //pid_t parentpid;
    
    char string[] = "ls -la";
    char readbuffer[80];
    
    pipe(fd);
    
    if(fork() == 0) { // child
        
        dup2(fd[0], 0);
        close(fd[1]);
        
        write(fd[1], string, 8);
        
        exit(0);
    }
    else { // parent
        
        dup2(fd[1], 1);
        close(fd[0]);
        nbytes = read(fd[0], readbuffer, sizeof(readbuffer));
        
        char* const argList[] = {"la -la", NULL};
        execvp(cmd1[0], cmd1);
    
    }

    exit(0);
}

