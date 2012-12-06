#include "Servidor.h"
#include "HiloAceptarJug.h"
#include "HiloEnviarJug.h"
#include "../app/ControladorApp.h"
#include "../jugador/ControladorJugador.h"
#define MANTENIMIENTO 1
using namespace std;

const string Servidor::TAG = "Servidor";

Servidor::Servidor(string unPuerto, string nivel, string maxJugadores, std::string unModo)
{
	if (! validarPuerto(unPuerto))
		throw ExceptionPuertoInvalido();
		
	try {
		Utilitario u;
		modo = unModo;
		waitSP = true;
		juegoFinalizado = false;
		colaBloq = new colaEventos;
		// Creo listas: de jugadores remotos, estados y eventos
		conexiones = new Conexiones;
		listaE = new ListaEstados;
		listaEv = new ListaEventos;
		listaPersonajesOcupados = new ListaParJugador;
		estadoEnemigos = new EstadoEnemigo();
		res = new ResolvedorServidor(conexiones, listaE, &m);
		// usa listas es estados y JR para agregar nuevas conexiones
		string archivoDep = nivel;
		//archivoDep += DEPENDENCIAS;
		hiloAceptar = new HiloAceptarJug(u.convertirAEntero(unPuerto), colaBloq, conexiones, listaE, &m, archivoDep);
		// si cambia algun estado genera un evento y lo agrega a la lista
//		hiloResolverMovimientos = new HiloResolverMovimientos(listaE, listaEv, &m);
		// si la lista tiene eventos loas envia a todos los jugadores
	//	hiloEnviarJug = new HiloEnviarJug(conexiones, listaEv, &m);
		eventH = new EventHandler;
		tempServer = Temporizador();
		tempEspera = Temporizador();
		tempEspera.setTiempoInicial();
		tempEspera.setIntervalo(MANTENIMIENTO);
		tempServer.setTiempoInicial();
		tempServer.setIntervalo(TIEMPO_ALIVE_SERVER);
		
		//Armo la ruta del archivo de configuracion del nivel correspondiente
		//string rutaArchivo = ControladorMenu::getInstance()->getMenu()->getData("Nivel") + ".yaml";
		//LoaderServidor* loader = new LoaderServidor(rutaArchivo);
		string archivo = "niveles/" + nivel + EXT_YAML;

		loaderServidor = new LoaderServidor(archivo);
		if (loaderServidor->parserEsNull()) {
			delete colaBloq; delete conexiones; delete listaE; delete listaEv;
			delete listaPersonajesOcupados; delete res; delete hiloAceptar;
			delete eventH;
			throw (ExceptionIO(archivo));
		}
		this->juego = new Juego(loaderServidor->cargarNivel());
		this->maxJugadores = atoi(maxJugadores.c_str());
		this->cantJugadores = 0;
	
	} catch(ExceptionConex& e){
		ControladorApp::getInstance()->setEstado(e.what());
		throw(e);
	}
}

Servidor::~Servidor()
{
	for (IterConexiones it = conexiones->begin(); it != conexiones->end(); ++it) 
	//	delete (*it);
		
	for (IterListaEstados itE = listaE->begin(); itE != listaE->end(); ++itE) 
		delete (*itE);
		
	for (IterParJugador itPJ = listaPersonajesOcupados->begin(); itPJ != listaPersonajesOcupados->end(); ++itPJ) 
		delete (*itPJ);
		
	delete conexiones;
    delete listaE;
	delete colaBloq;
	delete res;
	delete hiloAceptar;
    delete listaEv;
    delete eventH;
    delete listaPersonajesOcupados;
	delete juego;
	delete loaderServidor;
	delete estadoEnemigos;
}

void Servidor::detener(){
	m.lock();
	// detengo la entrada y la sincronizo
	hiloAceptar->detenerEntrada();
	hiloAceptar->sincronizar();

	for (IterConexiones it = conexiones->begin(); it != conexiones->end(); ++it) 
		(*it)->detenerJugador();
	/*
	// espero a que se resuelvan las ultimas consultas
	while (nact || ncons)
		m.wait();*/
	// desconecto los clientes y los sincronizo
	for (IterConexiones it = conexiones->begin(); it != conexiones->end(); ++it){
		(*it)->desconectarJugador();
		(*it)->sincronizar();
	}

	colaBloq->close();
	m.unlock();
}

bool Servidor::hayCantidadMin(){
	return (cantJugadores == this->maxJugadores);
}

