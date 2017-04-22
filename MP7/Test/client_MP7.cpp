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
    int n;
    int w;
    string name;
    void* arg;
    vector<RequestChannel*> work_chan_vector;
    RequestChannel* work_chan;
    bounded_buffer* request_buff;
    vector<vector<int>*> count_vectors = vector<vector<int>*>(3);
    int response_index;
    
    bounded_buffer *john_response;
    bounded_buffer *jane_response;
    bounded_buffer *joe_response;
    
    vector<int> *john_count;
    vector<int> *jane_count;
    vector<int> *joe_count;
    
    pthread_mutex_t* l;
    string results;
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
    void print(string s){
        pthread_mutex_lock(&console_lock);
        cout << s << endl;
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

string make_histogram(string name, vector<int> *data) {
    string results = "Frequency count for " + name + ":\n";
    for(int i = 0; i < data->size(); ++i) {
        results += to_string(i * 10) + "-" + to_string((i * 10) + 9) + ": " + to_string(data->at(i)) + "\n";
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
        
        if(request == "data Jane Smith") {
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
    
    int sent_requests = p.w;
    int received_requests = 0;

    while(received_requests < (3 * p.n)) {
        
        FD_ZERO(&read_fds);
        for(int i = 0; i < read_descriptors.size(); i++)  {
            FD_SET(read_descriptors[i], &read_fds);
        }
        
        int temp_max = read_descriptors[0];
        for(int i = 1; i < read_descriptors.size(); i++)  {
            if(read_descriptors[i] > temp_max)	temp_max = read_descriptors[i];
        }
        
        fd_set temp_set = read_fds;
        retval = select(temp_max + 1, &temp_set, NULL, NULL, NULL);

        string resp;
        string next_req;
        
        for(int i = 0; i < read_descriptors.size(); i++){
            if(FD_ISSET(read_descriptors[i], &read_fds)){
                resp = channels[i]->cread();
                
                received_requests += 1;
                
                if(name_number[i] == 0){
                    (*p.jane_response).push_back(resp);
                }
                else if(name_number[i] == 1){
                    (*p.john_response).push_back(resp);
                }
                else if(name_number[i] == 2){
                    (*p.joe_response).push_back(resp);
                }
                else printf("ERROR :(");
                if(sent_requests < 3*(p.n))  {
                    
                    
                    next_req = (*(p.request_buff)).retrieve_front();
                    
                    channels[i]->cwrite(next_req);
                    
                    sent_requests += 1;
                    
                    if(next_req == "data Jane Smith")  {
                        name_number[i] = 0;
                    }
                    else if(next_req == "data John Smith")  {
                        name_number[i] = 1;
                    }
                    else if(next_req == "data Joe Smith")  {
                        name_number[i] = 2;
                    }
                    else  {
                        printf("Data was not recognized\n");
                        exit;
                    }
                }
            }
        }
    }
    
    for(int i = 0; i < channels.size(); ++i) {
        channels[i]->send_request("quit");
    }
}

void* stat_thread_function(void* arg) {
    PARAMS_request* p = (PARAMS_request*)arg;
    int k = 0;
    while(true){
        if(p->response_index == 0)  {
            string response = (*(p->john_response)).retrieve_front();
            (*(p->john_count)).at(stoi(response) / 10) += 1;
        }
        else if(p->response_index == 1)  {
            string response = (*(p->jane_response)).retrieve_front();
            (*(p->jane_count)).at(stoi(response) / 10) += 1;
        }
        else{
            string response = (*(p->joe_response)).retrieve_front();
            (*(p->joe_count)).at(stoi(response) / 10) += 1;
        }
        ++k;
        if(k > (p->n)-1)  {
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
                cout << "This program can be invoked with the following flags:" << endl;
                cout << "-n [int]: number of requests per patient" << endl;
                cout << "-b [int]: size of request buffer" << endl;
                cout << "-w [int]: number of worker threads" << endl;
                cout << "-m 2: use output2.txt instead of output.txt for all file output" << endl;
                cout << "-h: print this message and quit" << endl;
                cout << "Example: ./client_solution -n 10000 -b 50 -w 120 -m 2" << endl;
                cout << "If a given flag is not used, a default value will be given" << endl;
                cout << "to its corresponding variable. If an illegal option is detected," << endl;
                cout << "behavior is the same as using the -h flag." << endl;
                exit(0);
        }
    }

    int pid = fork();
	if (pid > 0) {
        struct timeval start_time;
        struct timeval finish_time;
        int64_t start_usecs;
        int64_t finish_usecs;
        ofstream ofs;
        if(USE_ALTERNATE_FILE_OUTPUT) ofs.open("output2.txt", ios::out | ios::app);
        else ofs.open("output.txt", ios::out | ios::app);

        cout << "n == " << n << endl;
        cout << "b == " << b << endl;
        cout << "w == " << w << endl;

        cout << "CLIENT STARTED:" << endl;
        cout << "Establishing control channel... " << flush;
        RequestChannel *chan = new RequestChannel("control", RequestChannel::CLIENT_SIDE);
        cout << "done." << endl;

        /*
            This time you're up a creek.
            What goes in this section of the code?
            Hint: it looks a bit like what went here
            in MP7, but only a *little* bit.
         */
        
        pthread_mutex_t lock;
        bounded_buffer request_buff(b);
        vector<int> john_frequency_count(10, 0);
        vector<int> jane_frequency_count(10, 0);
        vector<int> joe_frequency_count(10, 0);
        
        bounded_buffer john_response(200);
        bounded_buffer jane_response(200);
        bounded_buffer joe_response(200);
        
        gettimeofday(&start_time, NULL);
        
        pthread_mutex_init(&lock, NULL);
        fflush(NULL);
        pthread_t all_threads[3+1+3+1];

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
        
        vector<RequestChannel*> channels(w, 0);
        for(int i = 0; i < w; i++)  {
            string s = chan->send_request("newthread");
            RequestChannel *workerChannel = new RequestChannel(s, RequestChannel::CLIENT_SIDE);
            channels[i] = workerChannel;
        }

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

        PARAMS_request p4;
        p4.n = n;
        p4.name = John_l;
        p4.john_count = &john_frequency_count;
        p4.john_response = &john_response;
        p4.response_index = 0;
        PARAMS_request* p4_ptr = &p4;
        p4.count_vectors[p4.response_index] = &john_frequency_count;
        pthread_create(&all_threads[4], NULL, &stat_thread_function, p4_ptr);

        PARAMS_request p5;
        p5.n = n;
        p5.name = Jane_l;
        p5.jane_count = &jane_frequency_count;
        p5.jane_response = &jane_response;
        p5.response_index = 1;
        PARAMS_request* p5_ptr = &p5;
        p5.count_vectors[p5.response_index] = &jane_frequency_count;
        pthread_create(&all_threads[5], NULL, &stat_thread_function, p5_ptr);

        PARAMS_request p6;
        p6.n = n;
        p6.name = Joe_l;
        p6.joe_count = &joe_frequency_count;
        p6.joe_response = &joe_response;
        p6.response_index = 2;
        PARAMS_request* p6_ptr = &p6;
        p6.count_vectors[p6.response_index] = &joe_frequency_count;
        pthread_create(&all_threads[6], NULL, &stat_thread_function, p6_ptr);

        for(int i = 0; i < 7; ++i){
            pthread_join(all_threads[i], NULL);
        }

        pthread_mutex_destroy(&lock);
        
        gettimeofday (&finish_time, NULL);
        start_usecs = (start_time.tv_sec * 1e6) + start_time.tv_usec;
        finish_usecs = (finish_time.tv_sec * 1e6) + finish_time.tv_usec;
        system("clear");
        cout << "Finished!" << endl;
        
        cout << "Results for n == " << n << ", w == " << w << endl;
        cout << "Time to completion: " << to_string(finish_usecs - start_usecs) << " usecs\n" << endl;
        
        
        cout << "John Smith total: " << accumulate(john_frequency_count.begin(), john_frequency_count.end(), 0) << endl;
        cout << p4.results << endl;
        cout << "Jane Smith total: " << accumulate(jane_frequency_count.begin(), jane_frequency_count.end(), 0) << endl;
        cout << p5.results << endl;
        cout << "Joe Smith total: " << accumulate(joe_frequency_count.begin(), joe_frequency_count.end(), 0) << endl;
        cout << p6.results << endl;
        
        ofs.close();
        cout << "Sleeping..." << endl;
        usleep(10000);
        string finale = chan->send_request("quit");
        cout << "Finale: " << finale << endl;
    }
	else if (pid == 0)
		execl("dataserver", NULL);
}
