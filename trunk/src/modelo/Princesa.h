#ifndef PRINCESA_H
#define PRINCESA_H

#include "Enemigo.h"
#include "../movimientos/MovimientoIzquierdaDerecha.h"
#include "../factories/IdHandler.h"
#include "Barril.h"


class ControladorApp;
class Nivel;

class Princesa: public Enemigo
{
	public:

		Princesa(Point* punto, int ancho, int alto, string nombre, ID unID, Nivel* nivel);
		virtual ~Princesa();
		void vivir();
		void mover(int result);
		int aplicarColision(Personaje* pers, int result, Point posAnterior);
	
	private:
		Nivel* nivel;
};

#endif /* PRINCESA_H */ 
