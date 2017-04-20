/*
    File: client_MP6.cpp

    Author: J. Higginbotham
    Department of Computer Science
    Texas A&M University
    Date  : 2016/05/21

    Based on original code by: Dr. R. Bettati, PhD
    Department of Computer Science
    Texas A&M University
    Date  : 2013/01/31

    MP6 for Dr. //Tyagi's
    Ahmed's sections of CSCE 313.
 */

/*--------------------------------------------------------------------------*/
/* DEFINES */
/*--------------------------------------------------------------------------*/

    /* -- (none) -- */
    /* -- This might be a good place to put the size of
        of the patient response buffers -- */

/*--------------------------------------------------------------------------*/
/* INCLUDES */
/*
    As in MP7 no additional includes are required
    to complete the assignment, but you're welcome to use
    any that you think would help.
*/
/*--------------------------------------------------------------------------*/

#include <queue>
#include <cassert>
#include <cstring>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>
#include <string>
#include <sstream>
#include <sys/time.h>
#include <assert.h>
#include <fstream>
#include <numeric>
#include <vector>
#include "bounded_buffer.h"
#include "reqchannel.h"
#include <signal.h>
#include <stdio.h>


/*--------------------------------------------------------------------------*/
/* DATA STRUCTURES */
/*--------------------------------------------------------------------------*/

/*
    All *_params structs are optional,
    but they might help.
 */
 
 /*
struct request_thread_params {
    
};

struct worker_thread_params {
    
};

struct stat_thread_params {
    
};
*/

struct PARAMS {

	int n; //total number of requests per person
	int w;
	string name; //name of person sending requests
	void* arg; //not sure what this is
	std::vector<RequestChannel*> work_chan_vector;
	RequestChannel* work_chan;
	bounded_buffer* request_buff;
	std::vector<std::vector<int>*> count_vectors = std::vector<std::vector<int>*>(3); // 0. john, 1. jane, 2. joe
	int response_index;
	//std::vector<bounded_buffer*> *r_buffers; // 0. john, 1. jane, 2. joe
	
	bounded_buffer *john_response;
	bounded_buffer *jane_response;
	bounded_buffer *joe_response;
	
	std::vector<int> *john_count;
	std::vector<int> *jane_count;
	std::vector<int> *joe_count;
	
	pthread_mutex_t* l;
	std::string results;

};


/*
    This class can be used to write to standard output
    in a multithreaded environment. It's primary purpose
    is printing debug messages while multiple threads
    are in execution.
 */
class atomic_standard_output {
    pthread_mutex_t console_lock;
public:
    atomic_standard_output() { pthread_mutex_init(&console_lock, NULL); }
    ~atomic_standard_output() { pthread_mutex_destroy(&console_lock); }
    void print(std::string s){
        pthread_mutex_lock(&console_lock);
        std::cout << s << std::endl;
        pthread_mutex_unlock(&console_lock);
    }
};

atomic_standard_output threadsafe_standard_output;

/*--------------------------------------------------------------------------*/
/* CONSTANTS */
/*--------------------------------------------------------------------------*/

    /* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* HELPER FUNCTIONS */
/*--------------------------------------------------------------------------*/

std::string make_histogram(std::string name, std::vector<int> *data) {
    std::string results = "Frequency count for " + name + ":\n";
    for(int i = 0; i < data->size(); ++i) {
        results += std::to_string(i * 10) + "-" + std::to_string((i * 10) + 9) + ": " + std::to_string(data->at(i)) + "\n";
    }
    return results;
}


void* request_thread_function(void* arg) {
	
	//printf("[%s] %d\n", __FUNCTION__, __LINE__);
	PARAMS pr = *(PARAMS *)arg;
	
	
	for(int i = 0; i < pr.n; i++)  {
		//printf("[%s] %d\n", __FUNCTION__, __LINE__);
		(*pr.request_buff).push(pr.name);
		//cout << "pushed for: " << pr.name << endl;
	}   

	//cout << "finished reqests for: " << pr.name << endl;
	
}

