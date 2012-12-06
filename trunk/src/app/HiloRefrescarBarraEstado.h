#ifndef HILOREFRESCARBARRAESTADO_H
#define HILOREFRESCARBARRAESTADO_H

#include "../comun/Hilo.h"
#include "../comun/Mutex.h"
#include "../vista/Pantalla.h"

class BarraDeEstado;

class HiloRefrescarBarraEstado: public Hilo
{
	public:
		HiloRefrescarBarraEstado(SDL_Surface* surface, BarraDeEstado* unaB, Mutex* unMut);
		~HiloRefrescarBarraEstado();
		void correr();
	
	private:
		Mutex* mutex;
		SDL_Surface* surface;
		BarraDeEstado* barra;
};

#endif /* HILOREFRESCARBARRAESTADO_H */ 
