#ifndef VISTAMENU_H
#define VISTAMENU_H

#include "SDL/SDL.h"
#include "SDL/SDL_video.h"
#include "SDL/SDL_image.h"
#include "Imagen.h"
#include "MenuPrincipal.h"
#include "../comun/Definiciones.h"

class VistaMenu : public Imagen
{
	public:
		VistaMenu(std::string nombreArchivo, int tamX, int tamY, MenuPrincipal* menu);
		~VistaMenu();
		bool refrescar(SDL_Surface* destino);
		
	private:
		MenuPrincipal*	menu;
};

#endif /* VISTAMENU_H */ 
