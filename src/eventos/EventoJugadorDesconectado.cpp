#include "EventoJugadorDesconectado.h"
#include "../app/ControladorApp.h"

EventoJugadorDesconectado::EventoJugadorDesconectado(VectorChar v): Evento(v) {
	this->hidratar(v);
}

EventoJugadorDesconectado::EventoJugadorDesconectado(ID unID): Evento() {
	myID = unID;
}

VectorChar EventoJugadorDesconectado::serializar(){
	Utilitario utilitario;
	VectorChar v;
	std::string mensaje = EVENTO_JUGADORDESCONECTADO;
	mensaje += SEP;
	mensaje += utilitario.convertirAString(myID);
	utilitario.borrarCaracter(mensaje, SEPFIN);
	// Borro todos los SEPFIN y agrego uno al final
	
	utilitario.agregarCaracteres(v, mensaje);
	return v;
}

void EventoJugadorDesconectado::hidratar(VectorChar v) {
	Utilitario utilitario;
	std::string mensaje = utilitario.convertirVectorAString(v);
	// El Index 0 es el tipo de evento que usaron para instanciar esta clase
	myID = utilitario.convertirAEntero(utilitario.separar(mensaje, SEP, 1));
}

void EventoJugadorDesconectado::actuar(ResolvedorJugador* res){
	Utilitario u;
	std::string mensaje = "Jugador (ID: " + u.convertirAString(myID) + ") se ha desconectado.";
	ControladorApp::getInstance()->setEstado(mensaje);
//	res->avisarDesconeccionJugador(myID);
	// Paso la imagen de una lista a otra
	res->desocuparVistaPersonaje(myID);

}
