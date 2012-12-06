#ifndef MOVIMIENTOAUTOMATICO_H
#define MOVIMIENTOAUTOMATICO_H

#include "MovimientoPersonaje.h"

// CLASE ABSTRACTA

class MovimientoAutomatico: public MovimientoPersonaje
{
	public:
		MovimientoAutomatico(Point* unaPosicion, int potencia, int velocidad, float piso);
		virtual ~MovimientoAutomatico();
		virtual void actualizar();
	
	protected:

};

#endif /* MOVIMIENTOAUTOMATICO_H */ 
