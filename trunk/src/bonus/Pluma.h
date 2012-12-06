#ifndef PLUMA_H
#define PLUMA_H

#include "Bonus.h"
#include "../modelo/Protagonista.h"

class Pluma: public Bonus
{
	public:
		Pluma(Point* unaPos, int ancho, int alto, int tiempoVida, string nombre, ID unID, float piso);
		~Pluma();
		virtual int aplicarColision(Personaje* pers, int result, Point posAnterior);
		void vivir();
			
	private:
		static const string TAG;
};

#endif /* PLUMA_H */ 
