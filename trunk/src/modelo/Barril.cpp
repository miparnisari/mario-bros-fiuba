#include "Barril.h"
#include "../app/ControladorApp.h"
#include "../modelo/Plataforma.h"
#include "../modelo/Escalera.h"
#include "../modelo/Fuego.h"
#include "../modelo/Tortuga.h"

#define VEL_BARR 2
#define POT_BARR 5

Barril::Barril(Point* punto, int ancho, int alto, string Nombre, ID unID, float piso)
	: Enemigo(punto, ancho, alto, Nombre, unID, piso)
{
	cont = 0;
	myID = unID;
	this->movimiento = new MovimientoAutomatico(punto, POT_BARR, VEL_BARR, piso);
	int random = rand() % 2;
	if (random >= 1) this->direccion = 1;
	else this->direccion = -1;
	this->ultPlataforma = NULL;
	this->ultEscalera = NULL;
	this->bajarEsc = 0;
}

Barril::~Barril(){
	delete this->movimiento;
	delete this->temp;
	//delete this->posicion;
}

void Barril::vivir(){

	this->movimiento->caerSinSalto();

	if(!this->getMorir())
	this->movimiento->aplicarFuerza(this->direccion * 5 * VEL_BARR);


}


int Barril::aplicarColision(Personaje* pers, int result, Point posAnterior){
	
	pers->colisionarConBarril(this);
	return false;
}

void Barril::colisionarConPlataforma(Plataforma* plataforma){

	if(this->ultPlataforma != plataforma){
			int random = rand() % 2;
			if (random >= 1) this->direccion = 1;
			else this->direccion = -1;
		this->ultPlataforma = plataforma;
		plataforma->aplicarColision(this);
	}
	

}

void Barril::colisionarConEscalera(Escalera* escalera){
	if(this->ultEscalera != escalera){
		this->bajarEsc = rand() % 2;
		this->ultEscalera = escalera;
	}
	if(bajarEsc)
		this->getMovimiento()->bajar();
}

void Barril::colisionarConFuego(Fuego* unFuego){
	
	unFuego->colisionarConBarril(this);	
}


void Barril::morir() {
	//Saca al barril del nivel.
	this -> setMorir(true);
	this -> setActivo(false);
}

int Barril::colisionarConTortuga(Tortuga* tortuga, Point posAnterior){

	if (tortuga->esCaparazon and (! tortuga->quieto))
			this->morir();

	return true;
}

