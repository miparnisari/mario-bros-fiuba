#include "Fuego.h"
#include "../eventos/EventoCrearEnemigo.h"
#include "../app/ControladorApp.h"
#include "../modelo/Nivel.h"
#define MAX_BOLAFUEGO 30

const string Fuego::TAG = "Fuego";

Fuego::Fuego(Point* unaPos, int ancho, int alto, string nombre, ID unID, Nivel* unNivel)
  : Enemigo(unaPos, ancho, alto, nombre, unID, unNivel->getPiso()) {
	Logger::info  (TAG , "Construccion correcta");
	this->adminID = new IdHandler(MAX_BOLAFUEGO);
	this->nivel = unNivel;
}

Fuego::~Fuego(){
	delete(adminID);
	delete this->movimiento;
	delete this->temp;
	delete this->posicion;
}

void Fuego::vivir(){

}

int Fuego::aplicarColision(Personaje* pers, int res, Point posAnterior) {
	
/*	if(((pers->getPos()->y + pers->getAlto() > posicion->y) || (pers->getPos()->y < posicion->y + alto)) &&
		((posAnterior.x < posicion->x + ancho) || ((posAnterior.x  + pers->getAncho() > posicion->x ) && (posAnterior.x  + pers->getAncho() < posicion->x + ancho)))){
				pers->colisionarConFuego(this);
	}*/

	pers->colisionarConFuego(this);
		
	return 1;
}

void Fuego::colisionarConBarril(Barril* unBarril) {
	//Debo transformar un barril convencional en una bola de fuego.

	if(unBarril->getActivo()){
		ID unID = (adminID->asignarID());
		if (unID != ID_INVALIDO){
			int ancho, alto;
			ControladorApp::getInstance()->getServidor()->getDimensionEnemigo("bolaFuego", &ancho, &alto);
			Point* punto = new Point(unBarril->getPos()->x, unBarril->getPos()->y );
			BolaDeFuego* bolaFuego = new BolaDeFuego(punto, ancho, alto, "bolaFuego", unID, unBarril->getMovimiento()->getPiso());
			this->nivel->agregarEnemigo(bolaFuego);
			ControladorApp::getInstance()->getServidor()->agregarEnemigo(bolaFuego);
			EventoCrearEnemigo ev(bolaFuego);
			ControladorApp::getInstance()->getServidor()->enviarEventoJugadores(&ev);
			unBarril->getMovimiento()->detenerEnX();
			unBarril->getMovimiento()->detenerEnY();
			unBarril->morir();
			
		}
	}
}


	

