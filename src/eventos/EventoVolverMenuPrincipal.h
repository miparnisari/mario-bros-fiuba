#ifndef EVENTOVOLVERMENUPRINCIPAL_H
#define EVENTOVOLVERMENUPRINCIPAL_H

#include "Evento.h"
#include "EventoBoton.h"
#include "../jugador/ResolvedorJugador.h"
#include "../comun/Utilitario.h"

class EventoVolverMenuPrincipal: public EventoBoton
{
	public:
		EventoVolverMenuPrincipal();
		~EventoVolverMenuPrincipal();
		void actuar();

};

#endif /* EVENTOVOLVERMENUPRINCIPAL_H */ 
