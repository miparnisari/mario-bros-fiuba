#ifndef EVENTOTERMINARSERVIDOR_H
#define EVENTOTERMINARSERVIDOR_H
#include "EventoBoton.h"
#include "../app/ControladorApp.h"

class EventoTerminarServidor: public EventoBoton
{
	public:
		EventoTerminarServidor(VectorChar v);
		EventoTerminarServidor();
		void actuar();
};

#endif /* EVENTOTERMINARSERVIDOR_H */ 
