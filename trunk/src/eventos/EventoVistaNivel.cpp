#include "EventoVistaNivel.h"
#include "../jugador/ResolvedorJugador.h"
#include "../modelo/Point.h"
EventoVistaNivel::EventoVistaNivel(VectorChar v): Evento(v) {
	this->hidratar(v);
}

EventoVistaNivel::EventoVistaNivel(Point* unaPos): Evento() {
	pos = new Point(unaPos->x, unaPos->y);
}

EventoVistaNivel::~EventoVistaNivel() {
	//delete(pos);
}

VectorChar EventoVistaNivel::serializar(){
	Utilitario utilitario;
	VectorChar v;
	std::string mensaje = EVENTO_VISTANIVEL;
	mensaje += SEP;
    mensaje += utilitario.convertirAString(pos->x);
    mensaje += SEP;
    mensaje += utilitario.convertirAString(pos->y);
    utilitario.borrarCaracter(mensaje, SEPFIN);
	// Borro todos los SEPFIN y agrego uno al final
	
	utilitario.agregarCaracteres(v, mensaje);
	delete pos;
	return v;
}

void EventoVistaNivel::hidratar(VectorChar v) {
	Utilitario utilitario;
	std::string mensaje = utilitario.convertirVectorAString(v);
	// El Index 0 es el tipo de evento que usaron para instanciar esta clase
	pos = new Point(utilitario.convertirAEntero(utilitario.separar(mensaje, SEP, 1)),
					utilitario.convertirAEntero(utilitario.separar(mensaje, SEP, 2)));
	
}

void EventoVistaNivel::actuar(ResolvedorJugador* res){
	res->setPosVistaNivel(pos);
}
