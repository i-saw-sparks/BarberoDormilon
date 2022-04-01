// ThreadingPractice.cpp: define el punto de entrada de la aplicación.
//

#include "ThreadingPractice.h"


void ThreadFunc() {
	std::cout << "Hilo secundario" << std::endl;

}

int main()
{
	std::cout << "Hilo principal" << std::endl;
	std::thread worker(ThreadFunc);
	worker.join();
	Customer customer1("Felipe");

	customer1.getThread().join();
	return 0;
}
