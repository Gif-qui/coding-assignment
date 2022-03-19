#include "hw9.h"
#include <thread>
#include <atomic>
#include <chrono>
#include <math.h>

bool csense = false;
int counter = 1;

void cbarr(int nthread){ //centralized barrier
	bool local_sense = !csense;
	if (counter++ == nthread) {
		counter--;
		csense = local_sense;
	} else {
		while (csense != local_sense) { }
	}
}


void centest(int i){
	printf("cenbarrier start %d \n", i);
	cbarr(5); //print test, just checks to see if things are working
	printf("cenbarrier passed%d \n", i);
}

void runcen(){

	std::thread thrd1(centest,1);
	std::thread thrd2(centest,2);
	std::thread thrd3(centest,3);
	std::thread thrd4(centest,4);
	std::thread thrd5(centest,5);
	//std::thread thrd6(centest,6); 
	//std::thread thrd7(centest,7);
	//std::thread thrd8(centest,8);
	//std::thread thrd9(centest,9);
	//std::thread thrd10(centest,10);
	thrd1.join();
	thrd2.join();
	thrd3.join();
	thrd4.join();
	thrd5.join();
	//thrd6.join();
	//thrd7.join();
	//thrd8.join();
	//thrd9.join();
	//thrd10.join();
}	