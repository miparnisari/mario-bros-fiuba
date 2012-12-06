#include "EventoCrearServidor.h"


EventoCrearServidor::EventoCrearServidor(VectorChar v){
}

EventoCrearServidor::EventoCrearServidor(){
}

void EventoCrearServidor::actuar(){
	bool singlePlayer = false;
	ControladorApp::getInstance()->crearServidor(singlePlayer);
}
