#include "SRTF.h"

void SRTF::printByArrivalTime(){
	cout << "pid   " << "  arrival time     " << "     burst time:\n";
	for (auto ele : process_info){
		cout << get<0>(ele) << "\t" << get<1>(ele) << "\t" << get<2>(ele) << endl;
	}
}

SRTF::SRTF(string file)
{
	extractProcessInfo(file);
	std::sort(begin(process_info), end(process_info), [](ProcessInfo const &t1, ProcessInfo const &t2) {
		return get<1>(t1) < get<1>(t2);
	});
	
}
//scheduling implementation
void SRTF::schedule_tasks(){
    
   
    for (int i = 0; i < process_info.size(); i++) {
        SRTF_queue.push(shared_ptr<Process>(new Process(get<0>(process_info[i]), get<1>(process_info[i]), get<2>(process_info[i]))));
    }
    
     printByArrivalTime();
    
    // for easier iterating
    
     vector<shared_ptr<Process>> processes;
    /*
    while(!SRTF_queue.empty()) {
        processes.push_back(SRTF_queue.top());
        SRTF_queue.pop();
    }
     */
    
    int i = 0;
    int system_time = processes[0]->get_arrival_time();
    int smallest = 0;
    
    while(system_time < 50) {
        
        
        cout << "System Time[" << system_time << "].........Process[PID=" << processes[smallest]->getPid() << "] is Running" << endl;
        processes[0]->Run(1);
        if(processes[0]->is_Completed()){
            cout << "System Time[" << system_time << "].........Process[PID=" << processes[i]->getPid() << "] finished its job!" << endl;
        }
            
        system_time++;
    }

    
    
    
    
}
