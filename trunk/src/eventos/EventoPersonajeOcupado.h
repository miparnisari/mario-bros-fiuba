#ifndef EVENTOPERSONAJEOCUPADO_H
#define EVENTOPERSONAJEOCUPADO_H

#include "Evento.h"

class EventoPersonajeOcupado: public Evento
{
	public:
		EventoPersonajeOcupado(VectorChar v);
		EventoPersonajeOcupado();
		VectorChar serializar();
		void hidratar(VectorChar v);
		void actuar(ResolvedorJugador* res);

	private:
		static const std::string TAG;
		std::string personaje;
};

#endif /* EVENTOPERSONAJEOCUPADO_H */ 
