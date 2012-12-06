#ifndef EVENTOJUGADORCONECTADO_H
#define EVENTOJUGADORCONECTADO_H

#include "Evento.h"
#include "../comun/Utilitario.h"
#include "../jugador/ResolvedorJugador.h"

class EventoJugadorConectado: public Evento
{
	public:
		EventoJugadorConectado(VectorChar v);
		EventoJugadorConectado(ID unID);
		VectorChar serializar();
		void hidratar(VectorChar v);
		void actuar(ResolvedorJugador* res);
};

#endif /* EVENTOJUGADORCONECTADO_H */ 
