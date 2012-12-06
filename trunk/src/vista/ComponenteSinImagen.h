#ifndef COMPONENTESINIMAGEN_H_
#define COMPONENTESINIMAGEN_H_

#include <SDL/SDL.h>
#include <string>
#include "Componente.h"
class ComponenteSinImagen : public Componente {

	public:
		ComponenteSinImagen(std::string id, int x, int y, int w, int h);
		virtual void refrescar(SDL_Surface* destino) = 0;
		virtual ~ComponenteSinImagen();
		
};

#endif /* COMPONENTESINIMAGEN_H_ */
