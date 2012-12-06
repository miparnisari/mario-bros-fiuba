#include "EventoDibujar.h"
#include "../jugador/ResolvedorJugador.h"

EventoDibujar::EventoDibujar(VectorChar v): Evento(v) {
	this->hidratar(v);
	
}

EventoDibujar::EventoDibujar(std::string unElemento, bool unEstado): Evento() {
	activo = unEstado;
	elemento = unElemento;

}

VectorChar EventoDibujar::serializar(){
	Utilitario utilitario;
	VectorChar v;
	std::string mensaje = EVENTO_DIBUJAR;
	mensaje += SEP;
	mensaje += elemento;
	mensaje += SEP;
	mensaje += utilitario.convertirAString(activo);
    utilitario.borrarCaracter(mensaje, SEPFIN);
	// Borro todos los SEPFIN y agrego uno al final
	
	utilitario.agregarCaracteres(v, mensaje);

	return v;
}

void EventoDibujar::hidratar(VectorChar v) {
	Utilitario utilitario;
	std::string mensaje = utilitario.convertirVectorAString(v);
	// El Index 0 es el tipo de evento que usaron para instanciar esta clase
	elemento = utilitario.separar(mensaje, SEP, 1);
	activo = utilitario.convertirAEntero(utilitario.separar(mensaje, SEP, 2));
	
}

void EventoDibujar::actuar(ResolvedorJugador* res){

	res->dibujarBonus(elemento, activo);
}
