#include "Pow.h"
#include "../app/ControladorApp.h"
#include "Juego.h"
#include "../server/Servidor.h"
#include "../eventos/EventoSonido.h"
const string Pow::TAG = "Pow";

Pow::Pow(Point* unaPos, int ancho, int alto, float rozamiento): Plataforma(unaPos, ancho, alto, rozamiento) {
	activo = true;
}

Pow::~Pow(){
}

int Pow::aplicarColision(Personaje* pers, int res, Point posAnterior){
	
	if(((pers->getPos()->y + pers->getAlto() > posicion->y) || (pers->getPos()->y < posicion->y + alto)) &&
		((posAnterior.x < posicion->x + ancho) || ((posAnterior.x  + pers->getAncho() > posicion->x ) && (posAnterior.x  + pers->getAncho() < posicion->x + ancho)))){
			pers->getMovimiento()->getPos()->y = posAnterior.y;
	}

	bool choqueVertical =  (((pers->getPos()->y > posicion->y) && (pers->getPos()->y + pers->getAlto() < posicion->y + alto)) ||
		((pers->getPos()->y > posicion->y) && (pers->getPos()->y + pers->getAlto() > posicion->y + alto)) ||
		((pers->getPos()->y < posicion->y) && (pers->getPos()->y + pers->getAlto() > posicion->y)) ||
		((pers->getPos()->y < posicion->y + alto) && (pers->getPos()->y + pers->getAlto() > posicion->y + alto)));

	if (choqueVertical and ((pers->getPos()->x +  pers->getAncho() > posicion->x ) and (pers->getPos()->x +  pers->getAncho() < posicion->x + ancho))){
		// Choque desde la derecha
		pers->getMovimiento()->getPos()->x = posAnterior.x - 2.5;
		pers->getMovimiento()->getPos()->y += 1; 
		pers->getMovimiento()->setSaltando(false);
		pers->getMovimiento()->detenerCaida();
	//	printf("1\n");	
	} else if (choqueVertical and ((pers->getPos()->x > posicion->x ) and (pers->getPos()->x  < posicion->x + ancho))){
		// Choque desde la izq
		pers->getMovimiento()->getPos()->x = posAnterior.x + 2.5;
		pers->getMovimiento()->getPos()->y += 1;
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
	
	if((this->getPos()->y + this->alto)<= posAnterior.y){
		if (activo) {
			ControladorApp::getInstance()->getServidor()->getJuego()->aplicarPow();
			EventoSonido ev("S","Toasty");
			ControladorApp::getInstance()->getServidor()->enviarEventoJugadores(&ev);
			activo = false;
		}
	}
	
//	pers->colisionarConPow(this);
	
	return 1;
}
