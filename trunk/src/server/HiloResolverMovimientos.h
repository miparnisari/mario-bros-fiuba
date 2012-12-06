#ifndef HILORESOLVERMOVIMIENTOS_H
#define HILORESOLVERMOVIMIENTOS_H

#include "../comun/Hilo.h"
#include "../comun/Definiciones.h"
#include "../comun/Mutex.h"
class Juego;
class ControladorJuego;
class ControladorApp;

class HiloResolverMovimientos: public Hilo
{
	public:
		HiloResolverMovimientos(ListaEstados* listaEs, ListaEventos* listaEv, Mutex* unMut);
		~HiloResolverMovimientos();
		void correr();
		bool activo();
			
	private:
		Mutex* m;
        ListaEstados* listaEstados;
		ListaEventos* listaEventos;
};

#endif
