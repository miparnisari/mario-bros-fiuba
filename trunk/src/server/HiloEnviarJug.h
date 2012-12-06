#ifndef HILOENVIARJUG_H
#define HILOENVIARJUG_H

#include "../comun/Hilo.h"
#include "../comun/Definiciones.h"
#include "../server/JugadorRemoto.h"
class HiloEnviarJug: public Hilo
{
	public:
		HiloEnviarJug(Conexiones* conex, ListaEventos* listaEv, Mutex* unMut);
		~HiloEnviarJug();
		void correr();

			
	private:
		Mutex* m;
        Conexiones* conexiones;
		ListaEventos* listaEventos;
};

#endif
