#ifndef FACTORYVIDAEXTRA_H_
#define FACTORYVIDAEXTRA_H_

#include "../modelo/Temporizador.h"
#include "IdHandler.h"
#include "../bonus/VidaExtra.h"
#include "../eventos/EventoCrearPersonajeAnimado.h"

class Nivel;
class ControladorApp;

class FactoryVidaExtra {
	public:
		FactoryVidaExtra();
		virtual ~FactoryVidaExtra();
		Bonus* crear(Point* point, Nivel* unNivel);

	private:
		//Point* posicion;
		//Temporizador* temp;
		IdHandler* adminID;
};

#endif /* FACTORYVIDAEXTRA_H_ */
