#ifndef FUEGO_H
#define FUEGO_H

#include "Enemigo.h"
#include "Protagonista.h"
#include "BolaDeFuego.h"
#include "Barril.h"
#include "../factories/IdHandler.h"
#include "../other/Logger.h"

class Personaje;
class ControladorApp;
class Nivel;

class Fuego : public Enemigo {

	public:
		Fuego(Point* punto, int ancho, int alto, string nombre, ID unID, Nivel* nivel);
		~Fuego();
		void vivir();
		int aplicarColision(Personaje* pers, int res, Point posAnterior);
		void colisionarConBarril(Barril* barril);
		//~ virtual int aplicarColision(Elemento* elem,int resultado, Point posAnterior);
		
	protected:
		static const string TAG;
		IdHandler* adminID;
		Nivel* nivel;
};

#endif /* FUEGO_H */
