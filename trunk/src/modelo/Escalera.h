#ifndef ESCALERA_H
#define ESCALERA_H

#include "Elemento.h"
#include "Protagonista.h"
#include "../other/Logger.h"

class Personaje;

class Escalera : public Elemento {
	public:
		Escalera(Point* unaPos, int ancho, int alto);
		~Escalera();
		int aplicarColision(Personaje* unPersonaje, int res, Point posAnterior);
		int colisionaConPersonaje(Personaje* pers);
		
	private:
		static const string TAG;
};

#endif /* ESCALERA_H */
