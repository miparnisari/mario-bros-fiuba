#ifndef CUADRODESELECCION_H
#define CUADRODESELECCION_H

#include <vector>
#include <iostream>
#include <math.h>
#include "SDL/SDL.h"
#include "ComponenteSinImagen.h"
#include "Opcion.h"
#include "BarraScroll.h"
#include "EspacioParaTexto.h"
#include "EspacioParaDibujar.h"

class CuadroDeSeleccion: public ComponenteSinImagen
{
	private:
		Opcion* opcionActual;
		std::vector<Opcion*> opciones;
		BarraScroll* barraScroll;
		EspacioParaTexto* espacioParaTexto;
		EspacioParaDibujar* espacioParaDibujar;
		
		int opcionMinimaVisible;
		int opcionMaximaVisible;
		
		void drawBox(SDL_Surface* destino);
		void drawOptions(SDL_Surface* destino);
		
	public:
		CuadroDeSeleccion(std::string id, int x, int y, int w, int h);
		~CuadroDeSeleccion();
		
		void agregarOpcion(Opcion* o);

		void refrescar(SDL_Surface* destino);
		bool manejarEventos(SDL_Event event);
		
		int getOpcionMinimaVisible();
		int getOpcionMaximaVisible();
		std::string getData();
		
		bool setOpcionMinimaVisible(int num);
		bool setOpcionMaximaVisible(int num);
	
};

#endif /* CUADRODESELECCION_H */ 
