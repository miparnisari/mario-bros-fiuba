#ifndef EVENTOGAMEOVER_H
#define EVENTOGAMEOVER_H

#include "Evento.h"

class ResolvedorJugador;

class EventoGameOver: public Evento
{
	public:
		EventoGameOver(VectorChar v);
		EventoGameOver(std::string estado);
		VectorChar serializar();
		void hidratar(VectorChar v);
		void actuar(ResolvedorJugador* res);
    private:
		std::string estado;
};

#endif /* EVENTOGAMEOVER_H */ 
