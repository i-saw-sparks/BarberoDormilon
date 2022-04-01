#pragma once

#include <string>
#include <iostream>
#include <thread>
#include <mutex>

class Customer {
	

private:
	std::thread customerTh;
	std::mutex& customerMutex;
	static int globalId;
	int id;

	void customerProc(void);

public:
	

	std::thread& getThread();
	Customer(std::mutex& m);
};