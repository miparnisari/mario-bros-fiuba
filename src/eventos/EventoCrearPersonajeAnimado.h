#ifndef EVENTOCREARPERSONAJEANIMADO_H
#define EVENTOCREARPERSONAJEANIMADO_H

#include "../modelo/Point.h"
#include "Evento.h"
#include "../bonus/Bonus.h"
class ResolvedorJugador;

class EventoCrearPersonajeAnimado: public Evento
{
	public:
		EventoCrearPersonajeAnimado(VectorChar v);
		EventoCrearPersonajeAnimado(Bonus* pers);
		~EventoCrearPersonajeAnimado();
		VectorChar serializar();
		void hidratar(VectorChar v);
		void actuar(ResolvedorJugador* res);
    private:
		ID myID;
        Point* miPos;
        std::string tipo;
};

#endif /* EVENTOCREARPERSONAJEANIMADO_H */ 
