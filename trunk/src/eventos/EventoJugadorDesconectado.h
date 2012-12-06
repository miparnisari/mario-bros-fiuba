#ifndef EVENTOJUGADORDESCONECTADO_H
#define EVENTOJUGADORDESCONECTADO_H
#include "../jugador/ResolvedorJugador.h"
#include "Evento.h"
#include "../comun/Utilitario.h"

class EventoJugadorDesconectado: public Evento
{
	public:
		EventoJugadorDesconectado(VectorChar v);
		EventoJugadorDesconectado(ID unID);
		VectorChar serializar();
		void hidratar(VectorChar v);
		void actuar(ResolvedorJugador* res);
};

#endif /* EVENTOJUGADORDESCONECTADO_H */ 
