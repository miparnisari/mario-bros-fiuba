#ifndef MOVIMIENTO_H
#define MOVIMIENTO_H
#include "Movimiento.h"
#include "../modelo/Point.h"

#include <iostream>

#define POTENCIA_CAIDA 3

class Movimiento
{
	public:
		Movimiento(Point* unaPosicion, int potencia, int velocidad, float piso);
		~Movimiento();
		
		
		Point* getPos();
		void setPos(Point pos);

		void aplicarFuerza(double fuerza);
		void saltar();
		void caer();
		void caerSinSalto();

		bool estaSaltando();
      	bool estaCayendo();
      	void setSaltando(bool estado);

       	void detenerEnX();
      	void detenerEnY();
      	float getPiso();
      	
      	bool rebotando;
      	bool cayendo;
		bool caidaSinSalto;

  	protected:
		// Magnitudes fisicas vectoriales
		Point velocidad;
		bool saltando;
		int potenciaSalto;
		double posVertInicial;
		double posFinal;
		Point* posicion;
		
		virtual void actualizar();
};

#endif /* MOVIMIENTO_H */ 
