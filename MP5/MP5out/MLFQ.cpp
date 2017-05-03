#include "MLFQ.h"

//The goal of this function is to fill the 4 levels with process_info 
//You should sort the process_info by the arrival_time of the Process;
//Process with smaller arrival time will have smaller index in the vector

//After filling in the top 3 levels, then do insertion for the fcfs level

int timeElapsed = 0;
vector<Process> procs;

MLFQ::MLFQ(string file)
{
    extractProcessInfo(file);
    
    std::sort(begin(process_info), end(process_info), [](ProcessInfo const &t1, ProcessInfo const &t2) {
        return get<1>(t1) < get<1>(t2);
    });

    /* NOTES FROM NAT
    * with new process, add to Level 1 queue. If full, add to Level 2 queue. If full, add to Level 3 queue. If full, add to lowest level (infinite size).
    
    * when time quantum used up on given level, drop a level until it finds a spot
     */
    
    vector<shared_ptr<Process>> level1;
    vector<shared_ptr<Process>> level2;
    vector<shared_ptr<Process>> level3;
    
    for(int i = 0; i < process_info.size(); i++) {
        int x = get<0>(process_info[i]);
        int y = get<1>(process_info[i]);
        int z = get<2>(process_info[i]);
        
        shared_ptr<Process> sp(new Process(x,y,z));
        if(level1.size() != LEVEL1_CAPACITY){
            level1.push_back(sp);
        }
        else if(level2.size() != LEVEL2_CAPACITY) {
            level2.push_back(sp);
        }
        else if(level3.size() != LEVEL3_CAPACITY){
            level3.push_back(sp);
        }
        else {
            Process* proc = new Process(x,y,z);
            procs.push_back(*proc);
            lowestLevel.push(*proc);
        }
        
    }
    
    upperLevels.push_back(level1);
    upperLevels.push_back(level2);
    upperLevels.push_back(level3);

}


//This function is used to keep track of the process who entered the fcfs queue most recently
//The purpose is to properly adjust the upcoming process's arrival time
//If the arrival time is changed, you can still check its original arrival time by accessing the 
//process_info variable
void MLFQ::update_last_process_fcfs(Process process_to_fcfs) {
	last_process_fcfs = process_to_fcfs;
}

//This function has the following assumptions:
/*
	1. The start_level is not equal goal_level;
	2. goal_level is larger then start_level
	3. When you use this function, you should know the process should not jump from level 0 to level 2 or 3 if the level 1 has a space there.
	   Generally, when you degrade a process, it tries to go to the level below by one level and if that level is full, it will keep going down 
	   until it finds a level which has space there.
	4. Successful jump will return 1, else 0
	5. To successfully jump to the goal_level, the process must go to the end of the vector corresponding to goal_level
*/
//start_level is the level the process is located at, it is one value of 0 , 1, 2;
//pos is its index in the vector
//goal_level is the level it tries to enter
int MLFQ::level_jump(shared_ptr<Process> p, unsigned int start_level, unsigned int pos, unsigned int goal_level) {
	
    if(start_level != goal_level && goal_level > start_level) {
        if(start_level >= 0 && start_level < 2) {
            upperLevels[goal_level][pos] = p;
        }
        else if (start_level == 2) {
            lowestLevel.push(*p);
        }
    }
    
	return 0;
}


/*
 p is the process which is going to be degrade to lower levle
 levle is the level it is located currently
 legal value of level can be: 0, 1, 2 Since no need to degrade for last level
 pos is the its index in the vector

0: it is located at the top level
1:  it is located at the second highest level
2:  it is located at the third highest level
3: it is in the fcfs level, no need to degrade, it will stay there until finishing the job and leave
*/

//pos is the index of the process in the vector
//Your goal is to degrade this process by one level
//You can use level_jump() function here based on which level the process is going to jump
void MLFQ::degrade_process(shared_ptr<Process> p, unsigned int level, unsigned int pos) {
	
    if(pos < upperLevels[level+1].size()) {
        level_jump(p,level,pos,level+1);
    }
}

/*
You can use multiple loops here to do the job based on the document;
Make sure print out the timing information correctly
*/
void MLFQ::schedule_tasks(){
    int system_time = 0;
    int timeElapsed = 0;
    int complete_count = 0;
    int response_time = 0;
    
    //int wait_times[processVec.size()];
    //int response_times[processVec.size()];
    
    for(auto ele : process_info) {
        
        for(int lvl = 0; lvl<= 2; lvl++) {
            
            int quantum;
            string levelLabel;
            if(lvl == 0) { quantum = LEVEL1_QUANTUM; levelLabel = "First";}
            if(lvl == 1) { quantum = LEVEL2_QUANTUM; levelLabel = "Second"; }
            if(lvl == 2) { quantum = LEVEL3_QUANTUM; levelLabel = "Third";}
            
            if(upperLevels[lvl].size() != 0) {
                cout << "System Time[" << timeElapsed << "]........." << levelLabel << " Level Queue Starts Work\n";
            }
            
            while(upperLevels[lvl].size() != 0) {
                if(upperLevels[lvl][0]->is_Completed()) {
                    
                    cout << "SystemTime["
                    << timeElapsed<<"]......."<<"Process[PID=" << upperLevels[lvl][0]->getPid()<<"] is Running" << endl;
                    upperLevels[lvl].erase(upperLevels[lvl].begin());
                    complete_count++;
                }
                else if(upperLevels[lvl][0]->get_remaining_time() < quantum) {
                    
                    cout << "SystemTime["
                    << timeElapsed<<"]......."<<"Process[PID=" << upperLevels[lvl][0]->getPid()<<"] is Running" << endl;
                    complete_count++;
                    for(int j = 0; j < upperLevels[lvl][0]->get_remaining_time(); j++) {
                        cout << "SystemTime["
                        << timeElapsed<<"]......."<<"Process[PID=" << upperLevels[lvl][0]->getPid()<<"] is Running" << endl;
                        timeElapsed++;
                    }
                    cout << "SystemTime["
                    << timeElapsed<<"]......."<<"Process[PID=" << upperLevels[lvl][0]->getPid()<<"] is Running" << endl;
                    complete_count++;
                    upperLevels[lvl][0]->Run(upperLevels[lvl][0]->get_remaining_time());
                    degrade_process(upperLevels[lvl][0],lvl,0);
                }
                else {
                    
                    upperLevels[lvl][0]->Run(quantum);
                    for(int k = 0; k < quantum; k++) {
                        cout << "SystemTime["
                        << timeElapsed<<"]......."<<"Process[PID=" << upperLevels[lvl][0]->getPid()<<"] is Running" << endl;
                        timeElapsed++;
                    }
                    cout << "SystemTime["
                    << timeElapsed<<"]......."<<"Process[PID=" << upperLevels[lvl][0]->getPid()<<"] is Running" << endl;
                    timeElapsed++;
                    system_time = timeElapsed;
                    
                    response_time = complete_count;

                    degrade_process(upperLevels[lvl][0],lvl,0);

                }
            }
        }
        
        }
    cout << "All done" << endl;
    
    double wait_time_sum = 0;
    double response_time_sum = 0;
    wait_time_sum += system_time;
    response_time_sum += response_time;
    
    cout << "wait_time_sum: " << wait_time_sum << endl;
    cout << "response_time_sum " << response_time_sum << endl;
    cout << "Average wait time: " << wait_time_sum/10 << endl;
    cout << "Average response time: " << response_time_sum/10 << endl;
    
    
}
