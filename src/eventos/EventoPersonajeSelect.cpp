#include "EventoPersonajeSelect.h"

EventoPersonajeSelect::EventoPersonajeSelect(VectorChar v): Evento(v) {
	this->hidratar(v);
}

EventoPersonajeSelect::EventoPersonajeSelect(ID unID, std::string unPersonaje): Evento() {
	myID = unID;
    personaje = unPersonaje;
}

EventoPersonajeSelect::~EventoPersonajeSelect() 
{
}

VectorChar EventoPersonajeSelect::serializar(){
	Utilitario utilitario;
	VectorChar v;
	std::string mensaje = EVENTO_PERSONAJESELECT;
	mensaje += SEP;
	mensaje += utilitario.convertirAString(myID);
	mensaje += SEP;
	mensaje += personaje;
	mensaje += SEP;
	utilitario.borrarCaracter(mensaje, SEPFIN);
	// Borro todos los SEPFIN y agrego uno al final
	
	utilitario.agregarCaracteres(v, mensaje);
	return v;
}

void EventoPersonajeSelect::hidratar(VectorChar v) {
	Utilitario utilitario;
	std::string mensaje = utilitario.convertirVectorAString(v);
	// El Index 0 es el tipo de evento que usaron para instanciar esta clase
	myID = utilitario.convertirAEntero(utilitario.separar(mensaje, SEP, 1));
    personaje = utilitario.separar(mensaje, SEP, 2);
}

void EventoPersonajeSelect::actuar(ResolvedorJugador* res){
    res->personajeSelect(myID, personaje);
}

Evento* EventoPersonajeSelect::actuar(ResolvedorServidor* res){
	return (res->personajeSelect(myID, personaje));
}
