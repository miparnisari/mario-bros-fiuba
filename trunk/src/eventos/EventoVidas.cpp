#include "EventoVidas.h"
#include "../jugador/ResolvedorJugador.h"

EventoVidas::EventoVidas(VectorChar v): Evento(v) {
	this->hidratar(v);
}

EventoVidas::EventoVidas(int vidas): Evento() {
	cantVidas = vidas;	
}

VectorChar EventoVidas::serializar(){
	Utilitario utilitario;
	VectorChar v;
	std::string mensaje = EVENTO_VIDAS;
	mensaje += SEP;
	mensaje += utilitario.convertirAString(cantVidas);
    utilitario.borrarCaracter(mensaje, SEPFIN);
	// Borro todos los SEPFIN y agrego uno al final
	
	utilitario.agregarCaracteres(v, mensaje);
	return v;
}

void EventoVidas::hidratar(VectorChar v) {
	Utilitario utilitario;
	std::string mensaje = utilitario.convertirVectorAString(v);
	// El Index 0 es el tipo de evento que usaron para instanciar esta clase
	cantVidas = utilitario.convertirAEntero(utilitario.separar(mensaje, SEP, 1));
}

void EventoVidas::actuar(ResolvedorJugador* res){
	res->dibujarVidas(cantVidas);
}
