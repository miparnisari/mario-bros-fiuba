#include "EventoElegirPersonaje.h"

EventoElegirPersonaje::EventoElegirPersonaje(VectorChar v){
}

EventoElegirPersonaje::EventoElegirPersonaje(){
}

void EventoElegirPersonaje::actuar(){
	ControladorApp::getInstance()->clienteEnviarPersonaje();
}
