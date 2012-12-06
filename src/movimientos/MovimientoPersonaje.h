#ifndef MOVIMIENTOPERSONAJE_H
#define MOVIMIENTOPERSONAJE_H
#include "Movimiento.h"
#include "../modelo/Point.h"
#include <iostream>
class MovimientoPersonaje : public Movimiento
{
	public:
		MovimientoPersonaje(Point* unaPosicion, int potencia, int velocidad, float piso);
		
		void aplicarFuerza(double fuerza);

		void saltar();
		void caer();
		void subir();
		void bajar();
		void detenerCaida();
		void detenerDesplazamiento();
		void setPuedeVolar(bool estado);
      	void setQuiereVolar(bool estado);

      	bool getQuiereBajar();
        bool getQuiereSubir();
        bool getPresionada();
        void setPresionada(bool estado);
      	
      	void setQuiereSubir(bool estado);
      	void setQuiereBajar(bool estado);
      	
      	void setRozamiento(float rozamiento);
      	void empujarEnY(double impulso);
      	void saltarAlto();

      	double getVelocidadX();
      	double getVelocidadY();
      	void setVelocidadX(double valor);
      	void setVelocidadY(double valor);
		void rebotar();
		
		void setPuedeSaltar(bool estado);
		
		bool estaSiendoEmpujado;
		bool sePuedeSaltar;
		bool presionada;
		bool quiereVolar;
		bool rebotando;
		  
	private:
      	void actualizar();
      	bool topeSaltoAlcanzado();
		float rozamiento;
		bool dobleSalto;
        bool puedeVolar;
		
		
		
		
		bool quiereSubir;
		bool quiereBajar;
       	float C1;
};

#endif /* MOVIMIENTOPERSONAJE_H */ 
