#ifndef EVENTOMOVERVISTA_H
#define EVENTOMOVERVISTA_H

#include "../modelo/Point.h"
#include "Evento.h"

class ResolvedorJugador;

class EventoMoverVista: public Evento
{
	public:
		EventoMoverVista(VectorChar v);
		EventoMoverVista(ID unID, Point* unPunto, std::string unMov);
		~EventoMoverVista();
		VectorChar serializar();
		void hidratar(VectorChar v);
		void actuar(ResolvedorJugador* res);
    private:
        Point* miPos;
        std::string miMov;
};

#endif /* EVENTOMOVERVISTA_H */ 
