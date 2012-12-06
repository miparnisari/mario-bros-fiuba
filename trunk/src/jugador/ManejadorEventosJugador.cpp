#include "ManejadorEventosJugador.h"
#include "Jugador.h"

const string ManejadorEventosJugador::TAG = "ManejadorEventosJugador";

ManejadorEventosJugador::ManejadorEventosJugador(ServidorRemoto* servidorRem)
{
//cout << "CONSTRUC CON SERVREM != NULL" << endl;
	servidor = servidorRem;
}

ManejadorEventosJugador::~ManejadorEventosJugador() {}

void ManejadorEventosJugador::manejarEventos() {
	
	ControladorJugador* cj = ControladorApp::getInstance()->getCJ();
	
	if (!cj) return;

	SDL_Event event;
	// Mientras haya eventos para manejar
	try {
		while ( SDL_PollEvent( &event ) )
		{
			
			if( event.type == SDL_KEYUP ){
				EventoTeclado* eventoTec = new EventoTeclado(cj->getID(), event.key.keysym.sym, false);
				servidor->enviar(eventoTec);
				//teclasPresionadas[event.key.keysym.sym] = false;
			}
			
			
			if( event.type == SDL_KEYDOWN ){
				EventoTeclado* eventoTec = new EventoTeclado(cj->getID(), event.key.keysym.sym, true);
					servidor->enviar(eventoTec);
			}
			
			if( event.type == SDL_QUIT) {
				cj->setEstadoConexJugador(false);
				if (servidor) {
					EventoSalir* eventoSal = new EventoSalir(cj->getID());
					servidor->enviar(eventoSal);
				}
				cj->desconectarASAP(true);
		/*		
				cj->setIDRecibido(false);
				cj->setRespuesta(false);
				cj->desactivar();
				if (cj->getJugador()) cj->getJugador()->detener();
				cj->limpiarListas();
				if (cj->getJugador()) delete (cj->getJugador());
				cj->setJugador(NULL) ; */
				ControladorApp::getInstance()->activarMenu();
				ControladorApp::getInstance()->setEstado("Desconexion del juego.");
				
				//system("rm -rf tmp/");
			}
		}

	}catch (ExceptionConex& e){
		Logger::error(TAG, e.what());
		ControladorJugador* cj = ControladorApp::getInstance()->getCJ();
		
		cj->desactivar();
		if (cj->getJugador()) {
			cj->getJugador()->detener();
			delete (cj->getJugador());
		}
		cj->setJugador(NULL) ;
		ControladorApp::getInstance()->activarMenu();
		return;
	}
}

