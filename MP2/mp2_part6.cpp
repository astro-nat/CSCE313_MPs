/* -------------------------------------------------------------------------- */
/* Developers: Natalie Cluck, Megan Fischer                                   */
/* Project: CSCE-313 Machine Problem #2                                       */
/*                                                                            */
/* A program named mp2_part6.cpp which starts the command ”ls -la” using
 a fork() followed by an exec() (any of the exec functions will work).
 Use a UNIX pipe system call to send the output of ls -la back to the parent,
 read it using the read() function, and then write it to the console using the
 write() function. Note: the pipe will not work if you do not close and/or
 redirect the correct file descriptors. It’s up to you to figure out which
 ones those need to be.                                                       */

/*                                                                            */
/* File: ./mp2_part6.cpp                                                      */
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/* Standard Library Includes                                                  */
/* -------------------------------------------------------------------------- */
/*
 #include <stdlib.h>
 #include <unistd.h>
 #include <sys/types.h>
 
 #include <iostream>
 
 char *cmd1[] = { "/bin/ls -la", 0 };
 
 int main()
 {
 
 int fd[2], nbytes;
 //pid_t childpid;
 //pid_t parentpid;
 
 char string[] = "ls -la";
 char readbuffer[80];
 
 pipe(fd);
 
 if(fork() == 0) { // child writes to pipe
 
 // open the pipe, call exec here, write output from exec into pipe
 
 close(fd[0]); // read not needed
 
 dup(fd[1]);
 close(fd[1]);
 
 //execl(cmd1[0],(char*)NULL);
 
 write(fd[1], cmd1[0], strlen(cmd1[0])+1);
 //write(fd[1], cmd2[0], strlen(cmd2[0])+1);
 
 
 exit(0);
 }
 else { // parent reads from pipe
 
 // read output from pipe, write to console
 
 close(fd[1]); // write not needed
 
 nbytes = read(fd[0], readbuffer, sizeof(readbuffer));
 
 std::cout << readbuffer << std::endl;
 execl(readbuffer, (char*)NULL);
 
 close(fd[0]);
 write(1, readbuffer, nbytes);
 
 //execvp(cmd1[0],cmd1);
 
 }
 
 exit(0);
 }
 */






/* -------------------------------------------------------------------------- */
/* Developers: Natalie Cluck, Megan Fischer                                   */
/* Project: CSCE-313 Machine Problem #2                                       */
/*                                                                            */
/* A program named mp2_part6.cpp which starts the command ”ls -la” using
 a fork() followed by an exec() (any of the exec functions will work).
 Use a UNIX pipe system call to send the output of ls -la back to the parent,
 read it using the read() function, and then write it to the console using the
 write() function. Note: the pipe will not work if you do not close and/or
 redirect the correct file descriptors. It’s up to you to figure out which
 ones those need to be.                                                       */

/*                                                                            */
/* File: ./mp2_part6.cpp                                                      */
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/* Standard Library Includes                                                  */
/* -------------------------------------------------------------------------- */

#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <sys/types.h>


//char *cmd1[] = { "/bin/ls -la", 0 };

int main()
{
    
    std::cout << "0" << std::endl;
    
    int fd[2], nbytes;
    
    char readbuffer[80];
    
    pipe(fd);
    
    pid_t pid = fork();
    
    if(pid == 0) {
        
        std::cout << "2" << std::endl;
        
        close(fd[1]);
        dup2(fd[0], 0);
        execl("/bin/ls","ls","-la",(char*)NULL);
        
        
    }
    else {
        
        std::cout << "1" << std::endl;
        
        close(fd[0]);
        
        while ((nbytes = read(fd[1], readbuffer, sizeof(readbuffer))) > 0){
            //std::cout << "nybytes: " << nbytes << std::endl;
            write(fd[1], readbuffer, nbytes);
            //std::cout << readbuffer << std::endl;
        }
        
        //std::cout << readbuffer << std::endl;
        close(fd[1]);
        
        
    }
    
    exit(0);
}
