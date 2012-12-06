#include "EventoNivel.h"
#include "../app/ControladorApp.h"

const string EventoNivel::TAG = "EventoNivel";

EventoNivel::EventoNivel(VectorChar v): Evento(v) {
	this->hidratar(v);
}

EventoNivel::EventoNivel(ID unID, std::string unNivel): Evento() {
	myID = unID;
    nivel = unNivel;
}

VectorChar EventoNivel::serializar(){
	Utilitario utilitario;
	VectorChar v;
	std::string mensaje = EVENTO_NIVEL;
	mensaje += SEP;
	mensaje += utilitario.convertirAString(myID);
	mensaje += SEP;
	mensaje += nivel;
	mensaje += SEP;
	utilitario.borrarCaracter(mensaje, SEPFIN);
	// Borro todos los SEPFIN y agrego uno al final
	
	utilitario.agregarCaracteres(v, mensaje);
	std::string m = "Enviando nivel: " + nivel;
	ControladorApp::getInstance()->setEstado(m);
	Logger::info (TAG, m);
	return v;
}

void EventoNivel::hidratar(VectorChar v) {
	Utilitario utilitario;
	std::string mensaje = utilitario.convertirVectorAString(v);
	// El Index 0 es el tipo de evento que usaron para instanciar esta clase
	myID = utilitario.convertirAEntero(utilitario.separar(mensaje, SEP, 1));
    nivel = utilitario.separar(mensaje, SEP, 2);
}

void EventoNivel::actuar(ResolvedorJugador* res){
	// Seteo el nivel que eligio el servidor
    res->setNivelActivo(myID, nivel);
}
