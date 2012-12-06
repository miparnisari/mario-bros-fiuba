#ifndef EVENTOVISTANIVEL_H
#define EVENTOVISTANIVEL_H

#include "Evento.h"

class ResolvedorJugador;

class EventoVistaNivel: public Evento
{
	public:
		EventoVistaNivel(VectorChar v);
		EventoVistaNivel(Point* unaPos);
		~EventoVistaNivel();
		VectorChar serializar();
		void hidratar(VectorChar v);
		void actuar(ResolvedorJugador* res);
    private:
		Point* pos;
};

#endif /* EVENTONIVEL_H */ 
