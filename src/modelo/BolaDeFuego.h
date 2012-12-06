#ifndef BOLADEFUEGO_H
#define BOLADEFUEGO_H

#include "Enemigo.h"
#include "../movimientos/MovimientoAutomatico.h"
#include "../modelo/Temporizador.h"
#include "../eventos/EventoMoverEnemigo.h"

class ControladorApp;
class Plataforma;
class Escalera;
class BolaDeFuego: public Enemigo
{
	public:
		BolaDeFuego(Point* punto, int ancho, int alto, string Nombre, ID unID, float piso);
		~BolaDeFuego();
		void vivir();
		int aplicarColision(Personaje* pers, int result, Point posAnterior);
		void colisionarConPlataforma(Plataforma* plataforma);
		void colisionarConEscalera(Escalera* esc);	

	private:
		//MovimientoAutomatico* movimiento;
		ID myID;
		int cont;
		int direccion;
		Plataforma* ultPlataforma;
		Escalera* ultEscalera;
		int subirEsc;
};

#endif /* BOLADEFUEGO_H */ 
