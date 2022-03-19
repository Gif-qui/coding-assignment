#include "hw9.h"
#include <thread>
#include <atomic>
#include <chrono>
#include <math.h>

int nthreads = 5; //values needed for the dissemination barrier to wkr
int rounds = log2(nthreads);
bool dsense = false;
int parity = 0;

void dbarr(bool **flags, int tid){ //dissemination barrier
	for (int i = 0; i < rounds; i++) {
		int partner = (tid + 2^i) % nthreads;
		flags[partner][i] = !dsense;
		while (flags[tid][i] == dsense){ }
	}
	if (parity == 1) {
		dsense = !dsense;
	}
	parity = 1-parity;
}

void disstest(int id, bool **flags){
	printf("diss barrier start %d\n", id);
	dbarr(flags, id); //barrier is run here, if works all ends should come after start
	printf("diss barrier end %d\n", id);
}

void run_barriers(){
	int nthread = 5;

	bool **flags;
	flags = new bool *[nthread];
	for (int i = 0; i < nthread; i++){
		flags[i] = new bool[3];
	} //this makes the array of pointers for the flags
	for (int i = 0; i < nthread; i++){
		for (int j = 0; j < 3; j++){
			flags[i][j] = false; //this fills all of the flags with false = sense
		}
	}

	std::thread thred1(disstest, 0, flags);
	std::thread thred2(disstest, 1, flags);
	std::thread thred3(disstest, 2, flags);
	std::thread thred4(disstest, 3, flags);
	std::thread thred5(disstest, 4, flags);
	thred1.join(); //just making the threads and running them
	thred2.join(); //join is the program can run, compiler wont compile without
	thred3.join();
	thred4.join();
	thred5.join();
}