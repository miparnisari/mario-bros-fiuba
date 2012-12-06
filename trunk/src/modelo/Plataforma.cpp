#include "Plataforma.h"

const string Plataforma::TAG = "Plataforma";

Plataforma::Plataforma(Point* unaPos, int ancho, int alto, float rozamiento): Elemento(unaPos) {
	Logger::info  (TAG , "Construccion correcta");

	// atributos de elemento
	this->ancho = ancho;
	this->alto = alto;
	this->rozamiento = rozamiento;
}

Plataforma::~Plataforma(){
}

int Plataforma::aplicarColision(Personaje* pers, int res, Point posAnterior){
	
	if(((pers->getPos()->y + pers->getAlto() > posicion->y) || (pers->getPos()->y < posicion->y + alto)) &&
		((posAnterior.x < posicion->x + ancho) || ((posAnterior.x  + pers->getAncho() > posicion->x ) && (posAnterior.x  + pers->getAncho() < posicion->x + ancho)))){
			pers->getMovimiento()->getPos()->y = posAnterior.y;
	}
/*
	if(( ((pers->getPos()->y > posicion->y) && (pers->getPos()->y + pers->getAlto() < posicion->y + alto)) ||
		((pers->getPos()->y > posicion->y) && (pers->getPos()->y + pers->getAlto() > posicion->y + alto)) ||
		((pers->getPos()->y < posicion->y) && (pers->getPos()->y + pers->getAlto() > posicion->y)) ||
		((pers->getPos()->y < posicion->y + alto) && (pers->getPos()->y + pers->getAlto() > posicion->y + alto))
		
		)	&& ((pers->getPos()->x < posicion->x + ancho) || (pers->getPos()->x  + pers->getAncho() > posicion->x ))){
		pers->getMovimiento()->posicion->x = posAnterior.x;	
*/		
		
	bool choqueVertical =  (((pers->getPos()->y > posicion->y) && (pers->getPos()->y + pers->getAlto() < posicion->y + alto)) ||
		((pers->getPos()->y > posicion->y) && (pers->getPos()->y + pers->getAlto() > posicion->y + alto)) ||
		((pers->getPos()->y < posicion->y) && (pers->getPos()->y + pers->getAlto() > posicion->y)) ||
		((pers->getPos()->y < posicion->y + alto) && (pers->getPos()->y + pers->getAlto() > posicion->y + alto)));

	if (choqueVertical and ((pers->getPos()->x +  pers->getAncho() > posicion->x ) and (pers->getPos()->x +  pers->getAncho() < posicion->x + ancho))){
		// Choque desde la derecha
		pers->getMovimiento()->getPos()->x = posAnterior.x - 2.5;
		pers->getMovimiento()->getPos()->y += 5;
		pers->getMovimiento()->setSaltando(false);
		pers->getMovimiento()->detenerCaida();
	//	printf("1\n");	
	} else if (choqueVertical and ((pers->getPos()->x > posicion->x ) and (pers->getPos()->x  < posicion->x + ancho))){
		// Choque desde la izq
		pers->getMovimiento()->getPos()->x = posAnterior.x + 2.5;
		pers->getMovimiento()->getPos()->y += 5;
		pers->getMovimiento()->setSaltando(false);
		pers->getMovimiento()->detenerCaida();
	//	printf("2\n");
	} 

	if(this->getPos()->y >= (posAnterior.y + pers->getAlto())){
		pers->aplicarRozamiento(this->rozamiento);
		pers->getMovimiento()->sePuedeSaltar = true;
		pers->getMovimiento()->setSaltando(false);
		pers->getMovimiento()->detenerCaida();
	}
	
	
	pers->colisionarConPlataforma(this);
	
	return 1;
}
