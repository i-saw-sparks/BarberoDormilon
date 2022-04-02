#include "Customer.h"

int Customer::globalId = 0;

Customer::Customer(std::binary_semaphore& b, std::mutex& cm, std::mutex& sqm, std::counting_semaphore<1>& csmph, int& sillas, std::queue<Customer*>& que) :
	barberSem(b),
	coutMutex(cm),
	seatsQMutex(sqm),
	customersSm(csmph),
	sillasLibres(sillas),
	isOut(false),
	customersQue(que){

	this->id = globalId;
	globalId++;
	this->customerTh = std::thread(&Customer::customerProc, this);
}

std::thread& Customer::getThread() {
	return this->customerTh;
}

void Customer::customerProc() {
	using namespace std::literals::chrono_literals;

	seatsQMutex.lock();       // Espera la señal para poder acceder a sillasLibres.
	if (sillasLibres > 0)        
	{
		sillasLibres -= 1;         
		customersQue.push(this);

		
		customersSm.release();
		
		coutMutex.lock();
		std::cout << "El cliente " << id << " esta esperando al barbero\t\t\t\tCantidad de sillas libres: " <<sillasLibres<< std::endl;
		coutMutex.unlock();
		seatsQMutex.unlock();

		// Se le corta el pelo al cliente.
		bool isMe = false;
		
		while (customersQue.front() != this);
		
		barberSem.acquire();
		coutMutex.lock();
		std::cout << "El cliente " << id << " termino de cortarse el pelo y sale de la peluqueria" << std::endl << std::endl;
		coutMutex.unlock();

		
	}
	else                         // Si no hay sillas libres.
	{
		seatsQMutex.unlock();
		coutMutex.lock();
		std::cout << "El cliente " << id << " salio de la peluqueria porque no hay espacio" << std::endl;
		coutMutex.unlock();
		// Manda señal para desbloquear el acceso a sillasLibres.

	}
}

int Customer::getId() {
	return id;
}