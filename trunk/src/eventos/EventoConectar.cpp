#include "EventoConectar.h"

EventoConectar::EventoConectar(VectorChar v){
}

EventoConectar::EventoConectar(){
}

void EventoConectar::actuar(){
	bool singlePlayer = false;
	ControladorApp::getInstance()->conectarJugador(singlePlayer);
}
