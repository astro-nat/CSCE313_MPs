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

//char *cmd1[] = "/bin/ls -la", 0";
//char *cmd2[] = { "/usr/bin/tr [a-zA-Z0-9a]", 0 };

int main()
{
    pid_t childpid[2], parentpid[2];
    int nbytes;
    char* buf[50];
    
    pipe(childpid);
    pipe(parentpid);
    
    if (fork() == 0){
        
        dup2(childpid[1], STDOUT_FILENO);
        close(childpid[0]);
        execlp("ls", "ls", "-la", (char *) NULL);
        
        exit(0);
    }
    
    wait(NULL);
    close(childpid[1]);
    
    if (fork() == 0){
        
        dup2(childpid[0], STDIN_FILENO);
        dup2(parentpid[1], STDOUT_FILENO);
        
        close(parentpid[0]);
        
        execlp("tr", "tr", "[a-zA-Z0-9]", "a", (char *) NULL);
        
        exit(0);
    }
    
    wait(NULL);
    close(childpid[0]);
    close(parentpid[1]);
    
    while(true){
        
        nbytes = read(parentpid[0], buf, sizeof(buf));
        write(STDOUT_FILENO, buf, nbytes);
        
        if (sizeof(buf) > nbytes){
            break;
        }
    }
    
    exit(0);
    
    /*
     
     // old stuff
     
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
     */
}

