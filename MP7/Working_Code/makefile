# makefile

all: dataserver client 

reqchannel.o: reqchannel.h reqchannel.cpp
	g++ -std=c++11 -c -g reqchannel.cpp

bounded_buffer.o: bounded_buffer.h bounded_buffer.cpp
	g++ -std=c++11 -c -g bounded_buffer.cpp
	
semaphore.o: semaphore.h semaphore.cpp
	g++ -std=c++11 -c -g semaphore.cpp
	
dataserver: dataserver.cpp reqchannel.o 
	g++ -std=c++11 -g -o dataserver dataserver.cpp reqchannel.o -lpthread


client: client_MP7.cpp reqchannel.o semaphore.o bounded_buffer.o
	g++ -std=c++11 -g -o client client_MP7.cpp reqchannel.o semaphore.o bounded_buffer.o -lpthread

clean:
	rm *.o fifo* dataserver client output*