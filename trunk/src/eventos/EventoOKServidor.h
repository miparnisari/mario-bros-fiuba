#ifndef EVENTOOKSERVIDOR_H
#define EVENTOOKSERVIDOR_H
#include "../jugador/ResolvedorJugador.h"
#include "../server/ResolvedorServidor.h"
#include "Evento.h"

class EventoOKServidor: public Evento
{
	public:
		EventoOKServidor(VectorChar v);
		EventoOKServidor(ID unID);
		VectorChar serializar();
		void hidratar(VectorChar v);
		void actuar(ResolvedorJugador* res);
        Evento* actuar(ResolvedorServidor* res);
    private: 
        VectorChar personaje;
};

#endif /* EVENTOOKSERVIDOR_H */ 
