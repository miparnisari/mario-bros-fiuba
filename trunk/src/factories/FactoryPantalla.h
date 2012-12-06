#ifndef FACTORYPANTALLA_H
#define FACTORYPANTALLA_H

#include "../modelo/Juego.h"
#include "../vista/Pantalla.h"
#include "../other/Logger.h"

class FactoryPantalla
{
	public:
		static Pantalla* crear(int width, int height, int bpp, std::string titulo);
		
	private:
		static const string TAG;
};

#endif /* FACTORYESCALERA_H */ 
