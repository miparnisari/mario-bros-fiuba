#ifndef PROTAGONISTA_H
#define PROTAGONISTA_H

#include "Personaje.h"
#include "../eventos/EventoVidas.h"
#include "../comun/Definiciones.h"
#include "Temporizador.h"
#include "../eventos/EventoGameOver.h"
class Hongo;
class Armadura;
class VidaExtra;
class Barril;
class ControladorJugador;
class Elemento;
class ControladorApp;
class Princesa;

class Protagonista: public Personaje
{
	public:
		Protagonista(Point* punto, int ancho, int alto, int velocidad,int potenciaSalto, ID cliente, string Nombre, float piso);
		~Protagonista();
		void vivir();
		void saltar();
		void caer();
		void mover(int fuerza);
		//int colisionaCon(Elemento* elem);
		void ganarVidas(int cantidad);
		void perderVidas(int cantidad);
		virtual void colisionarConBarril(Barril* barril);
		void colisionarConFuego(Fuego* unFuego);
		void setArmadura(bool valor);
		void colisionarConArmadura(Armadura* armadura);
		void colisionarConVidaExtra(VidaExtra* vidaExtra);
		void colisionarConPrincesa(Princesa* princesa);
		int colisionarConHongo(Hongo* hongo, Point posAnterior);
		int colisionarConTortuga(Tortuga* tortuga, Point posAnterior);
		void colisionarConBolaDeFuego(BolaDeFuego* bola);
		void colisionarConCamaElastica(CamaElastica* cama, Point posAnterior);
		void colisionarConPluma(Pluma* pluma, Point posAnterior);
		//MovimientoPersonaje* getMovimiento();
		//void aplicarRozamiento(float rozamiento);
		int getVidas();
	private:
		static const string TAG;
		ID cliente;
		int vidas;
		bool armadura;
		Temporizador* tempVidas;
		Temporizador* tempBonus;
		bool vivo; // para que no se mande el sonido de morir twice
		Point* posRespawn;
		//MovimientoPersonaje* movimiento;

};

#endif /* PROTAGONISTA_H */ 
