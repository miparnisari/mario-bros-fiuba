#ifndef EVENTOCREARSERVIDOR_H
#define EVENTOCREARSERVIDOR_H

#include <stdio.h>
#include <stdlib.h>
#include "EventoBoton.h"
#include "../app/ControladorApp.h"

class EventoCrearServidor: public EventoBoton
{
	public:
		EventoCrearServidor(VectorChar v);
		EventoCrearServidor();
		void actuar();
};

#endif /* EVENTOCREARSERVIDOR_H */ 
