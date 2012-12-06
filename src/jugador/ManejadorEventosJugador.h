#ifndef MANEJADOREVENTOSJUGADOR_H
#define MANEJADOREVENTOSJUGADOR_H

#include "SDL/SDL.h"
#include "../comun/Definiciones.h"
#include "../eventos/EventoTeclado.h"
#include "../eventos/EventoSalir.h"
#include "ServidorRemoto.h"
#include "ControladorJugador.h"
#include "../app/ControladorApp.h"

class ManejadorEventosJugador
{
	public:
		ManejadorEventosJugador(ServidorRemoto* servRem);
		~ManejadorEventosJugador();
		void manejarEventos();
			
	private:
		static const string TAG;
		ServidorRemoto* servidor;
};

#endif
