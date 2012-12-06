#ifndef ESPACIOPARADIBUJAR_H
#define ESPACIOPARADIBUJAR_H

#include <string>
#include "ComponenteSinImagen.h"
#include "AnimacionAuto.h"
#include "VistaElemento.h"
#include "../modelo/Point.h"
#include "../controlador/TiposDeDatos.h"

class EspacioParaDibujar: public ComponenteSinImagen
{
	public:
		EspacioParaDibujar(string id, int x, int y, int w, int h);
		virtual ~EspacioParaDibujar();
		bool manejarEventos(SDL_Event event);
		void setAnimacion(int ancho, int alto, string nombreArchivo, vector<st_Animacion*> vectorAnimaciones, std::string nombre);
		void refrescar(SDL_Surface* destino);
	
	private:
		void drawBox(SDL_Surface* destino);
	
		AnimacionAuto* animacion;
};

#endif /* ESPACIOPARADIBUJAR_H */ 
