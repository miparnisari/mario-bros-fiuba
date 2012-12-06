#include "EventoEliminarEnemigo.h"
#include "../jugador/ResolvedorJugador.h"

EventoEliminarEnemigo::EventoEliminarEnemigo(VectorChar v): Evento(v) {
	this->hidratar(v);
}

EventoEliminarEnemigo::EventoEliminarEnemigo(Enemigo* enemigo): Evento() {
	myID = enemigo->getID();
	tipo = enemigo->getNombre();
}

EventoEliminarEnemigo::EventoEliminarEnemigo(ID unID, std::string unNombre): Evento() {
	myID = unID;
	tipo = unNombre;
}
VectorChar EventoEliminarEnemigo::serializar(){
	Utilitario utilitario;
	VectorChar v;
	std::string mensaje = EVENTO_ELIMINAR_VISTA_ENEMIGO;
	mensaje += SEP;
	mensaje += tipo;
	mensaje += SEP;
	mensaje += utilitario.convertirAString(myID);
    mensaje += SEP;

	utilitario.borrarCaracter(mensaje, SEPFIN);
	// Borro todos los SEPFIN y agrego uno al final
	
	utilitario.agregarCaracteres(v, mensaje);
	return v;
}

void EventoEliminarEnemigo::hidratar(VectorChar v) {
	Utilitario utilitario;
	std::string mensaje = utilitario.convertirVectorAString(v);
	// El Index 0 es el tipo de evento que usaron para instanciar esta clase
	tipo = utilitario.separar(mensaje, SEP, 1);
	myID = utilitario.convertirAEntero(utilitario.separar(mensaje, SEP, 2));
}

void EventoEliminarEnemigo::actuar(ResolvedorJugador* res){
	res->eliminarVistaEnemigo(tipo, myID);
}
