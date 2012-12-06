#include "EventoCrearEnemigo.h"
#include "../jugador/ResolvedorJugador.h"

EventoCrearEnemigo::EventoCrearEnemigo(VectorChar v): Evento(v) {
	this->hidratar(v);
}

EventoCrearEnemigo::EventoCrearEnemigo(Enemigo* enemigo): Evento() {
	myID = enemigo->getID();
	tipo = enemigo->getNombre();
	miPos = new Point(enemigo->getPos()->x, enemigo->getPos()->y);
}

EventoCrearEnemigo::~EventoCrearEnemigo() {
	delete (miPos);
}

VectorChar EventoCrearEnemigo::serializar(){
	Utilitario utilitario;
	VectorChar v;
	std::string mensaje = EVENTO_CREAR_ENEMIGO;
	mensaje += SEP;
	mensaje += tipo;
	mensaje += SEP;
	mensaje += utilitario.convertirAString(myID);
    mensaje += SEP;
    mensaje += utilitario.convertirAString(miPos->x);
    mensaje += SEP;
    mensaje += utilitario.convertirAString(miPos->y);

	utilitario.borrarCaracter(mensaje, SEPFIN);
	// Borro todos los SEPFIN y agrego uno al final
	
	utilitario.agregarCaracteres(v, mensaje);
	return v;
}

void EventoCrearEnemigo::hidratar(VectorChar v) {
	Utilitario utilitario;
	std::string mensaje = utilitario.convertirVectorAString(v);
	// El Index 0 es el tipo de evento que usaron para instanciar esta clase
	tipo = utilitario.separar(mensaje, SEP, 1);
	myID = utilitario.convertirAEntero(utilitario.separar(mensaje, SEP, 2));
    miPos = new Point(utilitario.convertirAEntero(utilitario.separar(mensaje, SEP, 3)),utilitario.convertirAEntero(utilitario.separar(mensaje, SEP, 4)));
}

void EventoCrearEnemigo::actuar(ResolvedorJugador* res){
//	printf("evento crear enemigo X %f Y %f\n",miPos->x, miPos->y);
	res->crearEnemigo(tipo, myID, miPos);
}
