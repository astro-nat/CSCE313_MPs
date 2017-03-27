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
    
     //printByArrivalTime();
    
    // for easier iterating
    
     vector<shared_ptr<Process>> processes;
     while(!SRTF_queue.empty()) {
         processes.push_back(SRTF_queue.top());
         SRTF_queue.pop();
    }
    
    vector<shared_ptr<Process>> current_p;
    
    int i, smallest = 0;
    
    // make this equal to smallest arrival time - 1
    int system_time = 1;
    
    while(current_p.size() < processes.size()) {
        
        system_time++;
        
        // only looks through processes whose arrival time has arrived
        for(int i = 0; i < processes.size(); i++) {
            
            if(processes[i]->get_arrival_time() == system_time) {
                current_p.push_back(processes[i]);
            }
        }
        
        //testing
        for(int i = 0; i < current_p.size(); i++) {
            //cout << "Arrival time of " << current_p[i]->getPid() << ": " << current_p[i]->get_arrival_time() << endl;
            //cout << "Remaining time of " << current_p[i]->getPid() << ": " << current_p[i]->get_remaining_time() << endl;
        }
        
        // find process with smallest remaining time, excluding those with 0 remaining time
        if(current_p.size() > 0) {
            for(int i = 0; i < current_p.size(); i++) {
                
                //cout << "Aye" << endl;
                if(current_p[i]->get_remaining_time() < current_p[smallest]->get_remaining_time() && !current_p[i]->is_Completed()) {
                    smallest = i;
                    //cout << "Smallest remaining time: " << current_p[smallest]->get_remaining_time() << endl;
                }
            }
        }
        
        // if process with smallest remaining time not completed, run
        if(!current_p[smallest]->is_Completed()){
            //cout << "Smallest remaining time: " << current_p[smallest]->get_remaining_time() << endl;
            current_p[smallest]->Run(1);
            
            cout << "System Time[" << system_time << "].........Process[PID=" << current_p[smallest]->getPid() << "] is Running" << endl;
            
            if(current_p[smallest]->is_Completed()){
                cout << "System Time[" << system_time << "].........Process[PID=" << current_p[smallest]->getPid() << "] finished its job!" << endl;
            }
            
        }
        
        
        
        
    }

    
    
    
    
}
