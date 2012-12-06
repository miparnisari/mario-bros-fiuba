#ifndef VIDAEXTRA_H_
#define VIDAEXTRA_H_

#include "Bonus.h"
#include "../modelo/Personaje.h"
#include "../eventos/EventoSonido.h"

class ControladorApp;

class VidaExtra : public Bonus
{
	public:
		VidaExtra(Point* unaPos, int ancho, int alto, int tiempoVida, string nombre, ID unID, float piso);
		virtual ~VidaExtra();
		void vivir();
		int aplicarColision(Personaje* pers, int resultado, Point posAnterior);
		
	private:
		static const string TAG;
};

#endif /* VIDAEXTRA_H_ */
