#ifndef MOVIMIENTOIZQUIERDADERECHA_H
#define MOVIMIENTOIZQUIERDADERECHA_H

#include "MovimientoAutomatico.h"
#include "../modelo/Temporizador.h"

class MovimientoIzquierdaDerecha: public MovimientoAutomatico
{
	public:
		MovimientoIzquierdaDerecha(int unDesp, Point* unaPosicion, int potenciaSalto, int velocidad, float piso);
		virtual ~MovimientoIzquierdaDerecha();
		void actualizar();
	
	private:
		int desplazamiento;
		int contador;
		int sentido;
		void moverse();
		void invertirSentido();
};

#endif /* MOVIMIENTOIZQUIERDADERECHA_H */ 
