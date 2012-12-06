#include "FactoryPlumas.h"
#include "../modelo/Nivel.h"
#include "../app/ControladorApp.h"

#define MAX_BONUS 99
#define INTERVALO_BONUS 60
#define ANCHO_PLUMA 40
#define ALTO_PLUMA 60
#define TIEMPO_VIDA_PLUMA 7 // 7 segundos

FactoryPlumas::FactoryPlumas()
{
	this->adminID = new IdHandler(MAX_BONUS);
}

FactoryPlumas::~FactoryPlumas(){
	delete adminID;
}

Bonus* FactoryPlumas::crear(Point* punto, Nivel* unNivel) {
	
	ID unID = (adminID->asignarID());
	if (unID == ID_INVALIDO) return NULL;
	
	// Copio la posicion de quien dejo el bonus
	Point* unPunto = new Point(punto->x, punto->y);

	int ancho, alto;
	int result = ControladorApp::getInstance()->getServidor()->getDimensionEnemigo("pluma", &ancho, &alto);
	if(result){
		return new Pluma(unPunto, ancho, alto, TIEMPO_VIDA_PLUMA, "pluma", unID, unNivel->getPiso());
	}
	return NULL;
}
