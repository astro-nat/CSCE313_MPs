#include "FCFS.h"

//Use Base class's function to extract process information from file
//And fill in the fcfs_queue; the priority in this queue is the arrival time; 
//Make sure you did the ArrivalEarlierThan Comparator
FCFS::FCFS(string file)
{
    extractProcessInfo(file);
    
    for (int i = 0; i < process_info.size(); i++) {
        fcfs_queue.push(Process(get<0>(process_info[i]), get<1>(process_info[i]), get<2>(process_info[i])));
    }
    
}

void FCFS::print(){
	cout<<"pid\t"<<"  arrival time\t"<<"\tburst time:\n";
	for(auto ele : process_info){
		cout<<get<0>(ele)<<"\t"<<get<1>(ele)<<"\t"<<get<2>(ele)<<endl;
	}
}

//Assuming the time the CPU starts working with process is system time 0
void FCFS::schedule_tasks(){
	
    int system_time = 0;
    bool all_complete = 0;
    int wait_times = 0;
    int response_times = 0;
    double stack_size = fcfs_queue.size();
    
    while(all_complete == false) {
        cout << "System Time[" << system_time << "].........Process[PID=" << fcfs_queue.top().getPid() << "] is Running" << endl;

        wait_times += system_time;
        
        Process p = fcfs_queue.top();
        fcfs_queue.pop();
        p.Run(1);
        fcfs_queue.push(move(p));
        
        if(fcfs_queue.top().is_Completed()) {
            cout << "System Time[" << system_time << "].........Process[PID=" << fcfs_queue.top().getPid() << "] finished its job!" << endl;
            fcfs_queue.pop();
            response_times += system_time;
        }
        
        system_time++;
        
        if(fcfs_queue.empty()) {
            all_complete = true;
        }
        
    }
    double wait_time_sum = 0;
    double response_time_sum = 0;
    wait_time_sum += wait_times;
    response_time_sum += response_times;
    
    cout << "wait_time_sum: " << wait_time_sum << endl;
    cout << "response_time_sum " << response_time_sum << endl;
    cout << "fcfs_queue.size: " << stack_size << endl;
    cout << "Average wait time: " << wait_time_sum/stack_size << endl;
    cout << "Average response time: " << response_time_sum/stack_size << endl;
    
}

FCFS::FCFS(){}
