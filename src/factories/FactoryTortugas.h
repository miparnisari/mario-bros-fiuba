#ifndef FACTORYTORTUGAS_H_
#define FACTORYTORTUGAS_H_

#include "../modelo/Temporizador.h"
#include "IdHandler.h"
#include "../modelo/Tortuga.h"

class ControladorApp;

class FactoryTortugas {
	public:
		FactoryTortugas(Point* unaPosicion, float piso);
		~FactoryTortugas();
		Tortuga* crear(ID unID);

	private:
		Point* posicion;
		Temporizador* temp;
		//IdHandler* adminID;
		float piso;
};

#endif /* FACTORYTORTUGAS_H_ */
