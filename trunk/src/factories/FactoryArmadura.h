#ifndef FACTORYARMADURA_H
#define FACTORYARMADURA_H

#include "../modelo/Temporizador.h"
#include "IdHandler.h"
#include "../bonus/Armadura.h"
#include "../eventos/EventoCrearPersonajeAnimado.h"

class Nivel;
class ControladorApp;

class FactoryArmadura
{
	public:
		FactoryArmadura();
		~FactoryArmadura();
		Bonus* crear(Point* pos,Nivel* unNivel);

	private:
		IdHandler* adminID;

		
};

#endif /* FACTORYARMADURA_H */ 
