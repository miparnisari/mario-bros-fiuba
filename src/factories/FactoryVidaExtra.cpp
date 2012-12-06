#include "FactoryVidaExtra.h"
#include "../modelo/Nivel.h"
#include "../app/ControladorApp.h"

#define MAX_VIDAEXTRA 99
#define INTERVALO_VIDAEXTRA 45
#define ANCHO_VIDAEXTRA 50
#define ALTO_VIDAEXTRA 50
#define TIEMPO_VIDAEXTRA 7 // 7 segundos

FactoryVidaExtra::FactoryVidaExtra()
{
	this->adminID = new IdHandler(MAX_VIDAEXTRA);
}

FactoryVidaExtra::~FactoryVidaExtra(){
	delete adminID;
}


Bonus* FactoryVidaExtra::crear(Point* punto, Nivel* unNivel){
	ID unID = (adminID->asignarID());
	if (unID == ID_INVALIDO) return NULL;
	
	// Copio la posicion de quien dejo el bonus
	Point* unPunto = new Point(punto->x, punto->y);

	int ancho, alto;
	int result = ControladorApp::getInstance()->getServidor()->getDimensionEnemigo("VidaExtra", &ancho, &alto);
	if (result){
		return new VidaExtra(unPunto, ancho, alto, TIEMPO_VIDAEXTRA, "VidaExtra", unID, unNivel->getPiso());
	}
	return NULL;
}
