#include "FactoryBolasFuego.h"
#include "../app/ControladorApp.h"
#define INTERVALO_BOLAS 25
#define MAX_BOLAS 100


FactoryBolasFuego::FactoryBolasFuego(Point* unaPosicion, float piso)
{
	posicion = unaPosicion;
	temp = new Temporizador();
	this->adminID = new IdHandler(MAX_BOLAS);
	temp->setIntervalo(INTERVALO_BOLAS);
	temp->setTiempoInicial();
	this->piso = piso;
}

FactoryBolasFuego::~FactoryBolasFuego(){
	delete temp;
	delete adminID;
}

BolaDeFuego* FactoryBolasFuego::crear(){
	if (!temp->puedeRealizarAccion()) return NULL;
	temp->setTiempoInicial();
	ID unID = (adminID->asignarID());
	if (unID == ID_INVALIDO) return NULL;
	int ancho, alto;
	int result = ControladorApp::getInstance()->getServidor()->getDimensionEnemigo("bolaFuego", &ancho, &alto);
	Point* punto = new Point(posicion->x + 0.2, posicion->y - alto);
	if(result){
		return (new BolaDeFuego(punto, ancho, alto, "bolaFuego", unID, this->piso));
	}
	Logger::debug("FactoryBolas","No se encontro la informacion para cargarlas");
	return NULL;
}

