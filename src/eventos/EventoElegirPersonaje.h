#ifndef EVENTOELEGIRPERSONAJE_H_
#define EVENTOELEGIRPERSONAJE_H_
#include "EventoBoton.h"
#include "EventoPersonajeSelect.h"
#include "../app/ControladorApp.h"

class EventoElegirPersonaje: public EventoBoton
{
	public:
		EventoElegirPersonaje(VectorChar v);
		EventoElegirPersonaje();
		void actuar();
};

#endif /* EVENTOELEGIRPERSONAJE_H_ */ 
