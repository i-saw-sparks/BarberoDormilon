// ThreadingPractice.cpp: define el punto de entrada de la aplicación.
//

#include "ThreadingPractice.h"


int main()
{
	using namespace std::literals::chrono_literals;

	
	std::mutex coutMutex;
	std::mutex seatsQMutex;
	std::counting_semaphore<1> customersSm(0);

	std::vector<Customer*> customers;
	std::queue<Customer*> customerQue;

	int sillasLibres = 3;

	Barber mainBarber(coutMutex, seatsQMutex, customersSm, sillasLibres, customerQue);

	while (true) {
		
		coutMutex.lock();
		Customer* newCustomer = new Customer(mainBarber.getSem(), coutMutex, seatsQMutex, customersSm, sillasLibres, customerQue);
		customers.push_back(newCustomer);
		std::cout << "customer " << newCustomer->getId()<<" llego a la peluqueria" << std::endl;
		coutMutex.unlock();
		std::this_thread::sleep_for(2s);

		/*
		int size = customers.size();
		for (int i = 0; i < size; i++) {
			if (customers[i]->isOut) {
				delete customers[i];
				customers[i] = nullptr;
			}
		}
		std::remove_if(customers.begin(), customers.end(), [](Customer* c) {return c == nullptr; });
		*/
	}
	return 0;
}
