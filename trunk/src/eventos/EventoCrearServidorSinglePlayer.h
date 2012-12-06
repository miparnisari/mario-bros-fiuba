#ifndef EVENTOCREARSERVIDORSINGLEPLAYER_H
#define EVENTOCREARSERVIDORSINGLEPLAYER_H

#include <stdio.h>
#include <stdlib.h>
#include "EventoBoton.h"
#include "../app/ControladorApp.h"

class EventoCrearServidorSinglePlayer: public EventoBoton
{
	public:
		EventoCrearServidorSinglePlayer(VectorChar v);
		EventoCrearServidorSinglePlayer();
		void actuar();
};

#endif /* EVENTOCREARSERVIDORSINGLEPLAYER_H */ 
