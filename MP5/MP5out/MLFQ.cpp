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

    // load upper levels
    int system_time = 0;
    for(int i = 0; i < process_info.size(); i++) {
        
        shared_ptr<Process> p = shared_ptr<Process>(new Process(get<0>(process_info[i]), get<1>(process_info[i]), get<2>(process_info[i])));
        
        if(upperLevels[0].size() != LEVEL1_CAPACITY) {
            int quantum = 0;
            while(quantum < LEVEL1_QUANTUM && p->get_remaining_time() != 0) {
                upperLevels[0].push_back(p);
                p->update_remaining_time(p->get_remaining_time() - 1);
            }
            degrade_process(p,2,upperLevels[1].size());
            
        }
        else {
            // drop to level 2
            if(upperLevels[1].size() != LEVEL2_CAPACITY) {
                int quantum = 0;
                while(quantum < LEVEL2_QUANTUM && p->get_remaining_time() != 0) {
                    upperLevels[1].push_back(p);
                    p->update_remaining_time(p->get_remaining_time() - 1);
                }
                degrade_process(p,3,upperLevels[2].size());
            }
            else {
                // drop to level 3
                if (upperLevels[2].size() != LEVEL3_CAPACITY) {
                    int quantum = 0;
                    while(quantum < LEVEL3_QUANTUM) {
                        upperLevels[2].push_back(p);
                    }
                }
                else {
                    lowestLevel.push(*p);
                    system_time++;
                }
            }
        }
    }
    
    /*
    for(int i = 0; i < LEVEL1_CAPACITY; i++) {
        upperLevels[i].push_back(shared_ptr<Process>(new Process(get<0>(process_info[i]), get<1>(process_info[i]), get<2>(process_info[i]))));
    }
    
    // load lowest level
    for (int i = 0; i < process_info.size(); i++) {
        lowestLevel.push(Process(get<0>(process_info[i]), get<1>(process_info[i]), get<2>(process_info[i])));
    }
     */
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
        upperLevels[goal_level][pos] = p;
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
	
    if(level == 2 || level == 3) {
        upperLevels[level-1][pos] = p;
    }
    else if (level == 1) {
        lowestLevel.push(*p);
    }
}

/*
You can use multiple loops here to do the job based on the document;
Make sure print out the timing information correctly
*/
void MLFQ::schedule_tasks(){
	
    // with new process, add to Level 1 queue. If full, add to Level 2 queue. If full, add to Level 3 queue. If full, add to lowest level (infinite size).
    
    // when time quantum used up on given level, drop a level until it finds a spot
    
    for(int i = 0; i < process_info.size(); i++) {
        //upperLevels[0].push_back(process_info[i]);
        for(int i = 0; i < LEVEL1_QUANTUM; i++) {
            
            cout << "Runnin runnin runnin" << endl;
        }
    }
    
}
