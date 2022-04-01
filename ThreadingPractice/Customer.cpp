#include "Customer.h"

int Customer::globalId = 0;

Customer::Customer(std::mutex& m):customerMutex(m) {
	this->id = globalId;
	globalId++;
	this->customerTh = std::thread(&Customer::customerProc, this);
}

std::thread& Customer::getThread() {
	return this->customerTh;
}

void Customer::customerProc() {
	using namespace std::literals::chrono_literals;

	while (true) {
		customerMutex.lock();
		std::cout << this->id << " is running"<<std::endl;
		customerMutex.unlock();
		std::this_thread::sleep_for(1s);
	}
}