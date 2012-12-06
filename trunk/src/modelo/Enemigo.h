#ifndef ENEMIGO_H
#define ENEMIGO_H

#include "Personaje.h"
#include "../modelo/Temporizador.h"
//#include "../movimientos/MovimientoAutomatico.h"

class Enemigo: public Personaje
{
	public:
		Enemigo(Point* punto, int ancho, int alto, string Nombre, ID unID, float piso);
		virtual void vivir() = 0;
		void mover(int result);
		void setModificado(bool estado);
		void setActivo(bool estado);
		void setMorir(bool estado);
		bool getModificado();
		bool getActivo();
		bool getMorir();
		virtual void aplicarPow();
		virtual std::string getTipoMovimiento();
		//MovimientoAutomatico* getMovimiento();
		//void aplicarRozamiento(float rozamiento);

	protected:
		bool activo;
		bool modificado;
		bool morir;
		Temporizador* temp;
		//MovimientoAutomatico* movimiento;
};

#endif /* ENEMIGO_H */ 
