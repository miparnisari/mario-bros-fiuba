#ifndef EVENTOBOTON_H
#define EVENTOBOTON_H

#include "Evento.h"

class EventoBoton: public Evento
{
	public:
		EventoBoton();
		virtual ~EventoBoton();
		VectorChar serializar();
		void hidratar(VectorChar v);
		virtual void actuar() = 0;
};

#endif /* EVENTOBOTON_H */ 
