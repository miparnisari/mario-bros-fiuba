#ifndef ESPACIOPARATEXTO_H
#define ESPACIOPARATEXTO_H

#include <string>
#include <utility>
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_image.h"
#include "../comun/Definiciones.h"
#include "ComponenteSinImagen.h"
#include "../controlador/TiposDeDatos.h"


class EspacioParaTexto: public ComponenteSinImagen
{
	public:
		EspacioParaTexto(std::string id, int x, int y, int w, int h);
		virtual ~EspacioParaTexto();
		
		void agregarTexto(ParTexto par);
		void refrescar(SDL_Surface* destino);
		void limpiarTexto();
		void modificarTexto(vector <ParTexto> nuevoTexto);
		bool manejarEventos(SDL_Event event);
	
	private:
		vector <ParTexto> texto;
		TTF_Font* font;
		void drawBox(SDL_Surface* destino);

};

#endif /* ESPACIOPARATEXTO_H */ 
