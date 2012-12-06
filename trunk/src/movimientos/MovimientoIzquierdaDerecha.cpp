#include "MovimientoIzquierdaDerecha.h"


MovimientoIzquierdaDerecha::MovimientoIzquierdaDerecha(int unDesp, Point* unaPosicion, int potenciaSalto, int velocidad, float piso)
	: MovimientoAutomatico(unaPosicion, potenciaSalto, velocidad,  piso)
{
	this->desplazamiento = unDesp;
	this->contador = unDesp;
	this->sentido = -1; // Empieza yendo a la izquierda
}


MovimientoIzquierdaDerecha::~MovimientoIzquierdaDerecha(){
	
}

void MovimientoIzquierdaDerecha::moverse() {
	this->aplicarFuerza(velocidad.x * sentido);
}

void MovimientoIzquierdaDerecha::invertirSentido() {
	this->sentido = this->sentido * (-1);
}

void MovimientoIzquierdaDerecha::actualizar() {

	if (this->contador > 0) {
		this->moverse();
		contador --;
	}
	else {
		this->detenerEnX();
		this->invertirSentido();
		this->contador = this->desplazamiento;
	}
}
