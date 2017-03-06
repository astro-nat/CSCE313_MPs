/* ------------------------------------------------------------------------- */
/* Developer: Andrew Kirfman                                                 */ 
/* Project: CSCE-313 Machine Problem #4                                              */
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

/* ------------------------------------------------------------------------- */
/* Global Variables                                                          */
/* ------------------------------------------------------------------------- */

// Put any global variables here

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
	/* Parse command line arguments */

	/* Initialize prompt to default (current directory followed by a colon */

	/* Vector to maintain background processes */

	/* Tokenize input command */

	// The tokenizer may make empty tokens, eliminate them

	// Account for special commands

	// Check to see if the process is to run in the background or foreground

	/* Remove quotes from beginning and end of tokens */

	/* Replace the string \" with the character '\"' */

	/* Detect command pipes */

	/* Set up communication pipes */

	/* Detect Redirection */

	/* Execute commands in order */

	return 0;
}