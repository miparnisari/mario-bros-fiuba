#ifndef EVENTOINICIARJUEGO_H
#define EVENTOINICIARJUEGO_H
#include "../jugador/ResolvedorJugador.h"
#include "Evento.h"

class EventoIniciarJuego: public Evento
{
	public:
		EventoIniciarJuego(VectorChar v);
		EventoIniciarJuego(ID unID);
		VectorChar serializar();
		void hidratar(VectorChar v);
		void actuar(ResolvedorJugador* res);
};

#endif /* EVENTOSINICIARJUEGO_H */ 
