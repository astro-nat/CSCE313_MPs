#include "Scheduler.h"

//Read a process file to extract process information
//All content goes to proces_info vector
void Scheduler::extractProcessInfo(string file){
    ifstream in;
    in.open(file);
    
	while(!in.eof()) {
		int temp1,temp2,temp3;
		in >> temp1;
		in >> temp2;
		in >> temp3;
		
		process_info.push_back(make_tuple(temp1,temp2,temp3));
	}
}
