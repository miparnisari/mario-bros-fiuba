#include "Escalera.h"

const string Escalera::TAG = "Escalera";

Escalera::Escalera(Point* unaPos, int ancho, int alto): Elemento(unaPos) {
	Logger::info  (TAG , "Construccion correcta");

	// atributos de elemento
	this->ancho = ancho;
	this->alto = alto;
}

Escalera::~Escalera(){
}

int Escalera::aplicarColision(Personaje* unPersonaje, int res, Point posAnterior) {
	if (this->colisionaConPersonaje(unPersonaje) == 1) {
		unPersonaje->getMovimiento()->getPos()->y = posAnterior.y; //La altura se mantiene en las escaleras

		unPersonaje->getMovimiento()->detenerCaida(); //Seteo la velocidad en Y como 0

		if ( unPersonaje->getMovimiento()->getQuiereSubir() ){
			unPersonaje->getMovimiento()->subir();
		} else if ( unPersonaje->getMovimiento()->getQuiereBajar() ){
			unPersonaje->getMovimiento()->bajar();
		 }
		 unPersonaje->colisionarConEscalera(this);
		 
		if(this->getPos()->y >= unPersonaje->getPos()->y){
			unPersonaje->getMovimiento()->sePuedeSaltar = true;
		}
		 
	}
	return 1;
}

int Escalera::colisionaConPersonaje(Personaje* pers) {
	//Para este caso se necesita que la parte superior del personaje, o la inferior, esten completamente dentro de la escalera.
	
	//Vertice superior izquierdo
	if (this->verticeDentro(pers->getPos()->x, pers->getPos()->y, posicion, ancho, alto)) {
	
		//Vertice superior derecho
		if (this->verticeDentro(pers->getPos()->x + pers->getAncho(), pers->getPos()->y, posicion, ancho, alto)) {
			return 1;
		}
	}
		
	//Vertice inferior izquierdo 
	if (this->verticeDentro(pers->getPos()->x, pers->getPos()->y + pers->getAlto(), posicion, ancho, alto)) {
	
		//Vertice superior derecho
		if (this->verticeDentro(pers->getPos()->x + pers->getAncho(), pers->getPos()->y + pers->getAlto(), posicion, ancho, alto)) {
			return 1;
		}
	}

	
	//Si salio es porque algun vertice no se encuentra dentro de la escalera, enonces no hay colision.
	return 0;
}
