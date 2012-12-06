#ifndef ETIQUETA_H_
#define ETIQUETA_H_

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "ComponenteSinImagen.h"
#include "../comun/Definiciones.h"
#include <string>

class Etiqueta : public ComponenteSinImagen {

	private:
		static const std::string TAG;
		int 		fontSize;
		TTF_Font* 	font;
		std::string texto;
		SDL_Surface* textoAmostrar;

	public:
		Etiqueta(std::string id, int x, int y, int w, int h, std::string texto, std::string unaFont, int fontSize);
		~Etiqueta();
		void refrescar(SDL_Surface* destino);
		bool manejarEventos(SDL_Event event);
};

#endif /* ETIQUETA_H_ */
