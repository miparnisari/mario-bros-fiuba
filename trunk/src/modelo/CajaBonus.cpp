#include "CajaBonus.h"
#include "../app/ControladorApp.h"
#include "Juego.h"
#include "../server/Servidor.h"
#include "../eventos/EventoSonido.h"
#include "../eventos/EventoCrearEnemigo.h"
#include "../modelo/Nivel.h"

#define TIEMPO_BONUS 5
const string CajaBonus::TAG = "CajaBonus";

CajaBonus::CajaBonus(Point* unaPos, int ancho, int alto, float rozamiento, Nivel* unNivel)
	: Plataforma(unaPos, ancho, alto, rozamiento) {
	tempBonus = new Temporizador();
	tempBonus->setIntervalo(TIEMPO_BONUS);
	nivel = unNivel;
}

CajaBonus::~CajaBonus(){
	delete(tempBonus);
}

int CajaBonus::aplicarColision(Personaje* pers, int res, Point posAnterior){
	
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
		pers->getMovimiento()->setPuedeSaltar(true);
		pers->getMovimiento()->setSaltando(false);
		pers->getMovimiento()->detenerCaida();
	}
	
	if((this->getPos()->y + this->alto)<= posAnterior.y){
		if (this->tempBonus->contando) {
	//		printf("1\n");
			if (this->tempBonus->puedeRealizarAccion()){
		//		printf("2\n");
				EventoSonido ev("S","CajaBonus");
				ControladorApp::getInstance()->getServidor()->enviarEventoJugadores(&ev);
				this->tempBonus->setTiempoInicial();
				Point* punto = new Point(posicion->x + 0.2, posicion->y - alto);
				Bonus* bonus = FactoryBonus::getInstance()->crearObligatorio(punto, nivel);
				nivel->agregarEnemigo(bonus);
				ControladorApp::getInstance()->getServidor()->agregarEnemigo(bonus);
				EventoCrearEnemigo evCE(bonus);
				ControladorApp::getInstance()->getServidor()->enviarEventoJugadores(&evCE);
			}
		} else {
	//		printf("3\n");
			EventoSonido ev("S","CajaBonus");
			ControladorApp::getInstance()->getServidor()->enviarEventoJugadores(&ev);
			this->tempBonus->setTiempoInicial();
			Point* punto = new Point(posicion->x + 0.2, posicion->y - alto );
			Bonus* bonus = FactoryBonus::getInstance()->crearObligatorio(punto, nivel);
			nivel->agregarEnemigo(bonus);
			ControladorApp::getInstance()->getServidor()->agregarEnemigo(bonus);
			EventoCrearEnemigo evCE(bonus);
			ControladorApp::getInstance()->getServidor()->enviarEventoJugadores(&evCE);
		}
	}
	
	return 1;
}
