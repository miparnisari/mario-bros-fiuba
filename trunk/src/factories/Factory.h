#ifndef FACTORY_H
#define FACTORY_H

#include "../modelo/Elemento.h"
#include "../modelo/Point.h"
#include <string>

class Factory
{
	public:
		static Elemento* crear(Point* unaPos, std::string nombreImagen);

};

#endif /* FACTORY_H */ 
