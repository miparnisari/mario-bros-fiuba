#ifndef EVENTOMOVERVISTAENEMIGO_H
#define EVENTOMOVERVISTAENEMIGO_H

#include "../modelo/Point.h"
#include "Evento.h"
class Enemigo;
class ResolvedorJugador;

class EventoMoverEnemigo: public Evento
{
	public:
		EventoMoverEnemigo(VectorChar v);
		EventoMoverEnemigo(Enemigo* enemigo);
		~EventoMoverEnemigo();
		VectorChar serializar();
		void hidratar(VectorChar v);
		void actuar(ResolvedorJugador* res);
    private:
        Point* miPos;
        std::string tipoEnemigo;
        std::string tipoMov;
};

#endif /* EVENTOMOVERVISTAENEMIGO_H */ 
