#ifndef ANIMACIONPROTAGONISTA_H
#define ANIMACIONPROTAGONISTA_H

#include "Animacion.h"
#include "../other/Logger.h"
#include "../comun/Definiciones.h"

class AnimacionProtagonista : public Animacion {
	
	private:
		static const string TAG;
		std::string estadoAnimacion;
		int margenScroll;
		
		void set_clips(vector<st_Animacion*>);
		int seleccionarImagen(int frameActual);

	public:
		AnimacionProtagonista(std::string nombre, Posicionable* animado, int prior,int alto, int ancho, vector<st_Animacion*> vectorAnimaciones, ID idCliente, std::string nombrePers);
		~AnimacionProtagonista();
		SDL_Rect* getCuadro();
		int getMargenScroll();
		void setMargenScroll(int scroll);
		void setEstadoAnimacion(std::string estado);

};

#endif /* ANIMACIONPROTAGONISTA_H */
