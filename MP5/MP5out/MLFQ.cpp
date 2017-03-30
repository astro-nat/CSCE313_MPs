#include "MLFQ.h"

//The goal of this function is to fill the 4 levels with process_info 
//You should sort the process_info by the arrival_time of the Process;
//Process with smaller arrival time will have smaller index in the vector

//After filling in the top 3 levels, then do insertion for the fcfs level
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

    // initialize to 3 levels
    upperLevels.resize(3);
    upperLevels[0].resize(LEVEL1_CAPACITY);
    upperLevels[1].resize(LEVEL2_CAPACITY);
    upperLevels[2].resize(LEVEL3_CAPACITY);
    
    // load upper levels
    int position = 0;
    for(int i = 0; i < process_info.size(); i++) {
        
        shared_ptr<Process> p = shared_ptr<Process>(new Process(get<0>(process_info[i]), get<1>(process_info[i]), get<2>(process_info[i])));
        
        // start at level 1
        int quantum = 0;
        while(position != LEVEL1_CAPACITY && !p->is_Completed() && quantum < LEVEL1_QUANTUM) {
            
            upperLevels[0][position] = p;
            p->update_remaining_time(p->get_remaining_time() - 1);
            position++;
            
            p->change_arrival_time(position);
            degrade_process(p,0,position);
            
            quantum++;
        }
        
        // if level 1 capacity or quantum reached, drop to level 2
        while(upperLevels[1].size() != LEVEL1_CAPACITY && !p->is_Completed()) {
            
            int quantum = 0;
            while(quantum < LEVEL2_QUANTUM && p->get_remaining_time() != 0) {
                upperLevels[1].push_back(p);
                p->update_remaining_time(p->get_remaining_time() - 1);
            }
            
            p->change_arrival_time(p->get_arrival_time() - LEVEL2_QUANTUM);
            degrade_process(p,0,p->get_arrival_time());
        }
        
        // if level 2 capacity or quantum reached, drop to level 3
        while(upperLevels[2].size() != LEVEL1_CAPACITY && !p->is_Completed()) {
            int quantum = 0;
                while(quantum < LEVEL2_QUANTUM && p->get_remaining_time() != 0) {
                    upperLevels[2].push_back(p);
                    p->update_remaining_time(p->get_remaining_time() - 1);
                }
                p->change_arrival_time(p->get_arrival_time() - LEVEL3_QUANTUM);
                degrade_process(p,0,p->get_arrival_time());
            }
            // if level 3 capacity or quantum eached, drop to lowest level
        
        if(!p->is_Completed()) {
            lowestLevel.push(*p);
            update_last_process_fcfs(*p);
            position++;
        }
    }

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
    
    cout << "System Time[" << system_time << "].........First Level Queue Starts Work\n";
    for(int i = 0; i < upperLevels[0].size(); i++) {
        cout << "System Time[" << system_time << "].........Process[PID=" << upperLevels[0][i]->getPid() << "] is Running" << endl;
        system_time++;
    }
    cout << "System Time[" << system_time << "].........Second Level Queue Starts Work\n";
    for(int i = 0; i < upperLevels[1].size(); i++) {
        cout << "System Time[" << system_time << "].........Process[PID=" << upperLevels[1][i]->getPid() << "] is Running" << endl;
        system_time++;
    }
    cout << "System Time[" << system_time << "].........Third Level Queue Starts Work\n";
    for(int i = 0; i < upperLevels[2].size(); i++) {
        cout << "System Time[" << system_time << "].........Process[PID=" << upperLevels[2][i]->getPid() << "] is Running" << endl;
        system_time++;
    }
    cout << "System Time[" << system_time << "].........FCFS Level Queue Starts Work";
    for(int i = 0; i < lowestLevel.size(); i++) {
        cout << "System Time[" << system_time << "].........Process[PID=" << lowestLevel.top().getPid() << "] is Running" << endl;
        system_time++;
    }
    
}
