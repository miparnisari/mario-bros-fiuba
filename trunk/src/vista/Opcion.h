#ifndef OPCION_H
#define OPCION_H

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "ComponenteSinImagen.h"
#include "../comun/Definiciones.h"
#include "EspacioParaTexto.h"
#include "EspacioParaDibujar.h"

class Opcion: public ComponenteSinImagen
{
	public:
		Opcion(std::string id, std::string font, int fontSize);
		~Opcion();
		
		void refrescar(SDL_Surface* destino);
		bool manejarEventos(SDL_Event event);
		void setDimensiones(int x, int y, int w, int h);
		const bool estaSeleccionada();
		void seleccionar();
		void desmarcar();
		std::string getData();
		void setAncho(int ancho);
		void setDatosAsociados(int x, int y, int w, int h, vector <ParTexto> datos);
		void setAnimAsociada(int x, int y, int w, int h, string nomArch, vector<st_Animacion*> vectorAnims, std::string nombrePers);
	
	private:
		static const std::string TAG;
		bool		seleccionada;
		std::string	fontName;
		int 		fontSize;
		TTF_Font* 	font;
		std::string texto;
		SDL_Surface* textoAmostrar;
		
		EspacioParaTexto* datosAsociados;
		EspacioParaDibujar* animAsociada;
};

#endif /* OPCION_H */ 
