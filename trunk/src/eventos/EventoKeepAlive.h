#ifndef EVENTOKEEPALIVE_H
#define EVENTOKEEPALIVE_H

#include "../jugador/ResolvedorJugador.h"
#include "../server/ResolvedorServidor.h"
#include "Evento.h"

class EventoKeepAlive: public Evento
{
	public:
		EventoKeepAlive(VectorChar v);
		EventoKeepAlive(ID unID);
		VectorChar serializar();
		void hidratar(VectorChar v);
        Evento* actuar(ResolvedorServidor* res);
        void actuar(ResolvedorJugador* res);
    private: 
        VectorChar personaje;
};

#endif /* EVENTOKEEPALIVE_H */ 
