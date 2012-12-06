#include "Princesa.h"
#include "../eventos/EventoCrearEnemigo.h"
#include "../app/ControladorApp.h"
#include "../modelo/Nivel.h"

Princesa::Princesa(Point* punto, int ancho, int alto, string nombre, ID unID, Nivel* unNivel)
	: Enemigo(punto, ancho, alto, nombre, unID, unNivel->getPiso())
{
	this->nivel = unNivel;
	this->movimiento = NULL;
}


Princesa::~Princesa()
{
	delete this->movimiento;
	delete this->temp;
	//delete this->posicion;
}

void Princesa::mover(int result) {
//	this->mov->actualizar();
	//this->setPos(this->mov->getPos());
}

void Princesa::vivir(){
}

int Princesa::aplicarColision(Personaje* pers, int result, Point posAnterior){
	if (!pers){
		printf("PERS ES NULL");
		return false;
	}
	pers->colisionarConPrincesa(this);
	return false;
}
