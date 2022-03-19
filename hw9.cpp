#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "hw9.h"

volatile int* make_buffer(int size){
	int n = size; //create n from 0-9999999
	volatile int *arr = new int[n]; //generate array 
	for (int i = 0; i < n; i++){
		arr[i] = rand() % 100; //fill array
	}
	return arr;
}

void benchmarking() {
	printf("BS = Buffer size, AAT = Average access time \n");
	for (int y = 0; y < 5; y++){

		int n; //size of buffer
		float avg_time; //avg time per access of byte
		clock_t length; //total length of time
		int x; //number of times it takes to access
		n = rand() % 10000000;
		
		volatile int *arr = make_buffer(n);

		x = rand() % 10000;
		length = clock();
		for (int i = 0; i < x; i++){
			volatile int arr[i];
		}
		length = clock() - length; //total time it takes to acces x times
		avg_time = ((float)length)/CLOCKS_PER_SEC; // time it takes to access one byte
		printf("BS (KBs): %d | AAT: %f (%ld Ticks) \n", n / 1000, avg_time, length);
		delete arr;
	}
}

int main() {
	benchmarking();

	//uncomment whichever test needs to run next
	clock_t length = clock();
	//run_barriers();
	runcen();
	//mcsrun();
	length = clock() - length;
	float avg_time = ((float)length)/CLOCKS_PER_SEC;
	printf("time: %f (%ld Ticks) \n", avg_time, length);
	//simple but effective enough timing method, have to manually divide by number of threads
	return 0;
}