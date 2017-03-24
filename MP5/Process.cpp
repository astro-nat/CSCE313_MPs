#include "Process.h"

//Constructor
/*
initialize everything to 0
*/
Process::Process() {
	
}

//Constructor
//make sure set isCompleted to false
Process::Process(int pid, int arrival_time, int cpu_burst_time) {

}

//Copy Construcor
//Construct it with pid, arrival_time, cpu_burst_time, remaining_time and isCompleted
Process::Process(const Process &p){

}

//Every time, When your process is runing, use this function to update 
//the remaining time and monitor if the process is done or not
void Process::Run(int run_time) {

}

int Process::getPid() const {

}
int Process::get_remaining_time() const {
	
}
int Process::get_cpu_burst_time() const {

}
int Process::get_arrival_time() const {
	
}
bool Process::is_Completed() const {

}

//This function will be used in MLFQ implementation
void Process::change_arrival_time(int new_arrival_time) {
	
}

//This function might be used in MLFQ implementation since you need to put 
//undone process from other levels to last level, you may want to update 
//remaining time for them.
void Process::update_remaining_time(int updated_remaining_time){
	
}

//Assignment Operator Overloading
//make sure do the assignment for pid, arrival_time, cpu_burst_time, remaining_time and isCompleted
Process & Process::operator=(const Process & p)
{

}


