#include "EventoMoverVista.h"
#include "../jugador/ResolvedorJugador.h"

EventoMoverVista::EventoMoverVista(VectorChar v): Evento(v) {
	this->hidratar(v);
}

EventoMoverVista::EventoMoverVista(ID unID, Point* unPunto, std::string unMov): Evento() {
	myID = unID;
    miPos = new Point(unPunto->x, unPunto->y);
    miMov = unMov;
}

EventoMoverVista::~EventoMoverVista() {
	delete (miPos);
}

VectorChar EventoMoverVista::serializar(){
	Utilitario utilitario;
	VectorChar v;
	std::string mensaje = EVENTO_MOVERVISTA;
	mensaje += SEP;
	mensaje += utilitario.convertirAString(myID);
    mensaje += SEP;
    mensaje += utilitario.convertirAString(miPos->x);
    mensaje += SEP;
    mensaje += utilitario.convertirAString(miPos->y);
    mensaje += SEP;
    mensaje += miMov;
	utilitario.borrarCaracter(mensaje, SEPFIN);
	// Borro todos los SEPFIN y agrego uno al final
	
	utilitario.agregarCaracteres(v, mensaje);
	return v;
}

void EventoMoverVista::hidratar(VectorChar v) {
	Utilitario utilitario;
	std::string mensaje = utilitario.convertirVectorAString(v);
	// El Index 0 es el tipo de evento que usaron para instanciar esta clase
	myID = utilitario.convertirAEntero(utilitario.separar(mensaje, SEP, 1));
	miPos = new Point(utilitario.convertirAEntero(utilitario.separar(mensaje, SEP, 2)),utilitario.convertirAEntero(utilitario.separar(mensaje, SEP, 3)));
    miMov = utilitario.separar(mensaje, SEP, 4);
}

void EventoMoverVista::actuar(ResolvedorJugador* res){
	res->moverVista(myID,miPos,miMov);
}
