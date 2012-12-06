#ifndef ARMADURA_H
#define ARMADURA_H

#include "Bonus.h"
#include "../modelo/Personaje.h"
#include "../eventos/EventoSonido.h"

class ControladorApp;
class Escalera;

class Armadura : public Bonus
{
	public:
		Armadura(Point* unaPos, int ancho, int alto, int tiempoVida, string nombre, ID unID, float piso);
		~Armadura();
		int aplicarColision(Personaje* pers, int resultado, Point posAnterior);
		void colisionarConEscalera(Escalera* escalera);
		void vivir();
			
	private:
		static const string TAG;
};

#endif /* ARMADURA_H */ 
