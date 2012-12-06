#ifndef PERSONAJEANIMADO_H
#define PERSONAJEANIMADO_H

#include "Personaje.h"
#include "Temporizador.h"
#include "../other/Logger.h"
#include "../movimientos/MovimientoAutomatico.h"

class PersonajeAnimado: public Personaje
{
	public:
		PersonajeAnimado(Point* punto, int ancho, int alto, string Nombre, float piso);
		~PersonajeAnimado();
		void vivir();
		virtual void mover(int result);
		
		bool getActivo();
		void setActivo(bool estado);
		MovimientoAutomatico* getMovimiento();
		void aplicarRozamiento(float rozamiento);
		
	protected:
		static const string TAG;
		Temporizador temp;
		MovimientoAutomatico* movimiento;
		bool activo;
		
		void animar();
};

#endif /* PERSONAJEANIMADO_H */ 
