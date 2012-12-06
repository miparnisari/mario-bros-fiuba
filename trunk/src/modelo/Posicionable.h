#ifndef POSICIONABLE_H
#define POSICIONABLE_H

#include "Point.h"
#include "../comun/Definiciones.h"

// Interfaz de objetos posicionables
class Posicionable 
{
	public:
		virtual Point* getPos() = 0;
		virtual void setPos(Point* unaPos) = 0;

};

#endif /* POSICIONABLE_H */ 
