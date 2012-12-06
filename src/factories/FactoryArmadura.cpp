#include "FactoryArmadura.h"
#include "../modelo/Nivel.h"
#include "../app/ControladorApp.h"

#define MAX_ARMADURA 99
#define INTERVALO_ARMADURA 30
#define ANCHO_ARMADURA 30
#define ALTO_ARMADURA 30
#define TIEMPO_VIDA_ARMADURA 10

FactoryArmadura::FactoryArmadura()
{
	this->adminID = new IdHandler(MAX_ARMADURA);
}

FactoryArmadura::~FactoryArmadura()
{
	delete adminID;
}

Bonus* FactoryArmadura::crear(Point* punto, Nivel* unNivel)
{
	ID unID = adminID->asignarID();

	if (unID == ID_INVALIDO) return NULL;
	// Copio la posicion de quien dejo el bonus
	Point* unPunto = new Point(punto->x, punto->y);
	int ancho, alto;
	int result = ControladorApp::getInstance()->getServidor()->getDimensionEnemigo("Armadura", &ancho, &alto);
	if (result){
		return new Armadura(unPunto, ancho, alto, TIEMPO_VIDA_ARMADURA, "Armadura", unID, unNivel->getPiso());
	}
	return NULL;
}
