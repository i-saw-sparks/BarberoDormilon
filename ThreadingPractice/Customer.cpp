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
	if (sillasLibres > 0)        // Si hay alguna silla libre, se sienta en una.
	{
		sillasLibres -= 1;         // Decrementando el valor de sillasLibres en 1.
		customersQue.push(this);

		customersSm.release(); // Manda señal al barbero de que hay un cliente disponible.
		seatsQMutex.unlock();// Manda señal para desbloquear el acceso a sillasLibres.
		coutMutex.lock();
		std::cout << "El cliente " << id << " esta esperando al barbero" << std::endl;
		coutMutex.unlock();

		// Se le corta el pelo al cliente.
		do {
			barberSem.acquire();
		} while (customersQue.front() != this);

		coutMutex.lock();
		std::cout << "El cliente " << id << " se esta cortando el pelo" << std::endl;
		coutMutex.unlock();
	}
	else                         // Si no hay sillas libres.
	{
		seatsQMutex.unlock();
		coutMutex.lock();
		std::cout << "El cliente " << id << " salio de la peluqueria porque no hay espacio" << std::endl;
		coutMutex.unlock();
		// Manda señal para desbloquear el acceso a sillasLibres.
		// El cliente se va de la barbería y no manda la señal de cliente disponible.	
	}
	//isOut = true;
}

int Customer::getId() {
	return id;
}