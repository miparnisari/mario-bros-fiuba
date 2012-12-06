#ifndef PANTALLA_H
#define PANTALLA_H

#include <string>
#include <list>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "../modelo/Point.h"
#include "Imagen.h"
#include "AnimacionProtagonista.h"
#include "../other/Logger.h"
#include "../comun/Definiciones.h"
class Pantalla
{
	public:
		Pantalla(int width, int height, int bpp, std::string titulo);
		~Pantalla();
		//void agregarImagen(Imagen* image);
		void cerrar();
		void delay(int num);
		bool refrescar(listaVistas lista, VistasEnemigos map, AnimacionProtagonista* vistaVidas, list<st_VistasBonus*> vistasBonus);
		const int getAncho();
		const int getAlto();
		SDL_Surface* getScreen();
	private:
		static const string TAG;
		SDL_Surface* screen;
		int ancho;
		int alto;
		
};

#endif /* PANTALLA_H */ 
