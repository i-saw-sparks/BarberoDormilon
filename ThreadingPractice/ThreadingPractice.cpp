// ThreadingPractice.cpp: define el punto de entrada de la aplicación.
//

#include "ThreadingPractice.h"


int main()
{
	std::mutex customerMutex;
	std::cout << "Hilo principal" << std::endl;
	Customer customer1("Felipe", customerMutex);
	Customer customer2("Claudia", customerMutex);
	Customer customer3("Oscar", customerMutex);

	customer1.getThread().join();
	customer2.getThread().join();
	customer3.getThread().join();
	return 0;
}
