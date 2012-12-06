#ifndef BONUS_H
#define BONUS_H

#include "../modelo/Point.h"
#include "../modelo/Enemigo.h"
#include "../modelo/Personaje.h"
#include "../movimientos/MovimientoAutomatico.h"
#include "../modelo/Temporizador.h"

// Clase abstracta
class Bonus: public Enemigo
{
	public:
		Bonus(Point* unaPos, int ancho, int alto, int velocidad, int tiempoVida, string nombre, ID unID, float piso);
		~Bonus();
		virtual int aplicarColision(Personaje* prot, int resultado);
		virtual void vivir();
		void setMovimiento(MovimientoAutomatico* unMov);
			
	private:
		static const string 	TAG;
		
	protected:
		int tiempoVidaSegs;
};

#endif /* BONUS_H */ 
