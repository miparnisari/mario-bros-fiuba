#include "EventoCrearServidorSinglePlayer.h"


EventoCrearServidorSinglePlayer::EventoCrearServidorSinglePlayer(VectorChar v){
}

EventoCrearServidorSinglePlayer::EventoCrearServidorSinglePlayer(){
}

void EventoCrearServidorSinglePlayer::actuar(){
	if (ControladorApp::getInstance()->getServidor() != NULL) {
		ControladorApp::getInstance()->getServidor()->detener();
		ControladorApp::getInstance()->destruirServidor();
	}
	
	bool singlePlayer = true;
	ControladorApp::getInstance()->crearServidor(singlePlayer);
	ControladorApp::getInstance()->conectarJugador(singlePlayer);
}
