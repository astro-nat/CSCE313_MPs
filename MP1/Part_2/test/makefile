# ---------------------------------------------------------------------------- #
# Developer: Andrew Kirfman, Margaret Baxter                                   #
# Project: CSCE-313 Machine Problem #1                                         #
#                                                                              #
# File: ./MP1/Part_2/Makefile                                                  #
# ---------------------------------------------------------------------------- #

CC=g++
STD=-std=c++11
CFLAGS=

all: main.o linkedlist2.o
	$(CC) $(STD) -o List_2 main.o linkedlist2.o
	
main.o: main.cpp
	$(CC) $(STD) -c main.cpp
	
linked_list2.o: linkedlist2.cpp linkedlist2.h
	$(CC) $(STD) -c linkedlist2.cpp linkedlist2.h
	
clean:
	rm -rf *.o List_2 *.gch
