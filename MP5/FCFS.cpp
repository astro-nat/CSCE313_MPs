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
	for(auto ele:process_info){
		cout<<get<0>(ele)<<"\t"<<get<1>(ele)<<"\t"<<get<2>(ele)<<endl;
	}
}

//Assuming the time the CPU starts working with process is system time 0
void FCFS::schedule_tasks(){
	
    int system_time = 0;
    bool all_complete = 0;
    
    while(all_complete == false) {
        
        cout << "System Time[" << system_time << "].........Process[PID=" << fcfs_queue.top().getPid() << "] is Running" << endl;
        
        Process p = fcfs_queue.top();
        fcfs_queue.pop();
        p.Run(1);
        fcfs_queue.push(move(p));
        
        if(fcfs_queue.top().is_Completed()) {
            cout << "System Time[" << system_time << "].........Process[PID=" << fcfs_queue.top().getPid() << "] finished its job!" << endl;
            fcfs_queue.pop();
        }
        
        system_time++;
        
        if(fcfs_queue.empty()) {
            all_complete = true;
        }
    }
    
}

FCFS::FCFS(){}
