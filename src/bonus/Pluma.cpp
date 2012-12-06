#include "Pluma.h"

const string Pluma::TAG = "Pluma";

Pluma::Pluma(Point* unaPos, int ancho, int alto, int tiempoVida, string nombre, ID unID, float piso)
	: Bonus(unaPos, ancho, alto, 0, tiempoVida, nombre, unID, piso)
{

}

Pluma::~Pluma()
{
	delete(this->posicion);
	delete this->temp;
}

void Pluma::vivir() 
{
	if (this->temp->puedeRealizarAccion()) {
		this->setMorir(true);
		return;
	}
}

int Pluma::aplicarColision(Personaje* pers,int resultado, Point posAnterior) 
{
	pers->colisionarConPluma(this, posAnterior);
	return false;
}
