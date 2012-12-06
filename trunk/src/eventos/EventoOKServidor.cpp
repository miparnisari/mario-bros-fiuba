#include "EventoOKServidor.h"

EventoOKServidor::EventoOKServidor(VectorChar v): Evento(v) {
	this->hidratar(v);
}

EventoOKServidor::EventoOKServidor(ID unID): Evento() {
	myID = unID;
}

VectorChar EventoOKServidor::serializar(){
	Utilitario utilitario;
	VectorChar v;
	std::string mensaje = EVENTO_OKSERVIDOR;
	mensaje += SEP;
	mensaje += utilitario.convertirAString(myID);
	mensaje += SEP;
	utilitario.borrarCaracter(mensaje, SEPFIN);
	// Borro todos los SEPFIN y agrego uno al final
	
	utilitario.agregarCaracteres(v, mensaje);
	return v;
}

void EventoOKServidor::hidratar(VectorChar v) {
	Utilitario utilitario;
	std::string mensaje = utilitario.convertirVectorAString(v);
	// El Index 0 es el tipo de evento que usaron para instanciar esta clase
	myID = utilitario.convertirAEntero(utilitario.separar(mensaje, SEP, 1));
}

void EventoOKServidor::actuar(ResolvedorJugador* res){
	//printf("ResolvedorJugador\n");
    res->OKServidor(myID);
}

Evento* EventoOKServidor::actuar(ResolvedorServidor* res){
	//printf("ResolvedorServidor\n");
	res->OKServidor(myID);
    return NULL;
}
