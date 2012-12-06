#ifndef CANIERIA_H
#define CANIERIA_H
#include "FactoryHongos.h"
#include "FactoryBolasFuego.h"
#include "FactoryTortugas.h"
#include "../modelo/Elemento.h"
#include "IdHandler.h"

class ControladorApp;
class ControladorJugador;
class Nivel;

class Canieria: public Elemento
{
	public:
		Canieria(Point* p, int ancho, int alto, Nivel* n, IdHandler* idHandler);
		~Canieria();
		void vivir();
		int aplicarColision(Elemento* elem,int resultado, Point posAnterior);
		int aplicarColision(Personaje* pers,int resultado, Point posAnterior);
			
	private:
		FactoryHongos* factHongos;
		FactoryBolasFuego* factBolas;
		FactoryTortugas* factTortugas;
		Nivel* nivel;
		IdHandler* asignadorID;
};

#endif /* CANIERIA_H */ 
