#include "Movimiento.h"
#include <stdio.h>

#define POTENCIA_CAIDA 3
const double G = -9.82;

Movimiento::Movimiento(Point* unaPosicion, int potencia, int vel, float piso) {
	posicion = unaPosicion;
	velocidad.x = 0;
	velocidad.y = 0;
	potenciaSalto = potencia;
	posVertInicial = unaPosicion->y;
	posFinal = piso;
}

Movimiento::~Movimiento() {
//	delete (this->posicion);
}


Point* Movimiento::getPos() {
	this->actualizar();
	return (posicion);
}

void Movimiento::setPos(Point pos) {
	this->posicion->x = pos.x;
	this->posicion->y = pos.y;
}

void Movimiento::aplicarFuerza(double fuerza) {
//	this->posicion->x += fuerza;
//	this->posicion->y += fuerza;
	 velocidad.x = fuerza * 0.1;
}

void Movimiento::detenerEnX() {
	this->velocidad.x = 0;
}

void Movimiento::detenerEnY() {
	this->velocidad.y = 0;
}

bool Movimiento::estaSaltando(){
	return saltando;
}

void Movimiento::setSaltando(bool estado){
	this->saltando = estado;
	if (this->saltando) printf ("setSaltando true\n");
}

bool Movimiento::estaCayendo(){
	return cayendo;
}

void Movimiento::caer() {
}

void Movimiento::saltar() {
}

void Movimiento::actualizar() {
}

float Movimiento::getPiso() {
	return this->posFinal;
}

void Movimiento::caerSinSalto() {

    if (!saltando && !cayendo) {
        //velocidad.y = (-1) * POTENCIA_CAIDA;
    	velocidad.y += (0.001 * G);
        caidaSinSalto = true;
    }
}
