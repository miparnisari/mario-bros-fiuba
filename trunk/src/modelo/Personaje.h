 #ifndef PERSONAJE_H_
#define PERSONAJE_H_

#include "Point.h"
#include "Posicionable.h"
#include "../comun/Definiciones.h"
#include "../other/Logger.h"
#include "../movimientos/MovimientoPersonaje.h"

// Implementa interfaz posicionable
class Elemento;
class Barril;
class Escalera;
class Plataforma;
class Armadura;
class VidaExtra;
class Hongo;
class Tortuga;
class BolaDeFuego;
class PlataformaInclinada;
class ControladorApp;
class Fuego;
class Princesa;
class CamaElastica;
class Pluma;

class Personaje: public Posicionable
{
	public:

		Personaje(Point* unPunto, int ancho, int alto, string nombre, float piso);
		virtual ~Personaje();
	//	void mover(tipoMovimiento dir,int m);
	//	void set_velocidad(int velocidad);
	//	int get_velocidad();
		int getAncho();
		int getAlto();
		MovimientoPersonaje* getMovimiento();
		void setID(ID unID);
		ID getID();
		string getNombre();
		virtual Point* getPos();
		virtual void setPos(Point* unaPos);
		virtual void vivir() = 0;
		virtual void mover(int result) = 0;
		int colisionaCon(Elemento*);
		int colisionaCon(Personaje*);
		void aplicarMovimiento();
		virtual int aplicarColision(Personaje* pers, int result, Point posAnterior);
		virtual int aplicarColision(Elemento* elem, int result, Point posAnterior);
		bool verticeDentro(float xVert, float yVert, Point* p, int ancho, int alto);
		void aplicarRozamiento(float rozamiento);
		virtual void colisionarConArmadura(Armadura* armadura) {};
		virtual void colisionarConVidaExtra(VidaExtra* vidaExtra) {};
		virtual void colisionarConBarril(Barril* barril) {};
		virtual void colisionarConBolaDeFuego(BolaDeFuego* bola) {};
		virtual int colisionarConHongo(Hongo* hongo, Point posAnterior);
		virtual int colisionarConTortuga(Tortuga* tortuga, Point posAnterior);
		virtual void colisionarConPlataforma(Plataforma* plataforma) {};
		virtual void colisionarConEscalera(Escalera* escalera) {};
		virtual void colisionarConFuego(Fuego* unFuego) {};
		virtual void colisionarConPrincesa(Princesa* princesa) {};
		virtual void colisionarConCamaElastica(CamaElastica* cama, Point posAnterior) {};
		virtual void colisionarConPluma(Pluma* pluma, Point posAnterior){};
		virtual int getVidas(){return 1;}
		
	private:
		static const string TAG;
		
	protected:
		Point* posicion;
		int ancho, alto;
		MovimientoPersonaje* movimiento;
		//ID cliente;
		string nombre;
		ID myID;
};
	
#endif
