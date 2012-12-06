#ifndef VISTANIVEL_H
#define VISTANIVEL_H

#include "Imagen.h"
#include "../modelo/Protagonista.h"

class VistaNivel: public Imagen
{
	public:
		VistaNivel(std::string nombre, Posicionable* elemento,int scroll,int anchoPantalla, int altoPantalla, int anchoNivel, int altoNivel, int prior, ID unID, std::string nombrePers);
		~VistaNivel(); 
		SDL_Rect* getCuadro();
		void set_vistaProt(Imagen* pers);
		void setVisor(Point* p);
	private:
		SDL_Rect visor;
		Imagen* protagonista;
		int scroll; 
		int anchoPantalla;
		int altoPantalla;
		int lvlWidth;
		int lvlHeight;
};

#endif /* VISTANIVEL_H */ 
