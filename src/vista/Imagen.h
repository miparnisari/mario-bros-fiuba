#ifndef IMAGEN_H
#define IMAGEN_H

// Clase abstracta de donde heredan las imagenes de diferentes formatos

#include <string>
#include <iostream>
#include <exception>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_rotozoom.h"
#include "../modelo/Posicionable.h"
#include "../other/Logger.h"

class Imagen
{
	public:
		Imagen(std::string nombreImagen, Posicionable* elemento, int prior,int alto,int ancho, ID unID, std::string nombre);
		virtual ~Imagen() = 0;
		
		const int 			getAlto();
		const int 			getAncho();
		const int 			getPrioridad();
		const bool 			getActivo();
		SDL_Surface* 		getImg();
		const std::string 		getNombre();
		virtual SDL_Rect* 	getCuadro();
		Point* 				getPos();
		const ID 			getID();
		std::string 		getNombrePers();
		
		void setActivo(bool valor);
		void set_dimension(int ancho,int alto);
		void setID(ID unID);
		void setPos(Point* unaPos);

		SDL_Surface* cargarImagen( std::string nombre );
		void rotarImg(int angulo);
		void resizearImg(double factX, double factY);
		double setFactorXResize(int tam_nivel);
		double setFactorYResize(int tam_nivel);
		
	protected:
		SDL_Surface* img;
		std::string nombre;
		std::string nombreImagen;
		int ancho;
		int alto;
		int prioridad;
		bool activo;
		ID myID;
		Posicionable* posicionable; // Referencia al objeto que representa
		
	private:
		static const string TAG;
};

#endif /* IMAGEN_H */ 
