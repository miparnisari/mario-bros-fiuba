#ifndef ESTADOENEMIGO_H
#define ESTADOENEMIGO_H
#include "../comun/Definiciones.h"
#include "../movimientos/MovimientoPersonaje.h"
//#include "../jugador/ControladorJugador.h"

//class ControladorJugador;
class ControladorApp;

typedef struct{
	Enemigo* enemigo;
	Point PosAnterior;
	Point UltimaPos;
}st_Enemigo;

class EstadoEnemigo
{
	public:
		EstadoEnemigo();
		~EstadoEnemigo();
	    void agregarEnemigo(Enemigo* enemigo);
	    void eliminarEnemigo(Enemigo* enemigo);
        void actualizarPosicion();

	private:
		list<st_Enemigo*> enemigos;
		int cont;
		//Mutex* m;
};

#endif /* ESTADOENEMIGO_H */ 
