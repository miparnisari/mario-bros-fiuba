#include "EventoIniciarJuego.h"

EventoIniciarJuego::EventoIniciarJuego(VectorChar v): Evento(v) {
	this->hidratar(v);
}

EventoIniciarJuego::EventoIniciarJuego(ID unID): Evento() {
	myID = unID;
}

VectorChar EventoIniciarJuego::serializar(){
	Utilitario utilitario;
	VectorChar v;
	std::string mensaje = EVENTO_INICIARJUEGO;
	mensaje += SEP;
	mensaje += utilitario.convertirAString(myID);
	utilitario.borrarCaracter(mensaje, SEPFIN);
	// Borro todos los SEPFIN y agrego uno al final
	
	utilitario.agregarCaracteres(v, mensaje);
	return v;
}

void EventoIniciarJuego::hidratar(VectorChar v) {
	Utilitario utilitario;
	std::string mensaje = utilitario.convertirVectorAString(v);
	// El Index 0 es el tipo de evento que usaron para instanciar esta clase
	myID = utilitario.convertirAEntero(utilitario.separar(mensaje, SEP, 1));
}

void EventoIniciarJuego::actuar(ResolvedorJugador* res){
	res->iniciarJuego(myID);
}
