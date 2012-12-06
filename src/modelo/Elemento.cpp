#include "Point.h"
#include "Elemento.h"

Elemento::Elemento(Point* unaPos){
	posicion = unaPos;
	ancho = 0;
	alto = 0;
}

Elemento::~Elemento(){
	delete (this->posicion);
}

Point* Elemento::getPos(){
	return posicion;
}

void Elemento::setPos(Point* otroPunto){
	(this->posicion)->setPos(otroPunto);
}

void Elemento::setAncho(int ancho){
	this->ancho = ancho;	
}

void Elemento::setAlto(int alto){
	this->alto = alto;	
}

int Elemento::getAlto(){
	return alto;
}

int Elemento::getAncho(){
	return ancho;
}

int Elemento::colisionaCon(Elemento* elem){
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

	// No hay colision
	return 0;	
}

int Elemento::colisionaCon(Personaje* pers){
	
	//Vertice superior izquierdo
	if (this->verticeDentro(posicion->x, posicion->y, pers->getPos(), pers->getAncho()*SENSIBILIDADELEM, pers->getAlto()*SENSIBILIDADELEM))
		return 1;
	
	//Vertice superior derecho
	else if	(this->verticeDentro(posicion->x + ancho, posicion->y, pers->getPos(), pers->getAncho()*SENSIBILIDADELEM, pers->getAlto()*SENSIBILIDADELEM))
		return 1;

	//Vertice inferior izquierdo 
	else if	(this->verticeDentro(posicion->x, posicion->y + alto, pers->getPos(), pers->getAncho()*SENSIBILIDADELEM, pers->getAlto()*SENSIBILIDADELEM)) 
		return 1;

	//Vertice inferior derecho 
	else if	(this->verticeDentro(posicion->x + ancho, posicion->y + alto, pers->getPos(), pers->getAncho()*SENSIBILIDADELEM, pers->getAlto()*SENSIBILIDADELEM))
		return 1;

	// No hay colision
	return 0;
}

int Elemento::colisionConPersonaje(Personaje* pers){
	
	//Vertice superior izquierdo
	if (this->verticeDentro(pers->getPos()->x, pers->getPos()->y, this->getPos(), this->getAncho(), this->getAlto()))
		return 1;
	
	//Vertice superior derecho
	else if	(this->verticeDentro(pers->getPos()->x + pers->getAncho(), pers->getPos()->y, this->getPos(), this->getAncho(), this->getAlto()))
		return 1;

	//Vertice inferior izquierdo 
	else if	(this->verticeDentro(pers->getPos()->x, pers->getPos()->y + pers->getAlto(), this->getPos(), this->getAncho(), this->getAlto()))
		return 1;
	//Vertice inferior derecho 
	else if	(this->verticeDentro(pers->getPos()->x + pers->getAncho(), pers->getPos()->y + pers->getAlto(), this->getPos(), this->getAncho(), this->getAlto()))
		return 1;

	// No hay colision
	return 0;
	
}

bool Elemento::verticeDentro(float xVert, float yVert, Point* p, int ancho, int alto){
//Verifica si un vertice en (xVert, yVert) esta dentro del rectangulo de vertice 
//sup izq en el punto p, con ancho y alto pasados por parametro
	if ( (xVert >= p->x) and (xVert <= p->x + ancho) and (yVert >= p->y) and (yVert <= p->y + alto) )
		return true;
	return false;	
}

int Elemento::aplicarColision(Elemento* elem,int resultado, Point posAnterior){return false;}

int Elemento::aplicarColision(Personaje* pers,int resultado, Point posAnterior){return false;}

void Elemento::vivir(){
}

