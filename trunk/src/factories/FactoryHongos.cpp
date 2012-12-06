#include "FactoryHongos.h"
#include "../app/ControladorApp.h"
#define MAX_HONGOS 50
#define INTERVALO_HONGOS 5


FactoryHongos::FactoryHongos(Point* unaPosicion, float piso)
{
	posicion = unaPosicion;
	//this->adminID = new IdHandler(MAX_HONGOS);
	temp = new Temporizador();
	temp->setIntervalo(INTERVALO_HONGOS);
	temp->setTiempoInicial();
	this->piso = piso;
}

FactoryHongos::~FactoryHongos(){
	delete temp;
	//delete adminID;
}

Hongo* FactoryHongos::crear(ID unID){
	if (!temp->puedeRealizarAccion()) return NULL;
	temp->setTiempoInicial();

	int ancho, alto;
	int result = ControladorApp::getInstance()->getServidor()->getDimensionEnemigo("hongo", &ancho, &alto);
	Point* punto = new Point(posicion->x + 0.2, posicion->y - alto);
	if(result){
		return (new Hongo(punto, ancho, alto, "hongo", unID, this->piso));
	}
	return NULL;
}

