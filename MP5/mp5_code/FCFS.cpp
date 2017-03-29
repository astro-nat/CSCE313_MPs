#include "FCFS.h"

//Use Base class's function to extract process information from file
//And fill in the fcfs_queue; the priority in this queue is the arrival time; 
//Make sure you did the ArrivalEarlierThan Comparator
FCFS::FCFS(string file)
{

}

void FCFS::print(){
	cout<<"pid\t"<<"  arrival time\t"<<"\tburst time:\n";
	for(auto ele:process_info){
		cout<<get<0>(ele)<<"\t"<<get<1>(ele)<<"\t"<<get<2>(ele)<<endl;
	}
}

//Assuming the time the CPU starts working with process is system time 0
void FCFS::schedule_tasks(){
	
}

FCFS::FCFS(){}