/*
void* quit_function(void * arg) {
	PARAMS pr = *(PARAMS *) arg;
	for(int i = 0; i < pr.w; ++i) { //push quits onto request_buffer
		(*pr.request_buff).push("quit");
	}
	//printf("quit thread done\n");
	//printf("[%s] %d\n", __FUNCTION__, __LINE__);
}
*/

void* worker_thread_function(void* arg) {
	
	//printf("entered worker thread function\n");

	//printf("[%s] %d\n", __FUNCTION__, __LINE__);
	
	PARAMS p = *(PARAMS*)arg;
	
	//printf("[%s] %d\n", __FUNCTION__, __LINE__);
	
	
	std::vector<RequestChannel*> channels = p.work_chan_vector; //vector of all our work channels
	std::vector<int> read_descriptors(p.w, 0); //contains all file descriptors for our request channels
	std:vector<int> name_number(p.w, 0); //used to associate file descriptors with the person sending the request
										 // 0 for jane request, 1 for john request, 2 for joe request

	fd_set read_fds; //fd_set with the read_fds of each channel
	int retval;
	// FD_ZERO(read_fds);

	//printf("Channel size = %d\n", channels.size());
	for(int i = 0; i < channels.size(); i++)  {
		int temp_fd = channels[i]->read_fd();
		read_descriptors[i] = temp_fd;
	}
	
	//printf("[%s] %d\n", __FUNCTION__, __LINE__);
	
	//send 1 request (popped from the req buffer) through each channel using cwrite()
	for(int i = 0; i < channels.size(); i++)  {

		std::string request = (*(p.request_buff)).pop();
		
		//cout << "popped: " << request << endl;
		
		if(request == "data Jane Smith")  {
			name_number[i] = 0;
		}
		else if(request == "data John Smith")  {
			name_number[i] = 1;
		}
		else if(request == "data Joe Smith")  {
			name_number[i] = 2;
		}
		else  {
			printf("Data was not recognized\n");
			exit;
		}
		channels[i]->cwrite(request);
	}
	
	int sent_requests = p.w;
	int recieved_requests = 0;
	
	//printf("[%s] %d\n", __FUNCTION__, __LINE__);
	
    //retrieve data from the buffer and send them to the server and receive reply
	while(recieved_requests < (3 * p.n)) {
		
		//printf("[%s] %d\n", __FUNCTION__, __LINE__);
		FD_ZERO(&read_fds);
		for(int i = 0; i < read_descriptors.size(); i++)  {
			FD_SET(read_descriptors[i], &read_fds); //watch a file to see when it has input to read
		}
		
		//get max
		int temp_max = read_descriptors[0];
		for(int i = 1; i < read_descriptors.size(); i++)  {
			if(read_descriptors[i] > temp_max)	temp_max = read_descriptors[i];
		}
		
		fd_set temp_set = read_fds;
		retval = select(temp_max + 1, &temp_set, NULL, NULL, NULL);
	 
		//printf("[%s] %d\n", __FUNCTION__, __LINE__);
		//use name_number and location of channel in vector to determine what persons data we have
		std::string resp;
		std::string next_req;
		
		for(int i = 0; i < read_descriptors.size(); i++){
			//printf("[%s] %d\n", __FUNCTION__, __LINE__);
			if(FD_ISSET(read_descriptors[i], &read_fds)){ //if ready to read from channel i
				//printf("[%s] %d\n", __FUNCTION__, __LINE__);
				resp = channels[i]->cread();
				
				recieved_requests += 1;
				
				if(name_number[i] == 0){ //Jane
					(*p.jane_response).push(resp);
				}
				else if(name_number[i] == 1){ //John
					(*p.john_response).push(resp);
				}
				else if(name_number[i] == 2){ //Joe
					(*p.joe_response).push(resp);
				}
				else printf("ERROR :(");
				//printf("[%s] %d\n", __FUNCTION__, __LINE__);
				if(sent_requests < 3*(p.n))  {
					
					//printf("[%s] %d\n", __FUNCTION__, __LINE__);
					
					next_req = (*(p.request_buff)).pop();
					
					//cout << "popped: " << next_req << endl;
					
					//printf("[%s] %d\n", __FUNCTION__, __LINE__);
					
					channels[i]->cwrite(next_req);
					
					sent_requests += 1;
					
					//printf("[%s] %d\n", __FUNCTION__, __LINE__);
					
					if(next_req == "data Jane Smith")  {
						name_number[i] = 0; //sent request to channel i for jane
					}
					else if(next_req == "data John Smith")  {
						name_number[i] = 1; //sent request to channel i for john
					}
					else if(next_req == "data Joe Smith")  {
						name_number[i] = 2; //sent request to channel i for joe
					}
					else  {
						printf("Data was not recognized\n");
						exit;
					}
					//cout << "sent requests: " << sent_requests << " limit: " << 3*(p.n) << endl;
				}
				//printf("[%s] %d\n", __FUNCTION__, __LINE__);
			}
		}
		//printf("[%s] %d\n", __FUNCTION__, __LINE__);
    } 

	//printf("[%s] %d\n", __FUNCTION__, __LINE__);

	//PARAMS pr = *(PARAMS *) arg;
	for(int i = 0; i < channels.size(); ++i) { //push quits onto request_buffer
		//usleep(10000);
		channels[i]->send_request("quit");
		//usleep(10000);
	}
	
}

