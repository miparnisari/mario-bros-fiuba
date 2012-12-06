#ifndef EVENTOPERSONAJESELECT_H
#define EVENTOPERSONAJESELECT_H
#include "../jugador/ResolvedorJugador.h"
#include "../server/ResolvedorServidor.h"
#include "Evento.h"

class EventoPersonajeSelect: public Evento
{
	public:
		EventoPersonajeSelect(VectorChar v);
		EventoPersonajeSelect(ID unID,  std::string unPersonaje);
		~EventoPersonajeSelect();
		VectorChar serializar();
		void hidratar(VectorChar v);
		void actuar(ResolvedorJugador* res);
		Evento* actuar(ResolvedorServidor* res);
    private: 
         std::string personaje;
};

#endif /* EVENTOPERSONAJESELECT_H */ 
