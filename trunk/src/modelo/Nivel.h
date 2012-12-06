#ifndef NIVEL_H
#define NIVEL_H

#include "Personaje.h"
#include "Protagonista.h"
#include "Enemigo.h"
#include "Elemento.h"
#include <list>
#include "../other/Logger.h"
#include "../comun/Definiciones.h"
#include "../eventos/EventoEliminarEnemigo.h"
#include "../factories/FactoryBonus.h"
#include "../bonus/Bonus.h"

class ControladorApp;

class Nivel
{
	public:
		Nivel(int alto, int ancho, int piso);
		~Nivel();
		void agregarPersonaje(Personaje* pers);
		Protagonista* getProtagonista(ID cliente);

		void agregarPersEnJuego(Personaje* pers);
		void agregarPersonaje(Protagonista* pers);
		void agregarProtagonista(parJugador jug);
		void agregarElemento(Elemento* elem);
		void agregarEnemigo(Enemigo* enemigo);
		void eliminarEnemigo(Enemigo* enemigo);
		void removerProtagonistaEnJuego(ID cliente);

		bool verificarPiso(int alto, Point posicion);
		bool puedeMover(ID unID, Point* posNueva);
		bool puedeMoverEnX(ID unID,Point* posNueva);
		bool puedeMoverEnY(ID unID,Point* posNueva);

		int getAncho();
		int getAlto();
		int getPiso();
		int getProtagonistasVivos();
		
		void vivir();

		void resolverColisiones();
		int detectarColision(Personaje* pers, Point posAnterior);
		int detectarColisionEnemigo(Personaje* pers, Point posAnterior);
		int detectarColision(Elemento* elem, Point posAnterior);
		void aplicarMovimiento(Personaje* pers);

		// Metodos para eliminar enemigos inactivos
		bool dentroDeLimites(Point* pos);
		void eliminarEnemigosInactivos();
		
		void aplicarPow();
		
	private:
		static const string TAG;
		
		int ancho, alto, piso;
		list<Personaje*> listaPersEnJuego;
		list<Protagonista*> listaPersonajes;
		list<Elemento*> listaElementos;
		Enemigos mapEnemigos;
		
		void marcarInactivos();
		
};

#endif /* NIVEL_H */ 
