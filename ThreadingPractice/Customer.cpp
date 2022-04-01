#include "Customer.h"

Customer::Customer(const std::string& name, std::mutex& m):name(name), customerMutex(m) {
	this->customerTh = std::thread(&Customer::customerProc, this);
}

std::thread& Customer::getThread() {
	return this->customerTh;
}

void Customer::customerProc() {
	using namespace std::literals::chrono_literals;

	while (true) {
		customerMutex.lock();
		std::cout << this->name << " is running"<<std::endl;
		customerMutex.unlock();
		std::this_thread::sleep_for(1s);
	}
}