#---------------------------------------------------------------------------- #
# Developer: Andrew Kirfman, Margaret Baxter                                   #
# Project: CSCE-313 Machine Problem #1                                         #
#                                                                              #
# File: ./MP1/Makefile                                                         #
# ---------------------------------------------------------------------------- #

CC=g++
STD=-std=c++11
CFLAGS=

all: main.o linkedlist.o
	$(CC) $(STD) -o List_1 main.o linkedlist.o
	
main.o: main.cpp
	$(CC) $(STD) -c main.cpp
	
linkedlist.o: linkedlist.cpp linkedlist.h
	$(CC) $(STD) -c linkedlist.cpp linkedlist.h
	
clean:
	rm -rf *o List_1 *.gch