void* stat_thread_function(void* arg) {
	
	//printf("entered stat thread function\n");

	PARAMS* p = (PARAMS*)arg;
	//printf("[%s] %d\n", __FUNCTION__, __LINE__);
	int k = 0;
	while(true){
		if(p->response_index == 0)  {
			//printf("[%s] %d\n", __FUNCTION__, __LINE__);
			std::string response = (*(p->john_response)).pop();
			(*(p->john_count)).at(stoi(response) / 10) += 1;			
		}
		else if(p->response_index == 1)  {
			//printf("[%s] %d\n", __FUNCTION__, __LINE__);
			std::string response = (*(p->jane_response)).pop();
			(*(p->jane_count)).at(stoi(response) / 10) += 1;			
		}
		else{
			//printf("[%s] %d\n", __FUNCTION__, __LINE__);
			std::string response = (*(p->joe_response)).pop();
			(*(p->joe_count)).at(stoi(response) / 10) += 1;			
		}
		++k;
		if(k > (p->n)-1)  {
			//printf("[%s] %d\n", __FUNCTION__, __LINE__);
			break;

		} 
		p->results = make_histogram(p->name, p->count_vectors[p->response_index]);
	}
    
}


/*--------------------------------------------------------------------------*/
/* MAIN FUNCTION */
/*--------------------------------------------------------------------------*/

