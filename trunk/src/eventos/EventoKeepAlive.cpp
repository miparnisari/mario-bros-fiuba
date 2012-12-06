#include "EventoKeepAlive.h"

EventoKeepAlive::EventoKeepAlive(VectorChar v): Evento(v) {
	this->hidratar(v);
}

EventoKeepAlive::EventoKeepAlive(ID unID): Evento() {
	myID = unID;
}

VectorChar EventoKeepAlive::serializar(){
	Utilitario utilitario;
	VectorChar v;
	std::string mensaje = EVENTO_KEEPALIVE;
	mensaje += SEP;
	mensaje += utilitario.convertirAString(myID);
	mensaje += SEP;
	utilitario.borrarCaracter(mensaje, SEPFIN);
	// Borro todos los SEPFIN y agrego uno al final
	
	utilitario.agregarCaracteres(v, mensaje);
	return v;
}

void EventoKeepAlive::hidratar(VectorChar v) {
	Utilitario utilitario;
	std::string mensaje = utilitario.convertirVectorAString(v);
	// El Index 0 es el tipo de evento que usaron para instanciar esta clase
	myID = utilitario.convertirAEntero(utilitario.separar(mensaje, SEP, 1));
}


Evento* EventoKeepAlive::actuar(ResolvedorServidor* res){
 //  std::cout << "KEEP ALIVE SERVIDOR" << std::endl;
   res->keepAlive(myID);
    return NULL;
}

void EventoKeepAlive::actuar(ResolvedorJugador* res){
//	 std::cout << "KEEP ALIVE JUGADOR" << std::endl;
	 res->keepAlive(myID);
}
