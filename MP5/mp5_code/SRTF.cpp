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
	/*
	Fill in this part
	*/
}