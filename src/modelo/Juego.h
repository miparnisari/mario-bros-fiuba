#ifndef JUEGO_H_
#define JUEGO_H_

#include <iostream>
#include <list>
#include "Personaje.h"
#include "Protagonista.h"
#include "Nivel.h"
#include "Point.h"
#include "Elemento.h"
//#include "../controlador/EventHandler.h"
#include "../controlador/SoundHandler.h"
#include "../controlador/FpsHandler.h"
#include "../vista/Pantalla.h"
#include "../vista/Imagen.h"
#include "../other/Logger.h"
#include "../comun/Definiciones.h"

using namespace std; 

class Juego {
	private:
		static const string TAG;

		bool activo;
		ListaEstados listaEstados;
		Nivel* nivel;
		

	public:
		Juego(Nivel* nivel);
		~Juego();
		void agregarProtagonista(parJugador prot);
		void agregarEnemigo(Enemigo* enemigo);
		void simular();
		void setActivo(bool param);
		Protagonista* getProtagonista(ID cliente);
		bool puedeMover(ID unID, Point* posNueva);
		bool puedeMoverEnX(ID unID, Point* posNueva);
		bool puedeMoverEnY(ID unID, Point* posNueva);
		int get_anchoNivel();
		int get_altoNivel();
		float getPiso();
		Nivel* getNivel();
		void setNivel(Nivel* nivel);
		void removerProtagonistaEnJuego(ID unID);
		void resolverColisiones();
		int detectarColision(Personaje* pers, Point posAnterior);
		int detectarColisionEnemigo(Personaje* pers, Point posAnterior);
		bool verificarPiso(int alto, Point posicion);
		void aplicarMovimiento(Personaje* pers);
		int detectarColision(ID cliente,Point posAnterior);
		void eliminarEnemigosInactivos();
		void aplicarPow();
};
	
#endif

