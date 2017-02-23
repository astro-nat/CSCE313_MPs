#!/usr/bin/env python

# --------------------------------------------------------------------------- #
# Developers: Natalie Cluck, Megan Fischer                                    #
# Project: CSCE-313 Machine Problem #3                                        #
#                                                                             #
# File: ./student/proctest.py                                                 #
# --------------------------------------------------------------------------- #


# --------------------------------------------------------------------------- #
# Standard Library Includes                                                   #
# --------------------------------------------------------------------------- #

import sys
import re
from subprocess import check_output, CalledProcessError
import subprocess


"""
Note to students: Your program must be written using the provided class
template below.  Functions that require your implementation are marked
with "Work needed here" in their method docstrings.

Be sure to delete all of these extraneous comments before submitting your
code for grading.  Also, delete all extra 'pass' statements.  They are
noop instructions and only there because Python does not like empty functions.
"""

def getcommand(pid,command):
    
    return ("ps -p " + pid + " -o " + command + "=\n")

class Proctest(object):
    """
    Object to contain process data and getter functions
    """
    
    def __init__(self, pid):
        

        # Read all data from pertinent files and save as class members
        
        # PID
        try:
        	pid = pid.strip()
        	self.pid = pid
        except CalledProcessError as e:
        	self.pid = e.output
        
        # PPID
        try:
            self.ppid = check_output(getcommand(pid,"ppid"),shell=True)
        except CalledProcessError as e:
            self.ppid = e.output

        # EUID
        try:
            self.euid = check_output(getcommand(pid,"euid"),shell=True)
        except CalledProcessError as e:
            self.euid = e.output
    
    	# EGID
    	try:
            self.egid = check_output(getcommand(pid,"egid"),shell=True)
        except CalledProcessError as e:
            self.egid = e.output
    
    	# RUID
        try:
            self.ruid = check_output(getcommand(pid,"ruid"),shell=True)
        except CalledProcessError as e:
            self.ruid = e.output
        
        # RGID
        try:
            self.rgid = check_output(getcommand(pid,"rgid"),shell=True)
        except CalledProcessError as e:
            self.rgid = e.output
        
        # FSUID
        try:
            self.fsuid = check_output(getcommand(pid,"fsuid"),shell=True)
        except CalledProcessError as e:
            self.fsuid = e.output
        
        # FSGID
        try:
            self.fsgid = check_output(getcommand(pid,"fsgid"),shell=True)
        except CalledProcessError as e:
            self.fsgid = e.output
        
        # R, S, D, T, Z, X
        try:
            self.state = check_output(getcommand(pid,"state"),shell=True)
        except CalledProcessError as e:
            self.state = e.output
        
        self.thread_count = ""
        self.priority = ""
        self.niceness = ""
        self.stime = ""
        self.utime = ""
        self.cstime = ""
        self.cutime = ""
        self.startcode = ""
        self.endcode = ""
        self.esp = ""
        self.eip = ""
        self.files = ""
        self.voluntary_context_switches = ""
        self.nonvoluntary_context_switches = ""
        self.last_cpu = ""
        self.allowed_cpus = ""
        self.memory_map = []
        

        pid = pid;
        ppid = "12345";
        euid = "23456";
        
        """
        Read all data from pertinent files and save as class members

        Work needed here!
        """

        pass

    def getpid(self):
        
        return self.pid

        
        """
        Returns the process id

        Work needed here!
        """


    def getppid(self):
        
        return self.ppid
    

    def geteuid(self):
        
        return euid
        
        """
        Returns the process's effective user ID

        Work needed here!
        """


    def getegid(self):
        
        return self.egid


    def getruid(self):
    
        return self.ruid


    def getrgid(self):
    
        return self.rgid

    def getfsuid(self):
    
        return self.fsuid


    def getfsgid(self):
    
        return self.fsgid


    def getstate(self):
    
        return self.state


    def getthread_count(self):
    
        return self.thread_count


    def getpriority(self):
    
        return self.priority


    def getniceness(self):
    
        return self.niceness


    def getstime(self):
    
        return self.stime


    def getutime(self):
    
        return self.utime


    def getcstime(self):
    
        return self.cstime


    def getcutime(self):
    
        return self.cutime


    def getstartcode(self):
    
        return self.startcode


    def getendcode(self):
    
        return self.endcode


    def getesp(self):
    
        return self.esp


    def geteip(self):
    
        return self.eip


    def getfiles(self):
    
        return self.files


    def getvoluntary_context_switches(self):
    
        return self.voluntary_context_switches

    def getnonvoluntary_context_switches(self):
    
        return self.nonvoluntary_context_switches


    def getlast_cpu(self):
    
        return self.last_cpu


    def getallowed_cpus(self):
    
        return self.allowed_cpus


    def getmemory_map(self):

        # returns array
        return self.memory_map

def main():

    # Read in PID
    sys.stdout.write("Enter the PID of a process: ")
    sys.stdout.flush()
    process_pid = sys.stdin.readline()

    process_data = Proctest(process_pid)

    # Start printing out values
    print ""
    print "Process Information:"
    print "  1) Identifiers"
    print "     PID: %s" % process_data.getpid()
    print "     PPID: %s" % process_data.getppid()
    print "     EUID: %s" % process_data.geteuid()
    print "     EGID: %s" % process_data.getegid()
    print "     RUID: %s" % process_data.getruid()
    print "     RGID: %s" % process_data.getrgid()
    print "     FSUID: %s" % process_data.getfsuid()
    print "     FSGID: %s" % process_data.getfsgid()
    print ""
    print "  2) State"
    print "     State: %s" % process_data.getstate()
    print ""
    print "  3) Thread Information"
    print "     Thread Count: %s" % process_data.getthread_count()
    print ""
    print "  4) Priority"
    print "     Priority Number: %s" % process_data.getpriority()
    print "     Niceness Value: %s" % process_data.getniceness()
    print ""
    print "  5) Time Information"
    print "     stime: %s" % process_data.getstime()
    print "     utime: %s" % process_data.getutime()
    print "     cstime: %s" % process_data.getcstime()
    print "     cutime: %s" % process_data.getcutime()
    print ""
    print "  6) Address Space"
    print "     Startcode: %s" % process_data.getstartcode()
    print "     Endcode: %s" % process_data.getendcode()
    print "     ESP: %s" % process_data.getesp()
    print "     EIP: %s" % process_data.geteip()
    print ""
    print "  7) Resources"
    print "     File Handles: %s" % process_data.getfiles()
    print "     Voluntary Context Switches: %s" % process_data.getvoluntary_context_switches()
    print "     Nonvoluntary Context Switches: %s" % process_data.getnonvoluntary_context_switches()
    print ""
    print "  8) Processor"
    print "     Last Processor: %s" % process_data.getlast_cpu()
    print "     Allowed Cores: %s" % process_data.getallowed_cpus()
    print ""
    print "  9) Memory Map"
    temp_mem_array = process_data.getmemory_map()
    for line in temp_mem_array:
        print "     %s" % line


if __name__ == "__main__":
    main()

