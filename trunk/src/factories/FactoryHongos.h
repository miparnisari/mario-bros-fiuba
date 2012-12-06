#ifndef FACTORYHONGOS_H
#define FACTORYHONGOS_H

#include "../modelo/Temporizador.h"
#include "IdHandler.h"
#include "../modelo/Hongo.h"

class ControladorApp;

class FactoryHongos
{
	public:
		FactoryHongos(Point* posicion, float piso);
		~FactoryHongos();
		Hongo* crear(ID unID);

	private:
		Point* posicion;
		Temporizador* temp;
		//IdHandler* adminID;
		float piso;
};

#endif /* FACTORYHONGOS_H */ 
