#ifndef PLATAFORMA_H
#define PLATAFORMA_H

#include "Elemento.h"
#include "Protagonista.h"
#include "../other/Logger.h"

class Personaje;

class Plataforma : public Elemento {

	public:
		Plataforma(Point* unaPos, int ancho, int alto, float rozamiento);
		~Plataforma();
		virtual int aplicarColision(Personaje* pers, int res, Point posAnterior);
		virtual int aplicarColision(Barril* unBarril) {};
		
	protected:
		static const string TAG;
		float rozamiento;
};

#endif /* PLATAFORMA_H */