void Servidor::correr(){
	Utilitario u; 
	hiloAceptar->iniciar();
	ID jugadorCaido = 0;
	Evento* evJugadorCaido = NULL;
//	printf("MODO: \n", modo.c_str());
	if (modo == "MP"){
		while(!hayCantidadMin() and this->corriendo()){
			usleep(200);
		//	std::cout << "CANT JUGADORES: "<< cantJugadores << "\n";
		//	ControladorApp::getInstance()->setEstado("Esperando jugadores");
			try{
				this->resolverEventos();
			} catch(BLQueueException& e){
				//std::cout << "BLQueueException" << "\n";
				this->parar();
			}
			
			m.lock();
			this->mantenerVivo();
			m.unlock();

			if (!hayCantidadMin()){
				EventoDibujar evD(ESPERANDO, true);
				m.lock();
				this->enviarEventoJugadores(&evD);
				m.unlock();
			}
		}
	} else if( modo == "SP"){
		while ((waitSP == true) and this->corriendo()){
			usleep(200);
			try{
				this->resolverEventos();
			} catch(BLQueueException& e){
				//std::cout << "BLQueueException" << "\n";
				this->parar();
			}
			
			m.lock();
			this->mantenerVivo();
			m.unlock();
		}
		
		//sleep(3);
	}
	EventoSonido evS("S","HereWeGo");
	m.lock();
	this->enviarEventoJugadores(&evS);
	m.unlock();
//	sleep(5);
	m.lock();
	if (modo == "MP"){
		EventoDibujar evD(ESPERANDO, false);
		this->enviarEventoJugadores(&evD);
		
	}
	m.unlock();

	EventoSonido evM("M","DBZ");
	m.lock();
	this->enviarEventoJugadores(&evM);
	m.unlock();
	
	while ( this->corriendo()){

		usleep(5);

		try {
			
			this->resolverEventos();
			m.lock();
			this->checkConexPerdidas(&jugadorCaido);
			m.unlock();
			// Si encontre algun jugador cayido en este ciclo
			// le aviso a todos que lo borren y llamo al metodo del resolvedor
			m.lock();
			if (jugadorCaido != 0){
				evJugadorCaido = res->desconectarJugador(jugadorCaido);
				for (IterConexiones it = conexiones->begin(); it != conexiones->end(); ++it)
					(*it)->enviar(evJugadorCaido);
				jugadorCaido = 0;
			}
			m.unlock();
			
			m.lock();
			this->mantenerVivo();
			m.unlock();

			this->resolverMovimientos();
			this->estadoEnemigos->actualizarPosicion();
			this->juego->simular();
			// TareasMantenimiento borra inactivos periodicamente
			this->tareasMantenimiento();

			m.lock();
			if (juegoFinalizado){
				this->informarGanador();
				m.unlock();
			} else m.unlock();
			
	//	this->resolverColisiones();
		 }catch (BLQueueException& e) {
			//std::cout << "BLQueueException" << "\n";
			Logger::fatal(TAG, "Error en la cola bloqueante.");
			this->parar();
			break;
		}

	}
	parar();

}

void Servidor::resolverMovimientos(){

	Protagonista* unProtagonista = NULL;

	// Recorro la lista de estados y actualizo
	EventoVistasLoop* evento = new EventoVistasLoop();
	EventoMoverVista* eventoMV = NULL;
	bool cambiosVista = false;

	m.lock();
	for (IterListaEstados it = listaE->begin(); it != listaE->end(); ++it){
		ID unID = (*it)->getID();

		// Aca debo buscar al personaje dentro del modelo
		if (this->juego) {
			unProtagonista = this->juego->getProtagonista(unID);
			string tipo = "";
			if (unProtagonista){
				if ((*it)->actualizarPosicion(unProtagonista->getMovimiento(), tipo)){
					eventoMV = new EventoMoverVista(unID, (*it)->getPos(), tipo);
					evento->agregarEventoVista(eventoMV);
					cambiosVista = true;
				}
			}
		}
	}

	m.unlock();
	if (cambiosVista){
		m.lock();
		for (IterConexiones itConex = conexiones->begin(); itConex != conexiones->end(); ++itConex){
			ID unID = (*itConex)->getID();
			unProtagonista = this->juego->getProtagonista(unID);
			if (unProtagonista){
				(*itConex)->enviar(evento);
			}
		}
		m.unlock();
		cambiosVista = false;
	}

	if (evento){
		delete evento;
		evento = NULL;
	}

}

void Servidor::setJuego(Juego* unJuego){
	this->juego = unJuego;
}

Juego* Servidor::getJuego(){
	return this->juego;
}

Conexiones* Servidor::getConexiones(){
	return conexiones;
}

ListaParJugador* Servidor::getListaPersonajesOcupados(){
	return  listaPersonajesOcupados;
}

Mutex* Servidor::getMutex(){
	&m;
}

void Servidor::agregarEnemigo(Enemigo* enemigo){
	this->estadoEnemigos->agregarEnemigo(enemigo);
}

bool Servidor::validarPuerto(string unPuerto) {
	Utilitario u;
	return u.esPuertoValido(unPuerto);
}

int Servidor::getMaxJugadores() {
	return this -> maxJugadores;
}

void Servidor::resolverColisiones(){
	this->juego->resolverColisiones();
}

void Servidor::enviarEventoJugadores(Evento* ev){
	//m.lock();
	for (IterConexiones it = conexiones->begin(); it != conexiones->end(); ++it){
		(*it)->enviar(ev);
	}
	//m.unlock();	
}

