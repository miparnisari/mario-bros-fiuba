#ifndef ELEMENTO_H
#define ELEMENTO_H

#include "Point.h"
#include "Posicionable.h"
#include "Personaje.h"

class Elemento: public Posicionable 
{
	public:
		Elemento(Point* unaPos);
		~Elemento();
		Point* getPos();
		void setPos(Point* unaPos);
		void setAncho(int ancho);
		void setAlto(int alto);
		int getAlto();
		int getAncho();
		virtual int colisionaCon(Elemento* elem);
		virtual int colisionaCon(Personaje* unPersonaje);
		bool verticeDentro(float xVert, float yVert, Point* p, int ancho, int alto);
		virtual int aplicarColision(Elemento* elem,int resultado, Point posAnterior);
		virtual int aplicarColision(Personaje* pers,int resultado, Point posAnterior);
		virtual int aplicarColisionConBarril(Elemento* elem){return false;}
		void virtual vivir();
		virtual int colisionConPersonaje(Personaje* pers);
		
	protected:
		Point* posicion;
		int alto;
		int ancho;

};

#endif /* ELEMENTO_H */ 
