#include "EventoSalirModoSinglePlayer.h"


EventoSalirModoSinglePlayer::EventoSalirModoSinglePlayer(VectorChar v){
}

EventoSalirModoSinglePlayer::EventoSalirModoSinglePlayer(std::string unNombreVentana){
	this->nombreVentana = unNombreVentana;
}

void EventoSalirModoSinglePlayer::actuar(){
	//FIXME
	if (ControladorApp::getInstance()->getServidor()) {
		ControladorApp::getInstance()->getServidor()->detener();
		ControladorApp::getInstance()->destruirServidor();
	}
	if (ControladorApp::getInstance()->getCJ()->JugadorEstaConectado()) {
		ControladorApp::getInstance()->volverAlMenuPrincipal();
	}	
	ControladorApp::getInstance()->redibujarVentana(this->nombreVentana);
	ControladorApp::getInstance()->singlePlayerSelect = false;
}
