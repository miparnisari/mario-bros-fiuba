#include "EventoActivarVentana.h"


EventoActivarVentana::EventoActivarVentana(VectorChar v){
}

EventoActivarVentana::EventoActivarVentana(std::string unNombreVentana){
	this->nombreVentana = unNombreVentana;
}

void EventoActivarVentana::actuar(){
	ControladorApp::getInstance()->redibujarVentana(this->nombreVentana);
}
