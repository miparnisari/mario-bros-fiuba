#ifndef CONTROLADORMENU_H
#define CONTROLADORMENU_H

#include "../comun/Definiciones.h"
#include "SDL/SDL.h"
#include "../vista/Pantalla.h"
#include "../vista/MenuPrincipal.h"
#include "../vista/VistaMenu.h"

class ControladorApp;

class ControladorMenu
{
	private:
		static const std::string TAG;
		MenuPrincipal*	menu;
		VistaMenu*		vistaMenu;
		bool			activo;
		
	public:
		ControladorMenu();
		~ControladorMenu();
		void manejarEventos();
		bool refrescar(Pantalla* p);
		const bool estaActivo();
		void activar();
		void desactivar();
		MenuPrincipal* getMenu();
		
};

#endif /* CONTROLADORMENU_H */ 
