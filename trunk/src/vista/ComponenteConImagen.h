#ifndef COMPONENTECONIMAGEN_H_
#define COMPONENTECONIMAGEN_H_

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "Componente.h"
#include <string>
#include <iostream>

// Clase abstracta

class ComponenteConImagen : public Componente {
	
	protected:
		static const std::string TAG;
		SDL_Surface* img;
		SDL_Rect* clip;
	
	public:
		ComponenteConImagen(std::string id, int x, int y, int w, int h, std::string filename);
		virtual ~ComponenteConImagen();
		
		void refrescar(SDL_Surface* destino);
		virtual bool manejarEventos(SDL_Event event) = 0;
		
		SDL_Surface* cargarImagen( std::string filename );
		SDL_Surface* getImg();
		SDL_Rect* getCuadro();
		
};

#endif /* COMPONENTECONIMAGEN_H_ */
