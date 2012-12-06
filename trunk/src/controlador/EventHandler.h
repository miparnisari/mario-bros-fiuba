#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include <map>
#include "SDL/SDL.h"
#include "../comun/Definiciones.h"
#include "../controlador/Timer.h"
#include "../movimientos/MovimientoPersonaje.h"
#include "../eventos/EventoMoverVista.h"

class Juego;

class EventHandler
{
	public:
		EventHandler();
		~EventHandler();
		void manejarEstados(ListaEventos* listaEv, ListaEstados* lista, Mutex* m);
        void manejarEventos(Juego* unJuego);
};

#endif /* EVENTHANDLER_H */
