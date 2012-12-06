#ifndef ESTADOJUGADOR_H
#define ESTADOJUGADOR_H
#include "../comun/Definiciones.h"
#include "../modelo/Point.h"
#include "../movimientos/MovimientoPersonaje.h"
//#include "../jugador/ControladorJugador.h"
#include "../app/ControladorApp.h"
//class ControladorJugador;
//class ControladorApp;

class EstadoJugador
{
	public:
		EstadoJugador(ID unID);
		~EstadoJugador();
		void teclaPresionada(int tecla);
		void teclaSoltada(int tecla);
		void setTeclaJustReleased(bool unEstado);
		bool estadoTecla(int tecla);
		bool getModificado();
		void setModificado(bool unEstado);
		void setSaltando(bool unEstado);
        ID getID();
        Point* getPos();
        // Si el parametro difiere de la posicion que tengo
        // entonces devuelvo true y actualizo la posicion
        bool actualizarPosicion(MovimientoPersonaje* mov, std::string& tipoMov);
		void cambiarPosicion(float x, float y);
	private:
		bool teclaValida(int tecla);
		std::string ultimoMovToString();
		//int contDer;
		//int contIzq;
		int teclasPresionadas[CANT_TECLAS];
        ID myID;
        Point* ultimaPosicion;
        Point* posicion;
        tipoMovimiento ultimoMov;
       // tipoMovimiento tipo;
		bool estaSaltando;
        bool modificado;
        bool teclaJustReleased;
        //Mutex* m;
};

#endif /* ESTADOJUGADOR_H */ 
