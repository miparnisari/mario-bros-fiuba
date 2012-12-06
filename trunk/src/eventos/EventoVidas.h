#ifndef EVENTOVIDAS_H
#define EVENTOVIDAS_H

#include "Evento.h"

class ResolvedorJugador;

class EventoVidas: public Evento
{
	public:
		EventoVidas(VectorChar v);
		EventoVidas(int cantVidas);
		VectorChar serializar();
		void hidratar(VectorChar v);
		void actuar(ResolvedorJugador* res);
    private:
		int cantVidas;
};

#endif /* EVENTOVIDAS_H */ 
