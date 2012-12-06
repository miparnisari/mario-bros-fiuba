#ifndef FACTORYNIVEL_H
#define FACTORYNIVEL_H
#define PRIOR_NIVEL 1

#include "../modelo/Nivel.h"
#include "../vista/VistaNivel.h"
#include "../other/Logger.h"
#include "../modelo/Posicionable.h"
#include "../modelo/Juego.h"

class FactoryNivel
{
	public:
		static Nivel* crear(int alto, int ancho, std::string nombreImagen, int scroll, int anchoPantalla, int altoPantalla);
		
	private:
		static const string TAG;
};

#endif /* FACTORYNIVEL_H */ 
