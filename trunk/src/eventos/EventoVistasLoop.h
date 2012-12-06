#ifndef EVENTOVISTASLOOP_H_
#define EVENTOVISTASLOOP_H_

#include "Evento.h"
#include "EventoMoverVista.h"

class ResolvedorJugador;

class EventoVistasLoop: public Evento {
	public:
		EventoVistasLoop(VectorChar v);
		EventoVistasLoop();
		~EventoVistasLoop();
		void agregarEventoVista(EventoMoverVista* evento);
		VectorChar serializar();
		void hidratar(VectorChar v);
		void actuar(ResolvedorJugador* res);
		void borrarEventos();
		
	private:
		VectorEventoMV* vectorEventos;
};

#endif /* EVENTOVISTASLOOP_H_ */
