#include "EventoTerminarServidor.h"

EventoTerminarServidor::EventoTerminarServidor(VectorChar v){
}

EventoTerminarServidor::EventoTerminarServidor(){
}

void EventoTerminarServidor::actuar(){
	ControladorApp::getInstance()->destruirServidor();
}
