#pragma once

#include <string>
#include <iostream>
#include <thread>
#include <mutex>
#include <semaphore>
#include <queue>

class Customer {
	

private:
	std::thread customerTh;
	std::binary_semaphore& barberSem;
	std::mutex& seatsQMutex;
	std::counting_semaphore<1>& customersSm;
	std::mutex& coutMutex;
	std::queue<Customer*>& customersQue;

	int& sillasLibres;

	static int globalId;
	int id;

	void customerProc(void);

public:
	
	bool isOut;
	std::thread& getThread();
	int getId();
	Customer(std::binary_semaphore&, std::mutex&, std::mutex&, std::counting_semaphore<1>&, int&, std::queue<Customer*>&);
};