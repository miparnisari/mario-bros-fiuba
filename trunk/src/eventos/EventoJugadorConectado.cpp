#include "EventoJugadorConectado.h"
#include "../app/ControladorApp.h"

EventoJugadorConectado::EventoJugadorConectado(VectorChar v): Evento(v) {
	this->hidratar(v);
}

EventoJugadorConectado::EventoJugadorConectado(ID unID): Evento() {
	myID = unID;
}

VectorChar EventoJugadorConectado::serializar(){
	Utilitario utilitario;
	VectorChar v;
	std::string mensaje = EVENTO_JUGADORCONECTADO;
	mensaje += SEP;
	mensaje += utilitario.convertirAString(myID);
	utilitario.borrarCaracter(mensaje, SEPFIN);
	// Borro todos los SEPFIN y agrego uno al final
	
	utilitario.agregarCaracteres(v, mensaje);
	return v;
}

void EventoJugadorConectado::hidratar(VectorChar v) {
	Utilitario utilitario;
	std::string mensaje = utilitario.convertirVectorAString(v);
	// El Index 0 es el tipo de evento que usaron para instanciar esta clase
	myID = utilitario.convertirAEntero(utilitario.separar(mensaje, SEP, 1));
}

void EventoJugadorConectado::actuar(ResolvedorJugador* res){
	Utilitario u;
	std::string mensaje = "Jugador (ID: " + u.convertirAString(myID) + ") se ha conectado.";
	ControladorApp::getInstance()->setEstado(mensaje);
}
