#include "EventoSalir.h"
#include "../app/ControladorApp.h"
#include "../jugador/ControladorJugador.h"
EventoSalir::EventoSalir(VectorChar v): Evento(v) {
	this->hidratar(v);
}

EventoSalir::EventoSalir(ID unID): Evento() {
	myID = unID;
}

VectorChar EventoSalir::serializar(){
	Utilitario utilitario;
	VectorChar v;
	std::string mensaje = EVENTO_SALIR;
	mensaje += SEP;
	mensaje += utilitario.convertirAString(myID);
	utilitario.borrarCaracter(mensaje, SEPFIN);
	// Borro todos los SEPFIN y agrego uno al final
	
	utilitario.agregarCaracteres(v, mensaje);
	return v;
}

void EventoSalir::hidratar(VectorChar v) {
	Utilitario utilitario;
	std::string mensaje = utilitario.convertirVectorAString(v);
	// El Index 0 es el tipo de evento que usaron para instanciar esta clase
	myID = utilitario.convertirAEntero(utilitario.separar(mensaje, SEP, 1));
}

Evento* EventoSalir::actuar(ResolvedorServidor* res){
	Utilitario u;
	std::string mensaje = "Jugador (ID: " + u.convertirAString(myID) + ") se ha desconectado.";
	ControladorApp::getInstance()->setEstado(mensaje);
	ControladorApp::getInstance()->singlePlayerSelect = false;
	Evento* eventoRespuesta = res->desconectarJugador(myID);
	return eventoRespuesta;
}
