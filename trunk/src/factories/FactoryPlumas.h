#ifndef FACTORYPLUMAS_H
#define FACTORYPLUMAS_H

#include "../modelo/Temporizador.h"
#include "IdHandler.h"
#include "../bonus/Pluma.h"
#include "../bonus/Armadura.h"
#include "../eventos/EventoCrearPersonajeAnimado.h"

class Nivel;
class ControladorApp;

class FactoryPlumas
{
	public:
		FactoryPlumas();
		~FactoryPlumas();
		Bonus* crear(Point* pos, Nivel* unNive);
	
	private:
		IdHandler* adminID;
		
};

#endif /* FACTORYPLUMAS_H */ 
