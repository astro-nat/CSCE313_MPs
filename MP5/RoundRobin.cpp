#include "RoundRobin.h"
#include <iostream>
using namespace std;
//No need to change it
RoundRobin::RoundRobin() {
	time_quantum = 0;
}


/*
This is a constructor for RoundRobin Scheduler, you should use the extractProcessInfo function first
to load process information to process_info and then sort process by arrival time;
Also, fill in the procesVec with shared_ptr

Also initialize time_quantum
*/
RoundRobin::RoundRobin(string file, int time_quantum) {
    this->time_quantum = time_quantum;
    extractProcessInfo(file);
	for (int i = 0; i < process_info.size(); i++) {
		processVec.push_back(shared_ptr<Process>(new Process(get<0>(process_info[i]), get<1>(process_info[i]), get<2>(process_info[i]))));
	}
}

void RoundRobin::set_time_quantum(int quantum) {
    time_quantum = quantum;
}

int RoundRobin::get_time_quantum() {
    return time_quantum;
}


//Schedule tasks based on RoundRobin Rule
//the jobs are put in the order the arrived
//Make sure you print out the information like we put in the document
void RoundRobin::schedule_tasks() {
	/*
	Do this part.
	*/
    
	//print();
    
    int system_time = 0;
    int complete_count = 0;
    int quantum_count = 0;
    bool all_complete = false;
    
    while(all_complete == false) {
        for(int i = 0; i < processVec.size(); i++) {
            
            if(processVec[i]->get_arrival_time() <= system_time) {
                quantum_count = 1;
                while(quantum_count <= time_quantum && !processVec[i]->is_Completed()) {
                    
                    //cout << "Arrival time of " << processVec[i]->getPid() << ": " << processVec[i]->get_arrival_time() << endl;
                    //cout << "System time: " << system_time << endl;
                    
                    cout << "System Time[" << system_time << "].........Process[PID=" << processVec[i]->getPid() << "] is Running" << endl;
                    processVec[i]->Run(1);
                        
                    if(processVec[i]->is_Completed()) {
                        cout << "System Time[" << system_time << "].........Process[PID=" << processVec[i]->getPid() << "] finished its job!" << endl;
                        complete_count++;
                    }
                    
                    quantum_count++;
                }
            }
            
            system_time++;
            
        }
    
        if(complete_count == processVec.size()) {
            all_complete = true;
        }
    }
}

//Fill in the procesVec with shared_ptr
//And set time_quantum, or you can also use set_time_quantum function for setting quantum
RoundRobin::RoundRobin(vector<ProcessInfo> &process_info, int time_quantum){
    time_quantum = time_quantum;
	for (int i = 0; i < process_info.size(); i++) {
		processVec.push_back(shared_ptr<Process>(new Process(get<0>(process_info[i]), get<1>(process_info[i]), get<2>(process_info[i]))));
	}
}

void RoundRobin::print(){
	for (auto ele : processVec){
		cout << ele->getPid() << "; " << ele->get_arrival_time() << "; " << ele->get_cpu_burst_time() << endl;
	}
}
