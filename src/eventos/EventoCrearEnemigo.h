#ifndef EVENTOCREARENEMIGO_H
#define EVENTOCREARENEMIGO_H

#include "../modelo/Point.h"
#include "Evento.h"
#include "../modelo/Enemigo.h"
class ResolvedorJugador;

class EventoCrearEnemigo: public Evento
{
	public:
		EventoCrearEnemigo(VectorChar v);
		EventoCrearEnemigo(Enemigo* enemigo);
		~EventoCrearEnemigo();
		VectorChar serializar();
		void hidratar(VectorChar v);
		void actuar(ResolvedorJugador* res);
    private:
		ID myID;
        Point* miPos;
        std::string tipo;
};

#endif /* EVENTOCREARENEMIGO_H */ 