void Servidor::enviarEventoJugador(Evento* ev, ID unID){
//	std::cout << "enviarEventoJugador" << std::endl;
	IterConexiones it = conexiones->begin();
	while(it != conexiones->end()){
		if ((*it)->getID() == unID){
			(*it)->enviar(ev);
			break;
		} else 
			++it;
	}
}

// Le envia un evento a todos los jugadores menos al del ID indicado
void Servidor::enviarEventoRestoJugador(Evento* ev, ID unID){
	for (IterConexiones it = conexiones->begin();it != conexiones->end() ; ++it){
		if ((*it)->getID() != unID)
			(*it)->enviar(ev);
	}
}

void Servidor::disminuirCantJugadores(){
	cantJugadores--;	
}

void Servidor::aumentarCantJugadores(){
	m.lock();	
//	std::cout << "cantJugadores++" << "\n";
	cantJugadores++;
	m.unlock();	
}

void Servidor::mantenerVivo(){
//	std::cout << "mantenerVivo" << std::endl;
	if (tempServer.puedeRealizarAccion()){
//		std::cout << "ENVIO KEEP ALIVE SERVIDOR" << std::endl;
		EventoKeepAlive evKA = EventoKeepAlive(0);	
		// Mando evento keepAlive del server a todos los jugadores
		for (IterConexiones it = conexiones->begin(); it != conexiones->end(); ++it){
				(*it)->enviar(&evKA);
		}
		tempServer.setTiempoInicial();
	}	
}

void Servidor::tareasMantenimiento(){
// Cada X segundos limpia los enemigos muertos, envia evento quitar cartel
	if (tempEspera.puedeRealizarAccion()){
		this->juego->eliminarEnemigosInactivos();
	/*	EventoDibujar evD(ESPERANDO, false);
		m.lock();
		this->enviarEventoJugadores(&evD);
		m.unlock();*/
		tempEspera.setTiempoInicial();
	}
}

void Servidor::resolverEventos(){
//	std::cout << "RESOLVER EVENTOS" << std::endl;
	Evento* evento = colaBloq->pop();
	while (evento){
		if (evento){			
			Evento* eventoRespuesta = evento->actuar(res);
			if (eventoRespuesta){
				Logger::info(TAG, "Envio evento respuesta");
				m.lock();
				for (IterConexiones it = conexiones->begin(); it != conexiones->end(); ++it){
					(*it)->enviar(eventoRespuesta);
				}
				m.unlock();
				delete eventoRespuesta;
			}
			
			delete evento;
			evento = colaBloq->pop();
		}
	}
}

void Servidor::checkConexPerdidas(ID* jugadorCaido){
//	std::cout << "checkConexPerdidas" << std::endl;
	IterConexiones it = conexiones->begin();
	Utilitario u;
	while (it != conexiones->end() and (*jugadorCaido) == 0){
	if (!(*it)->isAlive()){
		std::string m;
		m = "Se ha perdido la conexion con ID: ";
		*jugadorCaido = (*it)->getID();
		m += u.convertirAString((*it)->getID());
		std::cout << m << std::endl;
		ControladorApp::getInstance()->setEstado(m);
		//conexiones->erase(it++);
		
	} else 
		++it;
	}
}

int Servidor::getDimensionEnemigo(std::string tipo, int* ancho, int* alto){
	if (this->loaderServidor == NULL) {
		return 0;
	}
	return this->loaderServidor->getDimensionEnemigo(tipo, ancho, alto);
}

void Servidor::eliminarEnemigo(Enemigo* enemigo){
	this->estadoEnemigos->eliminarEnemigo(enemigo);	
}

void Servidor::informarGanador(){
	if ((modo == "MP") and (this->getJuego()->getNivel()->getProtagonistasVivos() == 1 ) and (cantJugadores > 1)){
		// Queda un solo jugador vivo 
		EventoSonido evSG("S","ganar");
		EventoGameOver evG("ganar");
		this->enviarEventoJugadores(&evSG);
		this->enviarEventoJugadores(&evG);
	}
	juegoFinalizado = false;
}

void Servidor::setFinalizo(bool estado){
//	m.lock();
	juegoFinalizado = estado;
//	m.unlock();
}

bool Servidor::getFinalizo(){
	return juegoFinalizado;
}

void Servidor::actualizarPosicionEstado(ID unID,Protagonista* protagonista){
	bool encontrado = false;
	for (IterListaEstados itE = listaE->begin(); itE != listaE->end() and !encontrado; ++itE){
		//std::cout << "for" << "\n";
		if ((*itE)->getID() == unID){
			std::cout << "Actualizo estado :" << (*(protagonista->getPos())) << "\n";
			(*itE)->cambiarPosicion(protagonista->getPos()->x, protagonista->getPos()->y);
			encontrado = true;
		}
	}
}

void Servidor::setWaitSP(bool estado){
//	m.lock();
	//std::cout << "waitSP = estado;" << "\n";
	waitSP = estado;
//	m.unlock();
}
