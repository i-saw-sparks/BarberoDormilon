// ThreadingPractice.cpp: define el punto de entrada de la aplicación.
//

#include "ThreadingPractice.h"


int main()
{
	using namespace std::literals::chrono_literals;

	std::mutex customerMutex;
	std::vector <Customer*> customerPool;

	std::cout << "Hilo principal" << std::endl;

	while (true) {
		customerPool.push_back(new Customer(customerMutex));

		std::this_thread::sleep_for(2s);
	}
	return 0;
}
