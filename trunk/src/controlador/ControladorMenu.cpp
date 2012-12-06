#include "ControladorMenu.h"
#include "../app/ControladorApp.h"

const string ControladorMenu::TAG = "ControladorMenu";

ControladorMenu::ControladorMenu()
{
	menu = new MenuPrincipal();
	vistaMenu = new VistaMenu(IMG_FONDO_MENU, SCREEN_WIDTH, SCREEN_HEIGHT,menu);
	menu->iniciar();
	activo = false;
}

ControladorMenu::~ControladorMenu() 
{
	delete(this->menu);
	delete(this->vistaMenu);
}

bool ControladorMenu::refrescar(Pantalla* p)
{
	bool res = this->vistaMenu->refrescar(p->getScreen());
	return res;
}

void ControladorMenu::manejarEventos()
{
	SDL_Event event;
	if (SDL_PollEvent(&event)) {
		this->menu->manejarEventos(event);
		if( event.type == SDL_QUIT ) {
			Logger::info(TAG,"Saliendo del menu.");
			this->desactivar();
			ControladorApp::getInstance()->desactivar();
		}
	}
}

const bool ControladorMenu::estaActivo()
{
	return this->activo;
}

void ControladorMenu::activar()
{
	activo = true;
}

void ControladorMenu::desactivar()
{
	activo = false;
}

MenuPrincipal* ControladorMenu::getMenu()
{
	return this->menu;
}
