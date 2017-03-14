/* ------------------------------------------------------------------------- */
/* Developers: Natalie Cluck, Megan Fischer                                  */ 
/* Project: CSCE-313 Machine Problem #4                                      */
/*                                                                           */
/* File: ./shell.cpp                                                         */ 
/* ------------------------------------------------------------------------- */


/* ------------------------------------------------------------------------- */
/* Standard Libaray Includes                                                 */
/* ------------------------------------------------------------------------- */

#include<iostream>
#include<cstdlib>
#include<ctime>
#include<unistd.h>
#include<stdlib.h>
#include<regex>
#include<string>
#include<vector>
#include<stdio.h>
#include<string.h>
#include<string>
#include<sstream>
#include<sys/wait.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include <fstream>
//#include <cerrno>
//#include <fcntl.h>

using namespace std;

/* ------------------------------------------------------------------------- */
/* Global Variables                                                          */
/* ------------------------------------------------------------------------- */

// Put any global variables here
const int MAX_PATH = 1000;

char temp[MAX_PATH];

// Use $PATH ?
string DIR = ( getcwd(temp, MAX_PATH) ? std::string( temp ) : std::string("") );
string PROMPT = "[" + ( DIR + "$ " );

string WHO = "";
string DATE = "";
string TIME = "";

/* User Definable Custom Prompt:
 * 
 * Allows users to define custom prompts using a simple command to change the string.  
 * The following set of macros will be replaced as follows:
 *
 *   - DIR: Current directory 
 *   - WHO: User's name
 *   - DATE: Current date
 *   - TIME: Current time
 */
void update_prompt()
{
    DIR = ( getcwd(temp, MAX_PATH) ? std::string( temp ) : std::string("") );
    PROMPT = "[" + ( DIR + "$ " );
}

int main(int argc, char** argv)
{
    string input;
	while(input != "q") {
        
        string delimiter = " ";
        string token;
        size_t pos = 0;
        vector<string> backgroundProcesses;
        vector<string> commands;
        
        string unix_command;
        string filename;
        
        /* Initialize prompt to default (current directory followed by a colon */
        update_prompt();
        cout << PROMPT;
        
        getline(cin,input);
        
        if(input.find(delimiter) != string::npos){
            while ((pos = input.find(delimiter)) != std::string::npos) {
                token = input.substr(0, pos);
                commands.push_back(token);
                input.erase(0, pos + delimiter.length());
            }
            // last argument not added in loop -> this handles that
            token = input.substr(0, pos);
            commands.push_back(token);
        }
        else {
            // adds argument if there is only one
            commands.push_back(input);
        }
        
        //*  testing * //
        for(auto i : commands) {
            cout << "Command: " << i << endl;
        }
        
        if(commands.size() > 0) {
            // DONE
            if(commands[0] == "cd") {
                if (commands.size() == 1){
                        chdir("/");
                    }
                else {
                    if (chdir(commands[1].c_str()) < 0) {
                        cout << "Directory does not exist!\n";
                    }
                    else {
                        DIR = ( getcwd(temp, MAX_PATH) ? std::string( temp ) : std::string("") );
                    }
                }
            }
            // DONE
            else if (commands[0] == "exit") {
                exit(0);
            }
            // DONE. 10 pts.
            else if (commands[0] == "pwd") {
                char cwd[1024];
                chdir("/path/to/change/directory/to");
                getcwd(cwd, sizeof(cwd));
                cout << cwd << endl;
                PROMPT = "[" + ( DIR + "$ " );
            }
            // DONE. 10 pts.
            else if (commands[0] == "df") {
                int pid2 = fork();
                if (pid2 == 0) {
                    if (commands[1] == "-h") {
                        execl("/bin/df","df", "-h", (char*) NULL);
                    }
                    execl("/bin/df","df", (char*) NULL);
                }
                wait(NULL);
            }
            // DONE
            else if (commands[0] == "ls") {
                int pid = fork();
                if (pid == 0) {
                    // DONE. 10 pts.
                    if (commands[1] == "-la") {
                        if (commands[2] == "-t") {
                            execl("/bin/ls","ls", "-la", "-t", (char*) NULL);
                        }
                        execl("/bin/ls","ls", "-la", (char*) NULL);
                    }
                    // DONE. 10 pts.
                    else if (commands[1] == "-t") {
                        execl("/bin/ls","ls", "-t", (char*) NULL);
                    }
                    int fds[2];
                    pipe(fds);
                    pid_t pid1;
                    pid1 = fork();
                    // DONE. 10 pts.
                    if (commands[1] == "-la" && commands[3] == "grep") {
                            // child process #1
                            if (pid1 == 0) {
                                dup2(fds[1], 1);
                                close(fds[0]);
                                close(fds[1]);
                                execl("/bin/ls","-la",(char*)NULL);
                            }
                            // child process #2
                            else if (pid1 != 0) {
                                dup2(fds[0], 0);
                                close(fds[1]);
                                execl("/bin/grep","temp.tar",(char*)NULL);
                            }
                    }
                    // DONE. 10 pts.
                    else if(commands[2] == "cat") {
                        // child process #1
                        if (pid1 == 0) {
                            dup2(fds[1], 1);
                            close(fds[0]);
                            close(fds[1]);
                            execl("/bin/ls","ls",(char*)NULL);
                        }
                        // child process #2
                        else if (pid1 != 0) {
                            dup2(fds[0], 0);
                            close(fds[1]);
                            execl("/bin/cat","cat",(char*)NULL);
                        }
                    }
                    execl("/bin/ls","ls", (char*) NULL);
                }
                wait(NULL);
                PROMPT = "[" + ( DIR + "$ " );
            }
            else if (commands[0] == "echo") {
                ofstream myfile;
                myfile.open ("temp_shell.txt");
                myfile << "Hello World";
                myfile.close();
                PROMPT = "[" + ( DIR + "$ " );
            }
            else if (commands[0] == "cat") {
                string file_text;
                ifstream infile;
                infile.open ("temp_shell.txt");
                while(!infile.eof()) // To get you all the lines.
                {
                    getline(infile,file_text); // Saves the line in STRING.
                    cout<< file_text << endl; // Prints our STRING.
                }
                infile.close();
                PROMPT = "[" + ( DIR + "$ " );
            }
            
            
            }
            else {
                cout << "Not a valid command." << endl;
                PROMPT = "[" + ( DIR + "$ " );
            }
            
        }
            
            /*
            if(commands[1] == "|") {
                unix_command = commands[0];
            }
            // unix_command AMP
            else if(commands[1] == "&") {
                unix_command = commands[0];
                // backgroundProcesses.push_back(<process id>);
                
            }
            // unix_command REDIRECTION filename
            else if(commands[1] == "<" || "||" || ">") {
                unix_command = commands[0];
            }
            // unix_command
            else if (commands.size() == 1) {
                unix_command = commands[0];
            }
            */
        
        // Check to see if the process is to run in the background or foreground

        /* Remove quotes from beginning and end of tokens */

        /* Replace the string \" with the character '\"' */

        /* Detect command pipes */
        
        // unix_command PIPE unix_command
        
        /* Set up communication pipes */

        /* Detect Redirection */

        /* Execute commands in order */
    }
    
	return 0;
}
