#include "EventoVistasLoop.h"
#include "../server/ResolvedorServidor.h"

EventoVistasLoop::EventoVistasLoop(VectorChar v) : Evento(v) {
	vectorEventos = new VectorEventoMV;
	this->hidratar(v);
}

EventoVistasLoop::EventoVistasLoop() : Evento() {
	vectorEventos = new VectorEventoMV;
}

void EventoVistasLoop::borrarEventos() {
	VectorEventoMV::iterator it;
	for ( it=vectorEventos->begin() ; it < vectorEventos->end(); ++it ) {
		delete(*it);
	}
	vectorEventos->clear();
	//delete vectorEventos;
}

EventoVistasLoop::~EventoVistasLoop(){
	borrarEventos();
}

void EventoVistasLoop::agregarEventoVista(EventoMoverVista* evento){
	//Agrega un eventoMoverVista al vector de eventos
	vectorEventos->push_back(evento);
}

VectorChar EventoVistasLoop::serializar(){
	VectorChar v;
	VectorChar aux;

	Utilitario utilitario;
	std::string mensaje = EVENTO_VISTASLOOP;
	mensaje += SEP;
	utilitario.borrarCaracter(mensaje, SEPFIN);
	// Borro todos los SEPFIN y agrego uno al final

	utilitario.agregarCaracteres(v, mensaje);
	
	//Recorro el vector de eventos
	for (IterVectorEventoMV it = vectorEventos->begin() ; it != vectorEventos->end(); ++it){
		aux.clear();
		aux = (*it)->serializar();
		//Recorro el evento y lo agrego al vector que devuelvo
		for (IterVectorChar itChar = aux.begin() ; itChar != aux.end(); ++itChar){
			v.push_back(*itChar);
		}

		//Agrego el caracter de separacion entre eventos
		v.push_back(SEP_EVENTO);
	}

	return v;
}

void EventoVistasLoop::hidratar(VectorChar v){
	VectorChar aux;

	IterVectorChar it = v.begin();
	while ((*it) != SEP) {
		++it;
	}
	
	
	++it; //Me paro en el primer char util
	
	
	//Recorro el vector de char para reconstruir el evento
	for (it ; it != v.end() ; ++it){

		if ((*it) == SEP_EVENTO){
			EventoMoverVista* evento = new EventoMoverVista(aux);
			this->agregarEventoVista(evento);
			aux.clear();
			//delete (evento);

		} else {
			aux.push_back(*it);
		}

	}
}

void EventoVistasLoop::actuar(ResolvedorJugador* res){
	res->moverVistasLoop(vectorEventos); 
	borrarEventos();
}
