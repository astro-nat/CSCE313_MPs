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
    PROMPT = "[" + ( DIR + "$ " );
}

int main(int argc, char** argv)
{
    string input;
	while(input != "q") {
        
        /* Parse command line arguments */
        
        string delimiter = " ";
        string token;
        size_t pos = 0;
        vector<string> backgroundProcesses;
        vector<string> commands;
        
        /* Initialize prompt to default (current directory followed by a colon */
        update_prompt();
        cout << PROMPT;
        getline(cin,input);
        
        // !! get this to work properly. Doesn't get last argument. !!
        
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
        //commands.push_back("ls");
        //commands.push_back("");
        for(auto i : commands) {
            cout << "Command: " << i << endl;
        }
        
        /* Tokenize input command */

        // The tokenizer may make empty tokens, eliminate them
        // commands.erase(std::remove(commands.begin(), commands.end(), " "), commands.end());

        // Account for special commands
        if(commands.size() > 0) {
            if(commands[0] == "cd") {
                cout << "SPECIAL" << endl;
                //char *directory = "/tmp";
                //int ret;
                //ret = chdir (directory);
                //if (ret == 0) {
                    //DIR = ( getcwd(temp, MAX_PATH) ? std::string( temp ) : std::string("") );
                    //PROMPT = "[" + ( DIR + "$ " );
                //}
                //else{
                    //cout << "Not a vaild directory." << endl;
                //}
                // TO DO: check for valid directory
                DIR = commands[1];
		// use "change dir" function
            }
            else if (commands[0] == "exit") {
                exit(0);
            }
            else if (commands[0] == "ls") {
                int pid = fork();
                if (pid == 0) {
                    if (commands[1] == "-la") {
                        if (commands[2] == "-t") {
                            execl("/bin/ls","ls", "-la", "-t", (char*) NULL);
                        }
                    }
                    if (commands[1] == "-t") {
                        execl("/bin/ls","ls", "-t", (char*) NULL);
                    }
                    execl("/bin/ls","ls", (char*) NULL);
                }
                wait(NULL);
                PROMPT = "[" + ( DIR + "$ " );
            }
            else if (commands[0] == "pwd") {
                char cwd[1024];
                chdir("/path/to/change/directory/to");
                getcwd(cwd, sizeof(cwd));
                cout << cwd << endl;
            }
            else if (commands[0] == "df") {
                int pid2 = fork();
                if (pid2 == 0) {
                    if (commands[1] == "-h") {
                        execl("/bin/df","df", "-h", (char*) NULL);
                    }
                    execl("/bin/df","df", (char*) NULL);
                }
                wait(NULL);
                PROMPT = "[" + ( DIR + "$ " );
            }
            else if (commands[0] == "cat") {
                int pid2 = fork();
                if (pid2 == 0) {
                    execl("/bin/df","df", (char*) NULL);
                }
                wait(NULL);
                PROMPT = "[" + ( DIR + "$ " );
            }
            if(commands[1] == "|") {
                
            }
            // unix_command AMP
            if(commands[1] == "&") {
                
                // backgroundProcesses.push_back(<process id>);
                
            }
            // unix_command REDIRECTION filename
            if(commands[1] == "<" || "||" || ">") {
                
            }
            // unix_command
            else if (commands.size() == 1) {
                
            }
            
        }

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
