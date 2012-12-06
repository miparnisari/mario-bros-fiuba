#include "Personaje.h"
#include "Elemento.h"
#include "Escalera.h"
#include "Plataforma.h"
#include "PlataformaInclinada.h"
#include "../modelo/Personaje.h"
#include "../app/ControladorApp.h"

const string Personaje::TAG = "Personaje";

Personaje::Personaje(Point* punto, int ancho, int alto, string nombre, float piso) {
	this->posicion = punto;
	this->alto = alto;
	this->ancho = ancho;
	this->nombre = nombre;
	this->movimiento = NULL;
	this->myID = ID_INVALIDO;
}

Personaje::~Personaje() 
{
}

Point* Personaje::getPos() {
	return (this->posicion);
}

void Personaje::setPos(Point* unaPos){
	(this->posicion)->setPos(unaPos);
}

string Personaje::getNombre(){
	return this->nombre;
}

int Personaje::getAncho(){
	return (this->ancho);
}

int Personaje::getAlto(){
	return (this->alto);
}

void Personaje::setID(ID unID){
	this->myID = unID;
}

ID Personaje::getID(){
	return this->myID;
}

int Personaje::colisionaCon(Elemento* elem){
	/*
	//Vertice superior izquierdo
	if (this->verticeDentro(posicion->x, posicion->y, elem->getPos(), elem->getAncho(), elem->getAlto()))
		return 1;
	
	//Vertice superior derecho
	else if	(this->verticeDentro(posicion->x + ancho, posicion->y, elem->getPos(), elem->getAncho(), elem->getAlto()))
		return 1;

//Vertice inferior izquierdo 
	else if	(this->verticeDentro(posicion->x, posicion->y + alto, elem->getPos(), elem->getAncho(), elem->getAlto()))
		return 1;
	//Vertice inferior derecho 
	else if	(this->verticeDentro(posicion->x + ancho, posicion->y + alto, elem->getPos(), elem->getAncho(), elem->getAlto()))
		return 1;
int Elemento::colisionConPersonaje(Personaje* pers){
	// No hay colision
	return 0;
	*/
	return elem->colisionConPersonaje(this);
}



int Personaje::colisionaCon(Personaje* pers){
	//Vertice superior izquierdo
	if (this->verticeDentro(posicion->x, posicion->y, pers->getPos(), pers->getAncho(), pers->getAlto()))
		return 1;
	
	//Vertice superior derecho
	else if	(this->verticeDentro(posicion->x + ancho, posicion->y, pers->getPos(), pers->getAncho(), pers->getAlto()))
		return 1;

	//Vertice inferior izquierdo 
	else if	(this->verticeDentro(posicion->x, posicion->y + alto, pers->getPos(), pers->getAncho(), pers->getAlto()))
		return 1;

	//Vertice inferior derecho 
	else if	(this->verticeDentro(posicion->x + ancho, posicion->y + alto, pers->getPos(), pers->getAncho(), pers->getAlto()))
		return 1;

	// No hay colision
	return 0;
}

bool Personaje::verticeDentro(float xVert, float yVert, Point* p, int ancho, int alto){
//Verifica si un vertice en (xVert, yVert) esta dentro del rectangulo de vertice 
//sup izq en el punto p, con ancho y alto pasados por parametro
	//if ( (xVert >= (p->x + 0.2*ancho)) and (xVert <= p->x + 0.8*ancho) and (yVert >= (p->y + 0.2*alto)) and (yVert <= p->y + 0.8*alto) )
	if ( (xVert >= (p->x + 0.2*ancho)) and (xVert <= p->x + 0.8*ancho) and (yVert >= p->y) and (yVert <= p->y + alto) )
		return true;
	return false;
}


void Personaje::aplicarRozamiento(float rozamiento){
	this->movimiento->setRozamiento(rozamiento);
}

MovimientoPersonaje* Personaje::getMovimiento(){
	return (this->movimiento);
}

void Personaje::aplicarMovimiento(){}

int Personaje::aplicarColision(Personaje* pers, int result, Point posAnterior){return false;}

int Personaje::aplicarColision(Elemento* elem, int result, Point posAnterior){return false;}

int Personaje::colisionarConHongo(Hongo* hongo, Point posAnterior){ return false;}

int Personaje::colisionarConTortuga(Tortuga* tortuga, Point posAnterior){ return false;}

