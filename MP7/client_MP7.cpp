/*
    File: client.cpp

    Author: J. Higginbotham
    Department of Computer Science
    Texas A&M University
    Date  : 2016/05/21

    Based on original code by: Dr. R. Bettati, PhD
    Department of Computer Science
    Texas A&M University
    Date  : 2013/01/31
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
    No additional includes are required
    to complete the assignment, but you're welcome to use
    any that you think would help.
*/
/*--------------------------------------------------------------------------*/

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
#include "reqchannel.h"

using namespace std;

/*
    This next file will need to be written from scratch, along with
    semaphore.h and (if you choose) their corresponding .cpp files.
 */

#include "bounded_buffer.h"

/*--------------------------------------------------------------------------*/
/* DATA STRUCTURES */
/*--------------------------------------------------------------------------*/

/*
    All *_params structs are optional,
    but they might help.
 */
struct PARAMS_request {
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

struct PARAMS_WORKER {

};

struct PARAMS_STAT {

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

/*
    You'll need to fill these in.
*/
void* request_thread_function(void* arg) {
    PARAMS_request pr = *(PARAMS_request *) arg;
    
    for(int i = 0; i < pr.n; i++) {
        
        (*pr.request_buff).push_back(pr.name);
    }
}

void* worker_thread_function(void* arg) {
    PARAMS_request p = *(PARAMS_request*)arg;
    
    vector<RequestChannel*> channels = p.work_chan_vector;
    vector<int> read_descriptors(p.w, 0);
    vector<int> name_number(p.w, 0);
    
    fd_set read_fds;
    int retval;
    
    for(int i = 0; i < channels.size(); i++) {
        int temp_fd = channels[i]->read_fd();
        read_descriptors[i] = temp_fd;
    }
    
    for(int i = 0; i < channels.size(); i++) {
        string request = (*(p.request_buff)).retrieve_front();
        
        if(request == "data Jane Sith") {
            name_number[i] = 0;
            
        }
        else if (request == "data John Smith") {
            name_number[i] = 1;
        
        }
        else if (request == "data Joe Smith") {
            name_number[i] = 2;
        }
        else {
            exit;
        }
        channels[i]->cwrite(request);
    }
}

void* stat_thread_function(void* arg) {

}

/*--------------------------------------------------------------------------*/
/* MAIN FUNCTION */
/*--------------------------------------------------------------------------*/

int main(int argc, char * argv[]) {
    int n = 10; //default number of requests per "patient"
    int b = 50; //default size of request_buffer
    int w = 10; //default number of worker threads
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
	if (pid > 0) {
        struct timeval start_time;
        struct timeval finish_time;
        int64_t start_usecs;
        int64_t finish_usecs;
        std::ofstream ofs;
        if(USE_ALTERNATE_FILE_OUTPUT) ofs.open("output2.txt", std::ios::out | std::ios::app);
        else ofs.open("output.txt", std::ios::out | std::ios::app);

        std::cout << "n == " << n << std::endl;
        std::cout << "b == " << b << std::endl;
        std::cout << "w == " << w << std::endl;

        std::cout << "CLIENT STARTED:" << std::endl;
        std::cout << "Establishing control channel... " << std::flush;
        RequestChannel *chan = new RequestChannel("control", RequestChannel::CLIENT_SIDE);
        std::cout << "done." << std::endl;

        /*
            This time you're up a creek.
            What goes in this section of the code?
            Hint: it looks a bit like what went here
            in MP7, but only a *little* bit.
         */
        
        // beginning of Nat additions
        
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
        //gettimeofday(&start_time, NULL);
        
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
        
        PARAMS_request p2;
        p2.n = n;
        p2.w = w;
        p2.name = Jane_l;
        p2.request_buff = &request_buff;
        p2.l = &lock;
        PARAMS_request* p2_ptr = &p2;
        pthread_create(&all_threads[0], NULL, &request_thread_function, p2_ptr);
        
        PARAMS_request p3;
        p3.n = n;
        p3.w = w;
        p3.name = Joe_l;
        p3.request_buff = &request_buff;
        p3.l = &lock;
        PARAMS_request* p3_ptr = &p3;
        pthread_create(&all_threads[2], NULL, &request_thread_function, p3_ptr);
        
        PARAMS_request p1;
        p1.n = n;
        p1.w = w;
        p1.name = John_l;
        p1.request_buff = &request_buff;
        p1.l = &lock;
        PARAMS_request* p1_ptr = &p1;
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
        PARAMS_request p;
        p.work_chan_vector = channels;
        p.request_buff = &request_buff;
        p.john_response = &john_response;
        p.joe_response = &joe_response;
        p.jane_response = &jane_response;
        p.l = &lock;
        p.w = w;
        p.n = n;
        PARAMS_request* p_ptr = &p;
        pthread_create(&all_threads[3], NULL, &worker_thread_function, p_ptr);
        
        //////////////////////////////////
        // Deal WIth Statistics Threads //
        //////////////////////////////////
        
        //JOHN
        PARAMS_request p4;
        p4.n = n;
        p4.name = John_l;
        p4.john_count = &john_frequency_count;
        p4.john_response = &john_response;
        p4.response_index = 0;
        PARAMS_request* p4_ptr = &p4;
        p4.count_vectors[p4.response_index] = &john_frequency_count;
        pthread_create(&all_threads[4], NULL, &stat_thread_function, p4_ptr);
        
        //printf("[%s] %d\n", __FUNCTION__, __LINE__);
        //JANE
        PARAMS_request p5;
        p5.n = n;
        p5.name = Jane_l;
        p5.jane_count = &jane_frequency_count;
        p5.jane_response = &jane_response;
        p5.response_index = 1;
        PARAMS_request* p5_ptr = &p5;
        p5.count_vectors[p5.response_index] = &jane_frequency_count;
        pthread_create(&all_threads[5], NULL, &stat_thread_function, p5_ptr);
        
        //printf("[%s] %d\n", __FUNCTION__, __LINE__);
        //JOE
        PARAMS_request p6;
        p6.n = n;
        p6.name = Joe_l;
        p6.joe_count = &joe_frequency_count;
        p6.joe_response = &joe_response;
        p6.response_index = 2;
        PARAMS_request* p6_ptr = &p6;
        p6.count_vectors[p6.response_index] = &joe_frequency_count;
        pthread_create(&all_threads[6], NULL, &stat_thread_function, p6_ptr);
        
        
        //printf("[%s] %d\n", __FUNCTION__, __LINE__);
        // PARAMS_request p_quit;
        // p_quit.w = w;
        // p_quit.request_buff = &request_buff;
        // p_quit.l = &lock;
        // PARAMS_request* p_quit_ptr = &p_quit;
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
        
        // end of Nat additions

        ofs.close();
        std::cout << "Sleeping..." << std::endl;
        usleep(10000);
        std::string finale = chan->send_request("quit");
        std::cout << "Finale: " << finale << std::endl;
    }
	else if (pid == 0)
		execl("dataserver", NULL);
}
