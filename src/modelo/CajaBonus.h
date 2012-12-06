#ifndef CAJABONUS_H
#define CAJABONUS_H

#include "Plataforma.h"
#include "Protagonista.h"
#include "../other/Logger.h"
#include "../modelo/Temporizador.h"
class Personaje;
class ControladorApp;
class Servidor;
class Juego;
class Nivel;

class CajaBonus : public Plataforma {

	public:
		CajaBonus(Point* unaPos, int ancho, int alto, float rozamiento, Nivel* nivel);
		~CajaBonus();
		int aplicarColision(Personaje* pers, int res, Point posAnterior);
	protected:
		static const string TAG;
		Temporizador* tempBonus;
		Nivel* nivel;
};

#endif /* CAJABONUS_H */
