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
string DIR = ( getcwd(temp, MAX_PATH) ? std::string( temp ) : std::string("") );
string PROMPT = ( DIR + "$ " );
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
    
}

int main(int argc, char** argv)
{
    string input;
	while(input != "q") {
        
        /* Parse command line arguments */
        vector<string> commands;
        string delimiter = " ";
        size_t pos = 0;
        std::string token;
        
        /* Initialize prompt to default (current directory followed by a colon */
        update_prompt();
        cout << DIR << "$ ";
        getline(cin,input);
        
        // !! get this to work properly. Doesn't get last argument. !!
        /*
        if(input.find(delimiter) != string::npos ){
            while ((pos = input.find(delimiter)) != std::string::npos) {
                token = input.substr(0, pos);
                commands.push_back(token);
                input.erase(0, pos + delimiter.length());
            }
        }
        else {
            commands.push_back(input);
        }
        */
        
        // testing //
        commands.push_back("exit");
        commands.push_back(" ");
        
        for(auto i : commands) {
            cout << "Command: " << i << endl;
        }
         
        
        /* Vector to maintain background processes */
        vector<string> backgroundProcesses;

        
        /* Tokenize input command */

        // The tokenizer may make empty tokens, eliminate them
        // commands.erase(std::remove(commands.begin(), commands.end(), " "), commands.end());

        // Account for special commands
        if(commands[0] == "cd") {
            cout << "SPECIAL" << endl;
            DIR = commands[1];
        }
        else if (commands[0] == "exit") {
            exit(0);
        }

        // Check to see if the process is to run in the background or foreground

        /* Remove quotes from beginning and end of tokens */

        /* Replace the string \" with the character '\"' */

        /* Detect command pipes */
        
        // unix_command PIPE unix_command
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

        /* Set up communication pipes */

        /* Detect Redirection */

        /* Execute commands in order */

    }
	return 0;
}
