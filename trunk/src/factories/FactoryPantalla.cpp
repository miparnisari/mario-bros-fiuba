#include "FactoryPantalla.h"
const string FactoryPantalla::TAG = "FactoryPantalla";

Pantalla* FactoryPantalla::crear(int width, int height, int bpp, std::string titulo) {
	Pantalla* pantalla = new Pantalla(width,height,bpp,titulo);
	return pantalla;
}
