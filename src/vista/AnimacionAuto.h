#ifndef ANIMACIONAUTO_H_
#define ANIMACIONAUTO_H_

#include <string>
#include <iostream>
#include "Animacion.h"
#include "../excepciones/Excepciones.h"
#include "../other/Logger.h"
#include "../modelo/Temporizador.h"

class AnimacionAuto : public Animacion
{
	private:

		Temporizador temp;
		map <std::string , st_Animacion* >::iterator iterador;

		int seleccionarImagen(int frameActual);
		void nextAnimacion();
		
		static const string TAG;
	
	public:
		AnimacionAuto(std::string nombre, Posicionable* animado, int prior,int alto, int ancho, vector<st_Animacion*> vectorAnimaciones, ID unID,std::string nombrePers);
		~AnimacionAuto();
		SDL_Rect* getCuadro();
};

#endif /* ANIMACIONAUTO_H_ */
