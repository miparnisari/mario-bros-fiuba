#include "Jugador.h"
const string Jugador::TAG = "Jugador";

Jugador::Jugador(std::string unPuerto, std::string host)
{
	Utilitario u;
	try{
		sock = new Socket((Puerto)u.convertirAEntero(unPuerto));
		myID = 0;
		sock->conectar(host);
	} catch (ExceptionConex& e){
		Logger::error(TAG, e.what());
		throw (e);
	}
	
	if (!sock){
		throw (ExceptionConex("No se pudo conectar: Host: " + host + "Puerto" + unPuerto));
	}
	resolvedor = new ResolvedorJugador();
	servidor = new ServidorRemoto(sock, resolvedor);
	activo = true;
	try{
		servidor->iniciar();
	} catch (ExceptionConex& e){
		Logger::error(TAG, "Fallo en el servidor remoto.");
		throw e;
	}
}

Jugador::Jugador()
{
	sock = new Socket((Puerto)PUERTO);
	myID = 0;
	sock->conectar("localhost");
	resolvedor = new ResolvedorJugador();
	servidor = new ServidorRemoto(sock, resolvedor);
	activo = true;
	servidor->iniciar();
}

Jugador::~Jugador()
{
	if (resolvedor){
		delete resolvedor;
		resolvedor = NULL;
	}
	
	if (servidor){ 
		delete servidor;
		servidor = NULL;
	}
}

bool Jugador::estaActivo(){
	return activo;
}

bool Jugador::setActivo(bool estado){
	activo = estado;
}

void Jugador::setID(ID unID){
	myID = unID;
}

ResolvedorJugador* Jugador::getResolvedor() {
	return resolvedor;
}

ID Jugador::getID(){
	return myID;
}

bool Jugador::socketEstaConectado(){
	return this->sock->conectado();
}

void Jugador::detener(){
	// detengo la entrada y la sincronizo
	try{
		if (servidor){
			servidor->detenerEntrada();
			servidor->sincronizar();
		}
	} catch (ExceptionConex& e){
		Logger::info(TAG, "El socket ya se habia cerrado");
	}
}

ServidorRemoto* Jugador::getServidorRemoto(){
	return servidor;
}
