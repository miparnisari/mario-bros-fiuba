#include "VistaMenu.h"

using namespace std;

VistaMenu::VistaMenu(string nombreArchivo, int tamX, int tamY, MenuPrincipal* unMenu)
	: Imagen(nombreArchivo, NULL, 1, tamX, tamY, 1, "vistaMenu")
{
	
	SDL_Init(SDL_INIT_EVERYTHING);
	
	double factX = this->setFactorXResize(tamX);
	double factY = this->setFactorYResize(tamY);
	this->resizearImg(factX, factY);
	this->menu = unMenu;
}

VistaMenu::~VistaMenu()
{
	SDL_FreeSurface( this->img );
	// El menu se borra en ControladorMenu
}

bool VistaMenu::refrescar(SDL_Surface* destino) 
{
	SDL_BlitSurface(getImg(),getCuadro(), destino, NULL); 
	
	// Pintamos la ventana actual
	this->menu->refrescar(destino);
	return true;
}
