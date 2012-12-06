#ifndef ANIMACION_H
#define ANIMACION_H

#include <vector>
#include <map>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "Imagen.h"
#include "../modelo/Personaje.h"
#include "../modelo/Posicionable.h"
#include "../controlador/TiposDeDatos.h"
#include "../comun/Definiciones.h"

class Animacion : public Imagen {

	public:
		Animacion(std::string nombre, Posicionable* animado, int prior,int alto, int ancho, vector<st_Animacion*> vectorAnimaciones, ID unID, std::string nombrePers);
		virtual ~Animacion();
		virtual SDL_Rect* getCuadro() = 0;
		
	protected:
		int frame;
		Posicionable* animado;
		map <std::string , st_Animacion* > animaciones; // Aca se guardan los struct con los datos de las animaciones
		map <std::string, vector<SDL_Rect> > clips;	// Aca se guardan los clips de las animaciones	
	private:
		void set_clips(vector<st_Animacion*>);
		virtual int seleccionarImagen(int frameActual) = 0;
};

#endif  /* ANIMACION_H */
