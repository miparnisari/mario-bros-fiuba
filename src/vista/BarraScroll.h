#ifndef BARRASCROLL_H
#define BARRASCROLL_H

#include "ComponenteSinImagen.h"
#include "BotonDeScroll.h"
#include "../comun/Definiciones.h"

class BarraScroll: public ComponenteSinImagen
{
	private:
		BotonDeScroll* botonArriba;
		BotonDeScroll* botonAbajo;
		
	public:
		BarraScroll(std::string id, int x, int y, int w, int h);
		virtual ~BarraScroll();
		virtual void refrescar(SDL_Surface* destino);
		bool manejarEventos(SDL_Event event);
		
		int getIncremento(SDL_Event event);
};

#endif /* BARRASCROLL_H */ 
