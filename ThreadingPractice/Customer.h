#pragma once

#include <string>
#include <iostream>
#include <thread>

class Customer {
	

private:
	std::string name;
	std::thread customerTh;
	void customerProc(void);

public:
	std::thread& getThread();
	Customer(const std::string& name);
};