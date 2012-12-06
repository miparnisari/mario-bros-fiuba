#ifndef HONGO_H
#define HONGO_H

#include "Enemigo.h"
#include "../movimientos/MovimientoAutomatico.h"
#include "../modelo/Temporizador.h"
#include "../eventos/EventoMoverEnemigo.h"

class ControladorApp;
class Tortuga;

class Hongo: public Enemigo
{
	public:
		Hongo(Point* punto, int ancho, int alto, string Nombre, ID unID, float piso);
		~Hongo();
		void vivir();
		int aplicarColision(Personaje* pers, int result, Point posAnterior);
		void morir();
		void aplicarPow();
		int colisionarConTortuga(Tortuga* tortuga, Point posAnterior);
		std::string getTipoMovimiento();
			
	private:
		//MovimientoAutomatico* movimiento;
		ID myID;
		int cont;
		bool mareado;
		int direccion;
};

#endif /* HONGO_H */ 
