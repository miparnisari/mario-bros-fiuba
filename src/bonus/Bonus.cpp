#include "Bonus.h"

const string Bonus::TAG = "Bonus";

Bonus::Bonus(Point* unaPos, int ancho, int alto, int velocidad, int tiempoVida, string nombre, ID unID, float piso)
	: Enemigo(unaPos, ancho, alto, nombre, unID, piso)
{
	this->tiempoVidaSegs = tiempoVida;
	this->temp = new Temporizador();
	this->temp->setIntervalo(tiempoVida);
	this->temp->setTiempoInicial();
	this->movimiento = new MovimientoPersonaje(unaPos, 0, 0, piso);
}

void Bonus::setMovimiento(MovimientoAutomatico* unMov)
{

}

Bonus::~Bonus()
{
}

void Bonus::vivir() 
{
	// Cada bonus sabe que hacer
}

int Bonus::aplicarColision(Personaje* prot,int resultado) 
{
	// Cada bonus sabe como colisionar
}
