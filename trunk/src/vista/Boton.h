#ifndef BOTON_H_
#define BOTON_H_

#include <string>
#include <iostream>
#include "SDL/SDL_image.h"
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "ComponenteSinImagen.h"
#include "../comun/Definiciones.h"
#include "../eventos/EventoBoton.h"

class Boton : public ComponenteSinImagen {

	private:
		static const std::string TAG;
		TTF_Font* font;
		std::string texto;
		EventoBoton* evento;
		bool active;
		
		void drawPressed(SDL_Surface* destino);
		void drawUnpressed(SDL_Surface* destino);
		void writeText(SDL_Surface* destino);

    public:
		Boton(std::string id, int x, int y, int w, int h, EventoBoton* ev, std::string texto, std::string font, int fontSize);
		~Boton();
		void refrescar(SDL_Surface* destino);
		bool manejarEventos(SDL_Event event);
		
		void setDimensiones(int x, int y, int w, int h);
		void setActive(bool estado);
		bool fuePresionado(SDL_Event event);
		
};

#endif /* BOTON_H_ */
