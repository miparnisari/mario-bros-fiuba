#include "Armadura.h"
#include "../app/ControladorApp.h"
#include "../server/Servidor.h"

const string Armadura::TAG = "Armadura";

Armadura::Armadura(Point* unaPos, int ancho, int alto, int tiempoVida, string nombre, ID unID, float piso)
	: Bonus(unaPos, ancho, alto, 0, tiempoVida, nombre, unID, piso)
{
	this->movimiento = new MovimientoAutomatico(unaPos, 1, 1, piso);
}

Armadura::~Armadura()
{
	delete (this->posicion);
	delete (this->movimiento);
	delete (this->temp);
}

void Armadura::vivir() 
{
	if (this->getActivo() and !this->getMorir()){
		this->movimiento->caerSinSalto();
		this->movimiento->aplicarFuerza(4);
	}
}

int Armadura::aplicarColision(Personaje* pers,int resultado, Point posAnterior)
{
	pers->colisionarConArmadura(this);
}

void Armadura::colisionarConEscalera(Escalera* escalera)
{
}

