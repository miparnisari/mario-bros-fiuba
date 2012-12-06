#ifndef EVENTOACTIVARVENTANA_H
#define EVENTOACTIVARVENTANA_H

#include <stdio.h>
#include <stdlib.h>
#include "EventoBoton.h"
#include "../app/ControladorApp.h"

class EventoActivarVentana: public EventoBoton
{
	public:
		EventoActivarVentana(VectorChar v);
		EventoActivarVentana(std::string nombreVentana);
		void actuar();
	
	private:
		std::string nombreVentana;
};

#endif /* EVENTOACTIVARVENTANA_H */ 
