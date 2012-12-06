#include "BolaDeFuego.h"
#include "../app/ControladorApp.h"
#include "../modelo/Plataforma.h"
#include "../modelo/Escalera.h"
#define VEL_BARR 1
#define POT_BARR 5
#define TIEMPO 8

BolaDeFuego::BolaDeFuego(Point* punto, int ancho, int alto, string Nombre, ID unID, float piso)
	: Enemigo(punto, ancho, alto, Nombre, unID, piso)
{
	cont = 0;
	myID = unID;
	this->movimiento = new MovimientoAutomatico(punto, POT_BARR, VEL_BARR, piso);
	this->direccion = -1;
	this->ultPlataforma = NULL;
	this->ultEscalera = NULL;
	this->subirEsc = 0;
	this->temp = new Temporizador();
	this->temp->setIntervalo(TIEMPO);
	this->temp->setTiempoInicial();
	Logger::debug("Bola", "Se creo una bola de fuego");
}

BolaDeFuego::~BolaDeFuego(){
	delete this->movimiento;
	delete this->temp;
	//delete this->posicion;
}

void BolaDeFuego::vivir(){
	this->movimiento->caerSinSalto();
	this->movimiento->aplicarFuerza(this->direccion * 5);
	if (this->temp->puedeRealizarAccion()) {
		this -> setActivo(false);
	}
}

int BolaDeFuego::aplicarColision(Personaje* pers, int result, Point posAnterior){
	pers->colisionarConBolaDeFuego(this);
	return false;
}

void BolaDeFuego::colisionarConPlataforma(Plataforma* plataforma){
	if(this->ultPlataforma != plataforma){
		this->direccion *= -1;
		this->ultPlataforma = plataforma;
	}
}

void BolaDeFuego::colisionarConEscalera(Escalera* escalera){
	if(this->ultEscalera != escalera){
		this->subirEsc = rand() % 2;
		this->ultEscalera = escalera;
	}
	if(subirEsc)
		this->getMovimiento()->subir();
}
