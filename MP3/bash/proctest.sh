#!/bin/bash

# --------------------------------------------------------------------------- #
# Developer: Andrew Kirfman                                                   #
# Project: CSCE-313 Machine Problem #3                                        #
#                                                                             #
# File: ./proctest.sh                                                         #
# --------------------------------------------------------------------------- #

# Forward declare the PID variable
PID=""

# Need to filter program so that only the functions are defined on a test
TESTING=false
if [ $# -gt 0 ]
then
    TESTING=true
fi

function getpid()
{

}

function getppid()
{

}

function geteuid()
{

}

function getegid()
{

}

function getruid()
{
    
}

function getrgid()
{

}

function getfsuid()
{

}

function getfsgid()
{

}

function getstate()
{

}

function getthread_count()
{
    
}

function getpriority()
{

}

function getniceness()
{

}

function getstime()
{

}

function getutime()
{

}

function getcstime()
{

}

function getcutime()
{

}

function getstartcode()
{

}

function getendcode()
{

}

function getesp()
{

}

function geteip()
{ 

}

function getfiles()
{

}

function getvoluntary_context_switches()
{

}

function getnonvoluntary_context_switches()
{

}

function getlast_cpu()
{

}

function getallowed_cpus()
{

}

function getmemory_map()
{

}

# Main program here
if [ $TESTING == false ]
then
    # Read in the value of the pid that the user would like to examine.  
    printf "Enter the pid of a process: " 
    read PID

    # If the value entered is not an integer, try again.  
    while ! [ "$PID" -eq "$PID" ] 2>/dev/null
    do
        printf "[ERROR]: Number was not a valid integer.  Try again: " 
        read PID
    done

    # Search the system to make sure that the process exists.  
    ls "/proc/$PID" > /dev/null
    if [ $? == 1 ]
    then
        echo "[ERROR]: A Process with the given ID does not exist on this system! - Exiting!"
        exit 1
    fi

    printf "\nProcess Information: " 
    
    printf "\n1) Identifiers\n"
    printf "   PID:   $(getpid) \n"
    printf "   PPID:  $(getppid) \n"
    printf "   EUID:  $(geteuid) \n"
    printf "   EGID:  $(getegid) \n"
    printf "   RUID:  $(getruid) \n"
    printf "   RGID:  $(getrgid) \n"
    printf "   FSUID: $(getfsuid) \n"
    printf "   FSGID: $(getfsgid) \n"
    
    printf "\n2) State: \n"
    printf "   State: $(getstate)\n"
    
    printf "\n3) Thread Information: \n"
    printf "   Thread Count: $(getthread_count) \n"
    
    printf "\n4) Priority: \n"
    printf "   Priority Number: $(getpriority) \n"
    printf "   Niceness Value:  $(getniceness) \n"
    
    printf "\n5) Time Information: \n"
    printf "   stime:  $(getstime) \n"
    printf "   utime:  $(getutime) \n"
    printf "   cstime: $(getcstime) \n"
    printf "   cutime: $(getcutime) \n"
    
    printf "\n6) Address Space: \n"
    printf "   Startcode: $(getstartcode) \n"
    printf "   Endcode:   $(getendcode) \n"
    printf "   ESP:       $(getesp) \n"
    printf "   EIP:       $(geteip) \n"
    
    printf "\n7) Resourses: \n"
    printf "   File Handles: $(getfiles) \n"
    printf "   Voluntary Context Switches: $(getvoluntary_context_switches)\n"
    printf "   Involuntary Context Switches: $(getnonvoluntary_context_switches)\n"
    
    printf "\n8) Processors: \n"
    printf "   Last processor: $(getlast_cpu) \n"
    printf "   Allowed Cores:  $(getallowed_cpus) \n"
        
    printf "\n9) Memory Map: \n"
    printf "$(getmemory_map) \n"

    exit 0
fi
