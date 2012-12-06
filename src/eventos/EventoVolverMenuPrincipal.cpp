#include "EventoVolverMenuPrincipal.h"
#include "../app/ControladorApp.h"

EventoVolverMenuPrincipal::EventoVolverMenuPrincipal(){}

EventoVolverMenuPrincipal::~EventoVolverMenuPrincipal(){}

void EventoVolverMenuPrincipal::actuar(){
	ControladorApp::getInstance() -> volverAlMenuPrincipal();
	ControladorApp::getInstance() -> setEstado("Se ha desconectado del servidor.");
	}

