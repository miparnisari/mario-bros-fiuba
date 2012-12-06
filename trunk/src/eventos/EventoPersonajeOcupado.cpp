#include "EventoPersonajeOcupado.h"

using namespace std;

const string EventoPersonajeOcupado::TAG = "EventoPersonajeOcupado";

EventoPersonajeOcupado::EventoPersonajeOcupado(VectorChar v): Evento(v) {
	this->hidratar(v);
}

EventoPersonajeOcupado::EventoPersonajeOcupado(): Evento() {
}

VectorChar EventoPersonajeOcupado::serializar(){
	Utilitario utilitario;
	VectorChar v;
	string mensaje;
	
	mensaje = EVENTO_PERSONAJE_OCUPADO;
	mensaje += SEP; // No se si esto va!
	utilitario.agregarCaracteres(v, mensaje);
	return v;
}

void EventoPersonajeOcupado::hidratar(VectorChar v) {
	// TODO
}

void EventoPersonajeOcupado::actuar(ResolvedorJugador* res){
	// TODO
}
