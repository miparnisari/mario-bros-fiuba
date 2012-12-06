#ifndef MONO_H
#define MONO_H

#include "Enemigo.h"
#include "../movimientos/MovimientoIzquierdaDerecha.h"
#include "../factories/IdHandler.h"
#include "Barril.h"


class ControladorApp;
class Nivel;

class Mono: public Enemigo
{
	public:

		Mono(Point* punto, int ancho, int alto, string nombre, ID unID, Nivel* nivel);
		virtual ~Mono();
		void vivir();
		void mover(int result);
	
	private:
		//Temporizador* temp;
		IdHandler* adminID;
		Nivel* nivel;
};

#endif /* MONO_H */ 
