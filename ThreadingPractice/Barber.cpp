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
	std::random_device rd;
	std::mt19937 gen(rd()); 
	std::uniform_int_distribution<> distr(2, 15); 


	while (true) {
		customersSm.acquire();// Espera la señal de un hilo cliente para despertar.
		seatsQMutex.lock();
		
		Customer* current = customerQue.front();
		sillasLibres += 1;          // Aumenta en uno el número de sillas libres.
		coutMutex.lock();
		std::cout << "El barbero desperto y esta atentendiendo al cliente " << current->getId()<<"\t\tCantidad de sillas libres: " << sillasLibres  << std::endl;
		coutMutex.unlock();

		seatsQMutex.unlock();

		
		int time = distr(gen);
		std::this_thread::sleep_for(std::chrono::seconds(time));
		seatsQMutex.lock();
		customerQue.pop();
		seatsQMutex.unlock();
		coutMutex.lock();

		std::cout << "El barbero termino de atender al cliente " << current->getId() << " y se fue a dormir" << std::endl;
		coutMutex.unlock();
		barberSm.release();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}