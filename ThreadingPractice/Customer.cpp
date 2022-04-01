#include "Customer.h"

Customer::Customer(const std::string& name):name(name) {
	std::cout << "Customer name: " << this->name;
	this->customerTh = std::thread(&Customer::customerProc, this);
}

std::thread& Customer::getThread() {
	return this->customerTh;
}

void Customer::customerProc() {
	using namespace std::literals::chrono_literals;

	while (true) {
		std::cout << this->name << " is running"<<std::endl;
		std::this_thread::sleep_for(1s);
	}
}