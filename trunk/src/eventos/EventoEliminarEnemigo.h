#ifndef EVENTOELIMINARENEMIGO_H
#define EVENTOELIMINARENEMIGO_H

#include "Evento.h"
#include "../modelo/Enemigo.h"
class ResolvedorJugador;

class EventoEliminarEnemigo: public Evento
{
	public:
		EventoEliminarEnemigo(VectorChar v);
		EventoEliminarEnemigo(Enemigo* enemigo);
		EventoEliminarEnemigo(ID unID, std::string unNombre);
		VectorChar serializar();
		void hidratar(VectorChar v);
		void actuar(ResolvedorJugador* res);
    private:
		ID myID;
        std::string tipo;
};

#endif /* EVENTOELIMINARENEMIGO_H */ 
