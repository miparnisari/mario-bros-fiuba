#ifndef EVENTOCONECTAR_H
#define EVENTOCONECTAR_H

#include "EventoBoton.h"
#include "../app/ControladorApp.h"

class EventoConectar: public EventoBoton
{
	public:
		EventoConectar(VectorChar v);
		EventoConectar();
		void actuar();
};

#endif /* EVENTOCONECTAR_H */ 
