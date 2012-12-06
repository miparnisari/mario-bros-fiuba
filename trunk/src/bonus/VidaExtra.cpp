#include "VidaExtra.h"
#include "../app/ControladorApp.h"
#include "../server/Servidor.h"

const string VidaExtra::TAG = "VidaExtra";

VidaExtra::VidaExtra(Point* unaPos, int ancho, int alto, int tiempoVida, string nombre, ID unID, float piso)
	: Bonus(unaPos, ancho, alto, 0, tiempoVida, nombre, unID, piso)
{
	this->movimiento = new MovimientoAutomatico(unaPos, 1, 1, piso);
}

VidaExtra::~VidaExtra() 
{
	delete (this->posicion);
	delete (this->movimiento);
	delete (this->temp);
}

void VidaExtra::vivir()
{
	if(this->getActivo() and !this->getMorir()){
		this->movimiento->caerSinSalto();
		this->movimiento->aplicarFuerza(5);
	}
}

int VidaExtra::aplicarColision(Personaje* pers,int resultado, Point posAnterior)
{
	pers->colisionarConVidaExtra(this);
}
