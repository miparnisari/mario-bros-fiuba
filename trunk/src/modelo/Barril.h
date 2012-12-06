#ifndef BARRIL_H
#define BARRIL_H

#include "Enemigo.h"
#include "../movimientos/MovimientoAutomatico.h"
#include "../modelo/Temporizador.h"
#include "../eventos/EventoMoverEnemigo.h"

class ControladorApp;
class Plataforma;
class Escalera;
class Fuego;
class Tortuga;

class Barril: public Enemigo
{
	public:
		Barril(Point* punto, int ancho, int alto, string Nombre, ID unID, float piso);
		~Barril();
		void vivir();
		int aplicarColision(Personaje* pers, int result, Point posAnterior);
		void colisionarConPlataforma(Plataforma* plataforma);
		void colisionarConEscalera(Escalera* esc);
		void colisionarConFuego(Fuego* unFuego);
		int colisionarConTortuga(Tortuga* tortuga, Point posAnterior);
		void morir();

	private:
		//MovimientoAutomatico* movimiento;
		ID myID;
		int cont;
		int direccion;
		Plataforma* ultPlataforma;
		Escalera* ultEscalera;
		int bajarEsc;
};

#endif /* BARRIL_H */ 
