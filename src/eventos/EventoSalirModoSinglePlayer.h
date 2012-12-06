#ifndef EVENTOSALIRMODOSINGLEPLAYER_H
#define EVENTOSALIRMODOSINGLEPLAYER_H

#include <stdio.h>
#include <stdlib.h>
#include "EventoBoton.h"
#include "../app/ControladorApp.h"

class EventoSalirModoSinglePlayer: public EventoBoton
{
	public:
		EventoSalirModoSinglePlayer(VectorChar v);
		EventoSalirModoSinglePlayer(std::string nombreVentana);
		void actuar();
	
	private:
		std::string nombreVentana;
};

#endif /* EVENTOSALIRMODOSINGLEPLAYER_H */ 
