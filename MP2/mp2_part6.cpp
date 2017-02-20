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
 #include <sys/types.h>
 #include <cstring>
 #include <iostream>
 
 char *cmd1[] = { "ls", "-la", NULL };
 //for exec each parameter should be a separate string
 
 int main()
 {
 
 int fd[2], nbytes;
 
 //char string[] = "ls -la"; //unused variable
 char readbuffer[2048]; // is a buffer size of 80 enough?
 
 pipe(fd);
 
 pid_t pid = fork();
 
 if(pid == 0) { // child writes to pipe
 
 // open the pipe, call exec here, write output from exec into pipe
 
 dup2(fd[1],1); // stdout goes to fd[1]
 close(fd[0]); // read not needed
 
 execvp(cmd1[0],cmd1); //execute command in child
 
 exit(0);
 }
 else { // parent reads from pipe
 
 // read output from pipe, write to console
 
 close(fd[1]); // write not needed
 
 //read the output of the child to readbuffer using fd[0]
 nbytes = read(fd[0], readbuffer, sizeof(readbuffer));
 
 //std::cout << readbuffer << std::endl;
 //write also outputs readbuffer
 //output readbuffer to STDOUT
 write(1, readbuffer, nbytes);
 }
 
 exit(0);
 }
