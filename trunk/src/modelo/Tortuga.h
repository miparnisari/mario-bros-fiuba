#ifndef TORTUGA_H_
#define TORTUGA_H_

#include "Enemigo.h"
#include "../movimientos/MovimientoAutomatico.h"
#include "../modelo/Temporizador.h"
#include "../eventos/EventoMoverEnemigo.h"

class ControladorApp;
class Plataforma;

class Tortuga : public Enemigo
{
	public:
		Tortuga(Point* punto, int ancho, int alto, string Nombre, ID unID, float piso);
		~Tortuga();
		void vivir();
		int aplicarColision(Personaje* pers, int result, Point posAnterior);
		void morir();
		void desplazar(int desplazamiento);
		void hacerseCaparazon();
		void aplicarPow();
		void colisionarConPlataforma(Plataforma* plataforma);
		std::string getTipoMovimiento();
		bool esCaparazon;
		bool quieto;
		int direccion;

	private:
		ID myID;
		int cont;
};

#endif /* TORTUGA_H_ */
