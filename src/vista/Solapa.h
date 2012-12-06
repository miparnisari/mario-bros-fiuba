#ifndef SOLAPA_H
#define SOLAPA_H

#include <list>
#include <iostream>
#include <string>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "Boton.h"
#include "Componente.h"
#include "../comun/Definiciones.h"
#include "../excepciones/Excepciones.h"

class Solapa {

	private:
		static const std::string TAG;
		std::list<Componente*> 	componentes;
		Boton*			 		botonAsociado;
		std::string 			nombre;
		SDL_Rect				fondo;
		bool					activa;
		
		void drawButton(SDL_Surface* destino);
		void drawBackground(SDL_Surface* destino);

	public:
		Solapa(std::string nombre);
		~Solapa();
		
		void agregarComponente(Componente* unComp);
		void eliminarComponente(std::string unID);
		
		void manejarEventos(SDL_Event event);
		void refrescar(SDL_Surface* destino);
		
		void setActive(bool estado);
		void setBotonAsociado(int x, int y, int w, int h);
		
		const bool				 	isActive();
		const std::string 			getNombre();
		std::list<Componente*>& 	getComponentes();
		Boton*			 			getBotonAsociado();
};

#endif /* SOLAPA_H */
