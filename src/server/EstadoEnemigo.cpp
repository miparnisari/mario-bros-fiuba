#include "EstadoEnemigo.h"
#include "../app/ControladorApp.h"
//#include "../jugador/ControladorJugador.h"

EstadoEnemigo::EstadoEnemigo(){
	this->cont = 0;
}

EstadoEnemigo::~EstadoEnemigo() {
	list<st_Enemigo*>::iterator it;
	for (it = enemigos.begin(); it!=enemigos.end(); ++it){
		delete(*it);
	}
	
	enemigos.clear();
}

void EstadoEnemigo::agregarEnemigo(Enemigo* enemigo){
	st_Enemigo* stEnemigo = new st_Enemigo;
	stEnemigo->enemigo = enemigo;
	stEnemigo->PosAnterior.x = enemigo->getPos()->x;
	stEnemigo->PosAnterior.y = enemigo->getPos()->y;
	stEnemigo->UltimaPos = Point(500, 500);
	this->enemigos.push_back(stEnemigo);
}

void EstadoEnemigo::eliminarEnemigo(Enemigo* enemigo){
	list<st_Enemigo*>::iterator it = enemigos.begin();
	for (it = enemigos.begin(); it != enemigos.end(); ++it) {
		if((*it)->enemigo == enemigo){
			delete(*it);
			enemigos.erase(it);
			return;
		}
	}
}


void EstadoEnemigo::actualizarPosicion(){
	
	if (cont == 50){
		for (list<st_Enemigo*>::iterator it = enemigos.begin(); it != enemigos.end(); ++it) {

			Point* p = (*it)->enemigo->getMovimiento()->getPos();

			if(!(ControladorApp::getInstance()->getServidor()->getJuego()->verificarPiso((*it)->enemigo->getAlto(), *((*it)->enemigo->getMovimiento()->getPos())))){
				(*it)->enemigo->getPos()->y = (*it)->PosAnterior.y;
			}

			//int detener = ControladorApp::getInstance()->getServidor()->getJuego()->detectarColision((*it)->enemigo, (*it)->PosAnterior);
			int detener = ControladorApp::getInstance()->getServidor()->getJuego()->detectarColisionEnemigo((*it)->enemigo, (*it)->PosAnterior);

			if(!detener) (*it)->enemigo->getMovimiento()->setRozamiento(0);

			if(!(ControladorApp::getInstance()->getServidor()->getJuego()->verificarPiso((*it)->enemigo->getAlto(), *p))){
				(*it)->enemigo->getPos()->y = (*it)->PosAnterior.y;
			}

			(*it)->PosAnterior.x = p->x;
			(*it)->PosAnterior.y = p->y;

			if ((p->distanceFrom((*it)->UltimaPos) > 2)){
				(*it)->UltimaPos.x = p->x;
				(*it)->UltimaPos.y = p->y;
				//std::string tipoMov = (*it)->enemigo->getTipoMovimiento();
				//Envio evento
				EventoMoverEnemigo ev((*it)->enemigo);
				ControladorApp::getInstance()->getServidor()->enviarEventoJugadores(&ev);

			}
		}

		cont = 0;
		
	} else cont++;
}
