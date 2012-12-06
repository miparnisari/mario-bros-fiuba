#include "EventoMoverEnemigo.h"
#include "../jugador/ResolvedorJugador.h"
#include "../modelo/Enemigo.h"

EventoMoverEnemigo::EventoMoverEnemigo(VectorChar v): Evento(v) {
	this->hidratar(v);
}

EventoMoverEnemigo::EventoMoverEnemigo(Enemigo* enemigo): Evento() {
	myID = enemigo->getID();
	tipoEnemigo = enemigo->getNombre();
	miPos = new Point(enemigo->getPos()->x, enemigo->getPos()->y);
	this->tipoMov = enemigo->getTipoMovimiento();
}

EventoMoverEnemigo::~EventoMoverEnemigo() {
	delete (miPos);
}

VectorChar EventoMoverEnemigo::serializar(){
	Utilitario utilitario;
	VectorChar v;
	std::string mensaje = EVENTO_MOVER_ENEMIGO;
	mensaje += SEP;
	mensaje += tipoEnemigo;
	mensaje += SEP;
	mensaje += utilitario.convertirAString(myID);
    mensaje += SEP;
    mensaje += utilitario.convertirAString(miPos->x);
    mensaje += SEP;
    mensaje += utilitario.convertirAString(miPos->y);
    mensaje += SEP;
    mensaje += tipoMov;
	utilitario.borrarCaracter(mensaje, SEPFIN);
	// Borro todos los SEPFIN y agrego uno al final
	
	utilitario.agregarCaracteres(v, mensaje);
	return v;
}

void EventoMoverEnemigo::hidratar(VectorChar v) {
	Utilitario utilitario;
	std::string mensaje = utilitario.convertirVectorAString(v);
	// El Index 0 es el tipo de evento que usaron para instanciar esta clase
	tipoEnemigo = utilitario.separar(mensaje, SEP, 1);
	myID = utilitario.convertirAEntero(utilitario.separar(mensaje, SEP, 2));
	miPos = new Point(utilitario.convertirAEntero(utilitario.separar(mensaje, SEP, 3)),utilitario.convertirAEntero(utilitario.separar(mensaje, SEP, 4)));
	tipoMov = utilitario.separar(mensaje, SEP, 5);
}

void EventoMoverEnemigo::actuar(ResolvedorJugador* res){
	//printf("evento mover enemigo X %f Y %f\n",miPos->x, miPos->y);
	res->moverVistaEnemigo(tipoEnemigo, myID, miPos, tipoMov);
}
