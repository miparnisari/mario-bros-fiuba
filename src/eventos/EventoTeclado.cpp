#include "EventoTeclado.h"

EventoTeclado::EventoTeclado(VectorChar v): Evento(v) {
	this->hidratar(v);
}

EventoTeclado::EventoTeclado(ID unID, int unaTecla, bool unPres): Evento() {
	myID = unID;
	teclaPres = unaTecla;
	presionada = unPres;
}

VectorChar EventoTeclado::serializar(){
	Utilitario utilitario;
	VectorChar v;
	std::string mensaje = EVENTO_TECLADO;
	mensaje += SEP;
	mensaje += utilitario.convertirAString(myID);
	mensaje += SEP;
	mensaje += utilitario.convertirAString(teclaPres);
	mensaje += SEP;
	mensaje += utilitario.convertirAString(presionada);
	utilitario.borrarCaracter(mensaje, SEPFIN);
	// Borro todos los SEPFIN y agrego uno al final
	
	utilitario.agregarCaracteres(v, mensaje);
	return v;
}

void EventoTeclado::hidratar(VectorChar v) {
	Utilitario utilitario;
	std::string mensaje = utilitario.convertirVectorAString(v);
	// El Index 0 es el tipo de evento que usaron para instanciar esta clase
	myID = utilitario.convertirAEntero(utilitario.separar(mensaje, SEP, 1));
	teclaPres = utilitario.convertirAEntero(utilitario.separar(mensaje, SEP, 2));
	presionada = utilitario.convertirAEntero(utilitario.separar(mensaje, SEP, 3));
}

Evento* EventoTeclado::actuar(ResolvedorServidor* res){
	//res.moverProtagonista(client, teclaPres, presionada);
	//return NULL; //ACA SE TIENE QUE DEVOLVER ALGO DEL TIPO eventoMoverVista
	Evento* eventoResp = res->actualizarEstado(myID, teclaPres,presionada);
	return eventoResp;
}
