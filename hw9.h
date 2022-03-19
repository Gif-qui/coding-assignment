#pragma once

//#include "hw9.cpp"
//#include "threading.cpp"
//#include "centralized.cpp"asdasd
volatile int* make_buffer(int size);

void benchmarking();

void cbar();

void centest(int i);

void runcen();

void dbarr(bool **flags, int tid);

void disstest(int id, bool **flags);

void run_barriers();

void mbarr(bool **flags, int tid);

void mcstest(bool **flags, int tid);

void mcsrun();