#ifndef COMPONENTE_H_
#define COMPONENTE_H_

#include <string>
#include <iostream>
#include "SDL/SDL_ttf.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
// Clase abstracta

class Componente {
	
	protected:
		std::string id;
		SDL_Rect box;
		
		SDL_Color translate_color(Uint32 int_color);
		SDL_Surface* renderizarTexto(TTF_Font* fuente, std::string texto, SDL_Color color);
	
	public:
		Componente(std::string id, int x, int y, int w, int h);
		virtual void refrescar(SDL_Surface* destino) = 0;
		virtual bool manejarEventos(SDL_Event event) = 0;
		virtual ~Componente();
		std::string getID();
		virtual std::string getData();
		
};

#endif /* COMPONENTE_H_ */