int main(int argc, char * argv[]) {

    int n = 10; //default number of requests per "patient"
    int b = 50; //default size of request_buffer
    int w = 10; //default number of requet channels handled by event handler
    bool USE_ALTERNATE_FILE_OUTPUT = false;
    int opt = 0;
    while ((opt = getopt(argc, argv, "n:b:w:m:h")) != -1) {
        switch (opt) {
            case 'n':
                n = atoi(optarg);
                break;
            case 'b':
                b = atoi(optarg);
                break;
            case 'w':
                w = atoi(optarg);
                break;
            case 'm':
                if(atoi(optarg) == 2) USE_ALTERNATE_FILE_OUTPUT = true;
                break;
            case 'h':
            default:
                std::cout << "This program can be invoked with the following flags:" << std::endl;
                std::cout << "-n [int]: number of requests per patient" << std::endl;
                std::cout << "-b [int]: size of request buffer" << std::endl;
                std::cout << "-w [int]: number of worker threads" << std::endl;
                std::cout << "-m 2: use output2.txt instead of output.txt for all file output" << std::endl;
                std::cout << "-h: print this message and quit" << std::endl;
                std::cout << "Example: ./client_solution -n 10000 -b 50 -w 120 -m 2" << std::endl;
                std::cout << "If a given flag is not used, a default value will be given" << std::endl;
                std::cout << "to its corresponding variable. If an illegal option is detected," << std::endl;
                std::cout << "behavior is the same as using the -h flag." << std::endl;
                exit(0);
        }
    }
    
    int pid = fork();
    if(pid == 0){
        struct timeval start_time;
        struct timeval finish_time;
        int64_t start_usecs;
        int64_t finish_usecs;
        ofstream ofs;
        if(USE_ALTERNATE_FILE_OUTPUT) ofs.open("output2.txt", ios::out | ios::app);
        else ofs.open("output.txt", ios::out | ios::app);
        
        std::cout << "n == " << n << std::endl;
        std::cout << "b == " << b << std::endl;
        std::cout << "w == " << w << std::endl;
        
        std::cout << "CLIENT STARTED:" << std::endl;
        std::cout << "Establishing control channel... " << std::flush;
        RequestChannel *chan = new RequestChannel("control", RequestChannel::CLIENT_SIDE);
        std::cout << "done." << std::endl;
        
	 
		//initialize lock and necessary buffers
		pthread_mutex_t lock;
		bounded_buffer request_buff(b); //b is max size of the request buffer
		std::vector<int> john_frequency_count(10, 0);
		std::vector<int> jane_frequency_count(10, 0);
		std::vector<int> joe_frequency_count(10, 0);

		bounded_buffer john_response(200); //"patient response buffers can be of an arbitrary fixed size"
		bounded_buffer jane_response(200);
		bounded_buffer joe_response(200);			 
		 
        //start timer
		gettimeofday(&start_time, NULL);
		
		//create all our threads
		pthread_mutex_init(&lock, NULL);
		fflush(NULL);		 
		pthread_t all_threads[3+1+3+1]; //3 request threads, 1 worker thread, 3 statistics threads, 1 quit thread (all in parallel)
										//we aren't currently using quit thread
		//printf("[%s] %d\n", __FUNCTION__, __LINE__);

		
		///////////////////////////////
		// Deal WIth Request Threads //
		///////////////////////////////
		string John_l = "data John Smith";
		string Jane_l = "data Jane Smith";		
		string Joe_l = "data Joe Smith";
		
		PARAMS p2;
		p2.n = n;
		p2.w = w;
		p2.name = Jane_l;
		p2.request_buff = &request_buff;
		p2.l = &lock;
		PARAMS* p2_ptr = &p2;
		pthread_create(&all_threads[0], NULL, &request_thread_function, p2_ptr);

		PARAMS p3;
		p3.n = n;
		p3.w = w;
		p3.name = Joe_l;
		p3.request_buff = &request_buff;
		p3.l = &lock;
		PARAMS* p3_ptr = &p3;
		pthread_create(&all_threads[2], NULL, &request_thread_function, p3_ptr);
		
		PARAMS p1;
		p1.n = n;
		p1.w = w;
		p1.name = John_l;
		p1.request_buff = &request_buff;
		p1.l = &lock;
		PARAMS* p1_ptr = &p1;
		pthread_create(&all_threads[1], NULL, &request_thread_function, p1_ptr);
		
		//printf("[%s] %d\n", __FUNCTION__, __LINE__);
		
		//////////////////////////////
		// Deal WIth Worker Thread //
		//////////////////////////////
		
		//create channels and add to list
		std::vector<RequestChannel*> channels(w, 0);
		for(int i = 0; i < w; i++)  {
			std::string s = chan->send_request("newthread");
			RequestChannel *workerChannel = new RequestChannel(s, RequestChannel::CLIENT_SIDE);
			channels[i] = workerChannel;
		}
		//Create one worker thread
		PARAMS p;
		p.work_chan_vector = channels;
		p.request_buff = &request_buff;
		p.john_response = &john_response;
		p.joe_response = &joe_response;
		p.jane_response = &jane_response;
		p.l = &lock;
		p.w = w;
		p.n = n;
		PARAMS* p_ptr = &p;	
		pthread_create(&all_threads[3], NULL, &worker_thread_function, p_ptr);
	 
		//////////////////////////////////
		// Deal WIth Statistics Threads //
		//////////////////////////////////		

		//JOHN
		PARAMS p4;
		p4.n = n;
		p4.name = John_l;
		p4.john_count = &john_frequency_count;
		p4.john_response = &john_response;
		p4.response_index = 0;
		PARAMS* p4_ptr = &p4;
		p4.count_vectors[p4.response_index] = &john_frequency_count;
		pthread_create(&all_threads[4], NULL, &stat_thread_function, p4_ptr);	
		
		//printf("[%s] %d\n", __FUNCTION__, __LINE__);		
		//JANE
		PARAMS p5;
		p5.n = n;
		p5.name = Jane_l;
		p5.jane_count = &jane_frequency_count;
		p5.jane_response = &jane_response;
		p5.response_index = 1;
		PARAMS* p5_ptr = &p5;
		p5.count_vectors[p5.response_index] = &jane_frequency_count;
		pthread_create(&all_threads[5], NULL, &stat_thread_function, p5_ptr);	

		//printf("[%s] %d\n", __FUNCTION__, __LINE__);
		//JOE
		PARAMS p6;
		p6.n = n;
		p6.name = Joe_l;
		p6.joe_count = &joe_frequency_count;
		p6.joe_response = &joe_response;
		p6.response_index = 2;
		PARAMS* p6_ptr = &p6;
		p6.count_vectors[p6.response_index] = &joe_frequency_count;
		pthread_create(&all_threads[6], NULL, &stat_thread_function, p6_ptr);	
	 

		//printf("[%s] %d\n", __FUNCTION__, __LINE__);
		// PARAMS p_quit;
		// p_quit.w = w;
		// p_quit.request_buff = &request_buff;
		// p_quit.l = &lock;
		// PARAMS* p_quit_ptr = &p_quit;
		// pthread_create(&all_threads[7], NULL, &quit_function, p_quit_ptr);		

	
		//join threads	
		for(int i = 0; i < 7; ++i){
			//printf("joining thread: %d\n", i);
			pthread_join(all_threads[i], NULL);
		}
		
		////////////////////////////////////////////////////////////////////////////////////////////////////////

		pthread_mutex_destroy(&lock);
		
		//end timer
		gettimeofday (&finish_time, NULL);
        start_usecs = (start_time.tv_sec * 1e6) + start_time.tv_usec;
        finish_usecs = (finish_time.tv_sec * 1e6) + finish_time.tv_usec;
		system("clear");
        std::cout << "Finished!" << std::endl;
		
        //print stuff
		std::cout << "Results for n == " << n << ", w == " << w << std::endl;
        std::cout << "Time to completion: " << std::to_string(finish_usecs - start_usecs) << " usecs\n" << std::endl;
        
		
		std::cout << "John Smith total: " << accumulate(john_frequency_count.begin(), john_frequency_count.end(), 0) << std::endl;
        std::cout << p4.results << std::endl; //supposed to print the histogram
        std::cout << "Jane Smith total: " << accumulate(jane_frequency_count.begin(), jane_frequency_count.end(), 0) << std::endl;
        std::cout << p5.results << std::endl; //supposed to print the histogram
        std::cout << "Joe Smith total: " << accumulate(joe_frequency_count.begin(), joe_frequency_count.end(), 0) << std::endl;
        std::cout << p6.results << std::endl; //supposed to print the histogram	 
        
        ofs.close();
        std::cout << "Sleeping..." << std::endl;
        usleep(10000);
        std::string finale = chan->send_request("quit");
        std::cout << "Finale: " << finale << std::endl;
    }
    else if(pid != 0) execl("dataserver", NULL);
}
