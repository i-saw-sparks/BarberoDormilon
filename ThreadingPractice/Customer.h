#pragma once

#include <string>
#include <iostream>
#include <thread>
#include <mutex>

class Customer {
	

private:
	std::string name;
	std::thread customerTh;
	std::mutex& customerMutex;
	void customerProc(void);

public:
	std::thread& getThread();
	Customer(const std::string& name, std::mutex& m);
};