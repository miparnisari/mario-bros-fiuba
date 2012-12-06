#include "Tortuga.h"
#include "../app/ControladorApp.h"
#include "../modelo/Plataforma.h"

#define VEL_TORTUGA 1
#define POT_TORTUGA 5
#define VEL_CAPARAZON 20
#define TIEMPO 1

Tortuga::Tortuga(Point* punto, int ancho, int alto, string Nombre, ID unID, float piso)
	: Enemigo(punto, ancho, alto, Nombre, unID, piso) {

	cont = 0;
	myID = unID;
	esCaparazon = false;
	quieto = false;
	direccion = 1;
	this->movimiento = new MovimientoAutomatico(punto, POT_TORTUGA, VEL_TORTUGA, piso);
	this->temp = new Temporizador();
}


Tortuga::~Tortuga() {
	delete this->movimiento;
	delete this->temp;
	//delete this->posicion;
}

void Tortuga::vivir(){

	if(this->getActivo()){
		
		if (!quieto){
			if (esCaparazon) this->movimiento->aplicarFuerza(VEL_CAPARAZON * 4 * direccion);
			else this->movimiento->aplicarFuerza(VEL_TORTUGA * 4);
		}
		
		this->movimiento->caerSinSalto();

	}

	if(this->temp->contando){
		if (this->temp->puedeRealizarAccion()){
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

int Tortuga::aplicarColision(Personaje* pers, int result, Point posAnterior){
	return pers->colisionarConTortuga(this, posAnterior);
}

void Tortuga::morir(){
	this->temp->setIntervalo(TIEMPO);
	this->temp->setTiempoInicial();
	this->setActivo(false);
}

void Tortuga::hacerseCaparazon(){
	esCaparazon = true;
	quieto = true;

	EventoMoverEnemigo ev(this);
	ControladorApp::getInstance()->getServidor()->enviarEventoJugadores(&ev);
}

void Tortuga::desplazar(int desplazamiento){
	this->posicion->x += desplazamiento;
}

void Tortuga::aplicarPow(){
	this->movimiento->detenerEnX();
	this->movimiento->detenerEnY();
	this->hacerseCaparazon();
}

std::string Tortuga::getTipoMovimiento(){
	std::string tipoMov = "";

	if (esCaparazon) tipoMov = "caparazon";
	else tipoMov = "quietoder";

	return tipoMov;
}

void Tortuga::colisionarConPlataforma(Plataforma* plataforma){

	bool estaArriba = (((this->posicion->y + this->alto > plataforma->getPos()->y) || (this->posicion->y < plataforma->getPos()->y + plataforma->getAlto())) &&
			  ((this->posicion->x < plataforma->getPos()->x + plataforma->getAncho()) || ((this->posicion->x  + this->ancho > plataforma->getPos()->x ) && (this->posicion->x  + this->ancho < plataforma->getPos()->x + plataforma->getAncho()))));

	if (!estaArriba){
		this->direccion *= -1;
	}
}
