#include "Hongo.h"
#include "../app/ControladorApp.h"
#include "../modelo/Tortuga.h"

#define VEL_HONGO 1
#define POT_HONGO 5
#define tiempo 1
#define tiempoMareado 4

Hongo::Hongo(Point* punto, int ancho, int alto, string Nombre, ID unID, float piso)
	: Enemigo(punto, ancho, alto, Nombre, unID, piso)
{
	cont = 0;
	myID = unID;
	this->movimiento = new MovimientoAutomatico(punto, POT_HONGO, VEL_HONGO, piso);
	this->temp = new Temporizador();
	this->mareado = false;
	int random = rand() % 2;
	if (random >= 1) this->direccion = 1;
	else this->direccion = -1;
	//this->temp->setIntervalo(tiempo);
}

Hongo::~Hongo(){
	delete this->movimiento;
	delete this->temp;
	//delete this->posicion;
}

void Hongo::vivir(){


	if(this->getActivo()){
			this->movimiento->caerSinSalto();
			if(!this->mareado && !this->getMorir())
				this->movimiento->aplicarFuerza(5 * VEL_HONGO * direccion);
		}

	if(this->temp->contando){
			if (this->temp->puedeRealizarAccion()){
				if(this->mareado){
					this->mareado = false;
					this->temp->contando = false;
				}
				else{
					if(!this->getMorir()){
						Nivel* nivel = ControladorApp::getInstance()->getServidor()->getJuego()->getNivel();
						Bonus* bonus = FactoryBonus::getInstance()->crear(this->posicion, nivel);
						if(bonus != NULL) {
							nivel->agregarEnemigo(bonus);
							ControladorApp::getInstance()->getServidor()->agregarEnemigo(bonus);
							EventoCrearEnemigo ev(bonus);
							ControladorApp::getInstance()->getServidor()->enviarEventoJugadores(&ev);
						}
						this->setMorir(true);
						this->temp->contando = false;
					}
				}
			}
		}



}

int Hongo::aplicarColision(Personaje* pers, int result, Point posAnterior){
	
	return pers->colisionarConHongo(this, posAnterior);
}
 
void Hongo::morir(){
	this->temp->setIntervalo(tiempo);
	this->temp->setTiempoInicial();
	this->setActivo(false);
	this->mareado = false;
	EventoMoverEnemigo ev(this);
	ControladorApp::getInstance()->getServidor()->enviarEventoJugadores(&ev);	
}

void Hongo::aplicarPow(){
	this->temp->setIntervalo(tiempoMareado);
	this->temp->setTiempoInicial();
	this->mareado = true;
	this->getMovimiento()->detenerEnX();
	this->getMovimiento()->detenerEnY();
	EventoMoverEnemigo ev(this);
	ControladorApp::getInstance()->getServidor()->enviarEventoJugadores(&ev);
}

std::string Hongo::getTipoMovimiento(){
	std::string tipoMov = "";

	if (this->mareado) tipoMov = "mareado";
	else if(!this->activo)tipoMov = "muriendo";
	else tipoMov = "quietoder"; 
	
	return tipoMov;
}


int Hongo::colisionarConTortuga(Tortuga* tortuga, Point posAnterior){

	if (tortuga->esCaparazon and (! tortuga->quieto)){
		this->setMorir(true);
		this->temp->contando = false;
	}
	return true;
}
