#include "ResolvedorServidor.h"
#include "../server/JugadorRemoto.h"
#include "../jugador/Jugador.h"
#include "../jugador/ControladorJugador.h"
#include "../app/ControladorApp.h"
#include "../eventos/EventoDibujar.h"
const string ResolvedorServidor::TAG = "ResolvedorServidor";
using namespace std;
ResolvedorServidor::ResolvedorServidor(Conexiones* listaCon,ListaEstados* unaLista, Mutex* unMutex): Resolvedor()
{
	listaC = listaCon;
    listaE = unaLista;
	m = unMutex;
}

ResolvedorServidor::~ResolvedorServidor()
{
	
}

Evento* ResolvedorServidor::actualizarEstado(ID cliente, int tecla, bool teclaPresionada){
	// ESTE METODO SOLAMENTE MODIFICA EL ESTADO DEL PROTAGONISTA EN CUESTION
	// SEGUN LA TECLA QUE SE HAYA PRESIONADO, Y SETEA EL BOOLEANO DE MODIFICADO
//cout << "resolver mover protagonista" << std::endl;
	
	IterListaEstados it = listaE->begin();
	bool encontrado = false;
	while ( it != listaE->end() and !encontrado ){
		if ((*it)->getID() == cliente) encontrado = true;
		else ++it;
	}
	
	if (!encontrado) return NULL;
	
//cout << "SE ENCONTRO EL ID" << std::endl;
		
	EstadoJugador* estado = (*it);

	if (teclaPresionada){
//cout << "SE ENCONTRO EL ID" << std::endl;
			estado->teclaPresionada(tecla);
			estado->setModificado(true);
	} else {
			estado->teclaSoltada(tecla);
			estado->setModificado(false);
			estado->setTeclaJustReleased(true);
	 }
	
	return NULL; //eventoRespuesta;
}

Evento* ResolvedorServidor::desconectarJugador(ID cliente){
//	Lock(*(this->m));
	IterConexiones it = listaC->begin();
	bool encontrado = false;
	while( it != listaC->end() and (!encontrado)){
//cout << "cliente: " << cliente << endl;
//cout << "ID cliente (iter): " << (*it)->getID() << endl;
		if ((*it)->getID() == cliente) encontrado = true;
		else ++it;
	}
		
	if (encontrado){
		if ((*it)->corriendo()){
			(*it)->detenerEntrada();
			(*it)->sincronizar();
		}
		delete (*it);
//cout << "encontrado" << endl;
		listaC->erase(it);
		// Borro el par ID - string
		ListaParJugador* lista = ControladorApp::getInstance()->getServidor()->getListaPersonajesOcupados();
		IterParJugador itPJ = lista->begin();
		encontrado = false;
		while ((itPJ != lista->end()) and (!encontrado)){
			if ((*itPJ)->second == cliente) encontrado = true;
			else ++itPJ;
		}
		if (encontrado){
			ControladorApp::getInstance()->getServidor()->getJuego()->removerProtagonistaEnJuego((*itPJ)->second);
			lista->erase(itPJ);
		
		}
		Servidor* server = ControladorApp::getInstance()->getServidor();
		server->disminuirCantJugadores();
//cout << "despues de borrar" << endl;
//cout << "ENVIO EVENTO DESCONECT JUGADOR: " << cliente << std::endl;
		EventoJugadorDesconectado* eventoRespuesta = new EventoJugadorDesconectado(cliente);
		return eventoRespuesta;
	} else return NULL;

}

Evento* ResolvedorServidor::personajeSelect(ID unID, std::string personaje){
//	std::cout << "personaje select" << "\n";
	Servidor* server = ControladorApp::getInstance()->getServidor();
	//Juego* juego = ControladorApp::getInstance()->getServidor()->getJuego();
	ListaParJugador* lista = server->getListaPersonajesOcupados();
	// jr es el jugador remoto del jugador que esta seleccionando el personaje
	JugadorRemoto* jr = NULL; 
	if (!lista) return NULL;
	Conexiones* conexiones = server->getConexiones();
	if (!conexiones){
		return NULL;
	}
	
	for (IterConexiones itConex = conexiones->begin(); itConex != conexiones->end(); ++itConex){
		if ((*itConex)->getID() == unID){
			jr = (*itConex);
			break;
		}
	}
	
	if (!jr){
		return NULL;
	}

	bool ocupado = false;
	if (lista->empty()){
		for (IterParJugador itPers = lista->begin(); itPers != lista->end(); ++itPers){
			if ((*itPers)->first == personaje){
	//			EventoPersonajeOcupado epo();
	//			jr->enviar(epo);
				std::string mensaje = "Personaje ocupado: ";
				mensaje += personaje;
				Logger::info(TAG, mensaje );
//cout << "personaje ocupado" << std::endl;
				ocupado = true;
			//	return NULL;
				// Envio evento de personaje ocupado y termino el metodo
			}
		}
	}
	// Si llego aca es porque el personaje estaba disponible
	// Lo agrego a la lista y la mando
	if (!ocupado){
		std::string mensaje = "Personaje desocupado: ";
		mensaje += personaje;
		Logger::info(TAG, mensaje );
		parJugador* par = new parJugador(personaje, unID);
		lista->push_back(par);
		
		
		server->getJuego()->agregarProtagonista(*par);
	//	std::cout << "AUMENTO CANT JUGADORES" << "\n";
		Protagonista* protagonista = server->getJuego()->getProtagonista(unID);
		server->actualizarPosicionEstado(unID, protagonista);
	//	EventoMoverVista evM(unID, protagonista->getPos(), "quietoder");
	//	jr->enviar(&evM);
		server->aumentarCantJugadores();
		// arranco a correr el timer de si la conex esta viva
//		EventoDibujar evD("esperando", true);
//		jr->enviar(&evD);
		jr->keepAlive();
	}
	
	EventoPersonajesUsados epu(lista);
	// No hago lock porque este metodo se encuentra dentro de uno ya
	jr->enviar(&epu);
	if(!ocupado) return new EventoPersonajeSelect(unID, personaje);
	return NULL;
}

Evento* ResolvedorServidor::keepAlive(ID unID){
	Servidor* server = ControladorApp::getInstance()->getServidor();
	Conexiones* conexiones = server->getConexiones();
	JugadorRemoto* jr = NULL;
	for (IterConexiones itConex = conexiones->begin(); itConex != conexiones->end(); ++itConex){
		if ((*itConex)->getID() == unID){
			jr = (*itConex);
			break;
		}
	}
	
	if (!jr) return NULL;
//cout << "ResolvedorServidor::keepAlive" << std::endl;
	jr->keepAlive();
	return NULL;
}

void ResolvedorServidor::OKServidor(ID unID){
	//printf("ResolvedorServidor OKServidorantes\n");
	Servidor* server = ControladorApp::getInstance()->getServidor();
	server->setWaitSP(false);
	//printf("ResolvedorServidor OKServidorantes\n");
}
