#include "hw9.h"
#include <thread>
#include <atomic>
#include <chrono>
#include <math.h>

int P = 5;
bool msense = false;
int nthread = 5;

void mbarr(bool **flags, int tid) { //mcs barrier
	int round = 0;
	for (round = 0; ((P | tid) & (1 << round)) == 0; round++){
		while (flags[tid][round] != msense) {}
	}
	if (round < log2(P)) {
		int parent = tid & ~((1 << (round+1)) - 1);
		flags[parent][round] = msense;
		while (flags[tid][round] != msense) { }
	}
	while (round-- > 0) {
		int child = tid | (1 << round);
		flags[child][round] = msense;
	}
	msense = !msense;
}

void mcstest(bool **flags, int tid){
	printf("mcsbarrier start %d\n", tid);
	mbarr(flags, tid); //test print
	printf("mcsbarrier end %d\n", tid);
}

void mcsrun() {
	// makes the flags for the mcs barrier
	bool **mcsflags;
	mcsflags = new bool *[nthread];
	for (int i = 0; i < nthread; i++){
		mcsflags[i] = new bool[3];
	}
	std::thread thread1(mcstest, mcsflags, 0);
	std::thread thread2(mcstest, mcsflags, 1);
	std::thread thread3(mcstest, mcsflags, 2);
	std::thread thread4(mcstest, mcsflags, 3);
	std::thread thread5(mcstest, mcsflags, 4);
	/*std::thread thread6(mcstest, mcsflags, 5);
	std::thread thread7(mcstest, mcsflags, 6);
	std::thread thread8(mcstest, mcsflags, 7);
	std::thread thread9(mcstest, mcsflags, 8);
	std::thread thread10(mcstest, mcsflags, 9);*/
	thread1.join();
	thread2.join();
	thread3.join();
	thread4.join();
	thread5.join();
	/*thread6.join();
	thread7.join();
	thread8.join();
	thread9.join();
	thread10.join();*/
}
