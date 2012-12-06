#include "FactoryTortugas.h"
#include "../app/ControladorApp.h"
#define MAX_TORTUGAS 25
#define INTERVALO_TORTUGAS 15

FactoryTortugas::FactoryTortugas(Point* unaPosicion, float piso) {
	posicion = unaPosicion;
	//this->adminID = new IdHandler(MAX_TORTUGAS);
	temp = new Temporizador();
	temp->setIntervalo(INTERVALO_TORTUGAS);
	temp->setTiempoInicial();
	this->piso = piso;
}

FactoryTortugas::~FactoryTortugas() {
	delete temp;
	//delete adminID;
}

Tortuga* FactoryTortugas::crear(ID unID){
	if (!temp->puedeRealizarAccion()) return NULL;
	temp->setTiempoInicial();

	int ancho, alto;
	int result = ControladorApp::getInstance()->getServidor()->getDimensionEnemigo("tortuga", &ancho, &alto);
	Point* punto = new Point(posicion->x + 0.2, posicion->y - alto);
	if(result){
		return (new Tortuga(punto, ancho, alto, "tortuga", unID, this->piso));
	}
	return NULL;
}
