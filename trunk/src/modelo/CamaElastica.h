#ifndef CAMAELASTICA_H
#define CAMAELASTICA_H

#include "Plataforma.h"

class CamaElastica: public Plataforma
{
	public:
		CamaElastica(Point* unaPos, int ancho, int alto);
		virtual ~CamaElastica();
		int aplicarColision(Personaje* pers, int res, Point posAnterior);

	private:
		static const string TAG;
};

#endif /* CAMAELASTICA_H */ 
