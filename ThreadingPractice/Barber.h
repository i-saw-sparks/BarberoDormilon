#pragma once

#include <thread>
#include <mutex>
#include <semaphore>
#include <iostream>
#include <queue>
#include <random>
#include "Customer.h"

class Barber {
private:
	std::binary_semaphore barberSm{0};
	std::counting_semaphore<1>& customersSm;
	std::queue<Customer*>& customerQue;
	std::thread barberTh;
	std::mutex& seatsQMutex;
	std::mutex& coutMutex;
	int& sillasLibres;

	void barberProc();

public:
	Barber(std::mutex&, std::mutex&, std::counting_semaphore<1>&, int&, std::queue<Customer*>&);
	std::binary_semaphore& getSem();

};