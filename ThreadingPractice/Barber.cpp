#include "Barber.h"

Barber::Barber(std::mutex& cm, std::mutex& sqm, std::counting_semaphore<1>& csmph, int& sillas, std::queue<Customer*>& que) :
	coutMutex(cm),
	seatsQMutex(sqm),
	customersSm(csmph),
	sillasLibres(sillas),
	customerQue(que) {
	this->barberTh = std::thread(&Barber::barberProc, this);
}

std::binary_semaphore& Barber::getSem() {
	return this->barberSm;
}

void Barber::barberProc() {
	using namespace std::literals::chrono_literals;

	while (true) {
		customersSm.acquire();// Espera la señal de un hilo cliente para despertar.
		coutMutex.lock();
		std::cout << "El barbero desperto" << std::endl;
		coutMutex.unlock();
		seatsQMutex.lock();// (Ya está despierto) Espera señal para poder modificar sillasLibres.
		Customer* current = customerQue.front();
		sillasLibres += 1;          // Aumenta en uno el número de sillas libres.
		coutMutex.lock();
		std::cout << "El barbero paso al cliente " << current->getId() << std::endl;
		coutMutex.unlock();

		seatsQMutex.unlock();

		std::this_thread::sleep_for(8s);
		seatsQMutex.lock();
		customerQue.pop();
		seatsQMutex.unlock();
		coutMutex.lock();

		std::cout << "El barbero termino de atender al cliente " << current->getId() << " y se fue a dormir" << std::endl;
		coutMutex.unlock();
		barberSm.release();
	}
}