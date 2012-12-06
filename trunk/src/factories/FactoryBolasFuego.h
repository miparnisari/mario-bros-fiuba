#ifndef FACTORYBOLASFUEGO_H
#define FACTORYBOLASFUEGO_H

#include "../modelo/Temporizador.h"
#include "IdHandler.h"
#include "../modelo/BolaDeFuego.h"

class ControladorApp;

class FactoryBolasFuego
{
	public:
		FactoryBolasFuego(Point* posicion, float piso);
		~FactoryBolasFuego();
		BolaDeFuego* crear();

	private:
		Point* posicion;
		Temporizador* temp;
		IdHandler* adminID;
		float piso;
};

#endif /* FACTORYBOLASFUEGO_H */ 
