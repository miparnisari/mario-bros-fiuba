#include "MovimientoAutomatico.h"


MovimientoAutomatico::MovimientoAutomatico(Point* unaPosicion, int potencia, int velocidad, float piso)
	: MovimientoPersonaje(unaPosicion, potencia, velocidad, piso)
{
	
}


MovimientoAutomatico::~MovimientoAutomatico()
{
	
}

void MovimientoAutomatico::actualizar() {
	
	//velocidad.x *= 1; //ROZAMIENTO;

	posicion->x += velocidad.x;
	posicion->y -= velocidad.y * 0.1;
}

