#include "Mono.h"
#include "../eventos/EventoCrearEnemigo.h"
#include "../app/ControladorApp.h"
#include "../modelo/Nivel.h"

#define VEL_MONO 2
#define POTENCIASALTO_MONO 0
#define DESPLAZAMIENTOENX 10
#define MAX_BARR 80
#define INTERVALO_BARR 7


Mono::Mono(Point* punto, int ancho, int alto, string nombre, ID unID, Nivel* unNivel)
	: Enemigo(punto, ancho, alto, nombre, unID, unNivel->getPiso())
{
	this->nivel = unNivel;
	this->movimiento = new MovimientoIzquierdaDerecha(DESPLAZAMIENTOENX, punto, POTENCIASALTO_MONO, VEL_MONO, this->nivel->getPiso());
	this->temp = new Temporizador();
	this->adminID = new IdHandler(MAX_BARR);
	temp->setIntervalo(INTERVALO_BARR);
	temp->setTiempoInicial();
}


Mono::~Mono()
{
	delete(adminID);
	delete this->movimiento;
	delete this->temp;
	//delete this->posicion;
}

void Mono::mover(int result) {
//	this->mov->actualizar();
	//this->setPos(this->mov->getPos());
}

void Mono::vivir(){
	
	this->movimiento->caerSinSalto();

	if (!temp->puedeRealizarAccion()) return;
	//printf("temp puede realizar accion\n");

	temp->setTiempoInicial();

	ID unID = (adminID->asignarID());
	if (unID == ID_INVALIDO) return;
	//printf("factoryhongos puede crear\n");

	int ancho, alto;

	ControladorApp::getInstance()->getServidor()->getDimensionEnemigo("barril", &ancho, &alto);
	Point* punto = new Point(posicion->x + 0.2, posicion->y - alto/2);
	Barril* barril = new Barril(punto, ancho, alto, "barril", unID, this->getMovimiento()->getPiso());
	this->nivel->agregarEnemigo(barril);
	ControladorApp::getInstance()->getServidor()->agregarEnemigo(barril);
	EventoCrearEnemigo ev(barril);
	ControladorApp::getInstance()->getServidor()->enviarEventoJugadores(&ev);

}
