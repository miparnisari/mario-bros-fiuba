#ifndef BOTONSDECROLL_H_
#define BOTONSDECROLL_H_

#include <string>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "ComponenteSinImagen.h"
#include "../comun/Definiciones.h"

class BotonDeScroll : public ComponenteSinImagen {

	private:
		int incremento;
		
		void drawTriangleDown(SDL_Surface* destino);
		void drawTriangleUp(SDL_Surface* destino);
		
    public:
		BotonDeScroll(std::string id, int x, int y, int w, int h, int incremento);
		~BotonDeScroll();
		
		void refrescarArriba(SDL_Surface* destino);
		void refrescarAbajo(SDL_Surface* destino);
		void refrescar(SDL_Surface* destino);
		bool manejarEventos(SDL_Event event);
		int getIncremento();
		
};

#endif /* BOTONSCROLL_H_ */
