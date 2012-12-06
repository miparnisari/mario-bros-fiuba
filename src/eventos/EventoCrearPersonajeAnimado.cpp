#include "EventoCrearPersonajeAnimado.h"
#include "../jugador/ResolvedorJugador.h"

EventoCrearPersonajeAnimado::EventoCrearPersonajeAnimado(VectorChar v): Evento(v) {
	this->hidratar(v);
}

EventoCrearPersonajeAnimado::EventoCrearPersonajeAnimado(Bonus* pers): Evento() {
	myID = pers->getID();
	cout << "ID: " << myID << endl;
	tipo = pers->getNombre();
	cout << "tipo: " << tipo << endl;
    miPos = new Point(pers->getPos()->x, pers->getPos()->y);
}

EventoCrearPersonajeAnimado::~EventoCrearPersonajeAnimado() {
	delete (miPos);
}

VectorChar EventoCrearPersonajeAnimado::serializar(){
	Utilitario utilitario;
	VectorChar v;
	std::string mensaje = EVENTO_CREAR_PERSONAJEANIMADO;
	mensaje += SEP;
	mensaje += tipo;
	mensaje += SEP;
	mensaje += utilitario.convertirAString(myID);
    mensaje += SEP;
    mensaje += utilitario.convertirAString(miPos->x);
    mensaje += SEP;
    mensaje += utilitario.convertirAString(miPos->y);

	utilitario.borrarCaracter(mensaje, SEPFIN);
	// Borro todos los SEPFIN y agrego uno al final
	
	utilitario.agregarCaracteres(v, mensaje);
	return v;
}

void EventoCrearPersonajeAnimado::hidratar(VectorChar v) {
	Utilitario utilitario;
	std::string mensaje = utilitario.convertirVectorAString(v);
	// El Index 0 es el tipo de evento que usaron para instanciar esta clase
	tipo = utilitario.separar(mensaje, SEP, 1);
	myID = utilitario.convertirAEntero(utilitario.separar(mensaje, SEP, 2));
    miPos = new Point(utilitario.convertirAEntero(utilitario.separar(mensaje, SEP, 3)),utilitario.convertirAEntero(utilitario.separar(mensaje, SEP, 4)));
}

void EventoCrearPersonajeAnimado::actuar(ResolvedorJugador* res){
	cout << "Evento crear personaje animado" << endl;
	res->crearPersonajeAnimado(tipo, myID, miPos);
}
