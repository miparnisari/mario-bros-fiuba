#ifndef POW_H
#define POW_H

#include "Plataforma.h"
#include "Protagonista.h"
#include "../other/Logger.h"

class Personaje;
class ControladorApp;
class Servidor;
class Juego;

class Pow : public Plataforma {

	public:
		Pow(Point* unaPos, int ancho, int alto, float rozamiento);
		~Pow();
		int aplicarColision(Personaje* pers, int res, Point posAnterior);

	protected:
		static const string TAG;
		bool activo;
};

#endif /* POW_H */
