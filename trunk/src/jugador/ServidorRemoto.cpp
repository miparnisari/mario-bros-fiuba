#include "ServidorRemoto.h"
#include "../app/ControladorApp.h"
#include "../jugador/ControladorJugador.h"
const string ServidorRemoto::TAG = "ServidorRemoto";
//port es el Puerto por el cual escuchará conexiones de los servers.
ServidorRemoto::ServidorRemoto(Socket* server, ResolvedorJugador* unRes):Hilo() {
	entradaServidor = server;
	resolvedor = unRes;
	temporizador = Temporizador();
	temporizador.setIntervalo(TIEMPO_ESPERA_SERVIDOR);
}

ServidorRemoto::~ServidorRemoto() {
	this->detenerEntrada();
	delete this->entradaServidor;
//cout << "entrada servidor" << std::endl;
	this->entradaServidor = NULL;
}

void ServidorRemoto::correr() {
	
	ControladorJugador* cj = ControladorApp::getInstance()->getCJ();
	while (corriendo()) {
		usleep(10);
		VectorChar datos;
		datos.clear();
		this->temporizador.setTiempoInicial();
		try{
			this->entradaServidor->recibirDatos(datos);
		}catch (ExceptionConex& ){
			Logger::error(TAG, "Fallo al recibir datos del Servidor Remoto.");
			if (cj->JugadorEstaConectado()) {
				ControladorApp::getInstance()->setEstado("Fallo la conexion con el servidor.");
				ControladorApp::getInstance()->getCJ()->desconectarASAP(true);
			//	ControladorApp::getInstance()->salidaPorDesconexion();
				break;
			}
		}
		
		if (not datos.empty()){
		
			Evento* evento = FactoryEventos::construir(datos);
			if (evento){
				evento->actuar(resolvedor);
				delete evento;
			} else{
				Logger::error(TAG, "Factory eventos no pudo usar el string recibido en el socket para crear un evento.");
			}
		}
	}
}

bool ServidorRemoto::enviar(Evento* ev){//std::string mensaje) {
	VectorChar v = ev->serializar();
	delete ev;
	ControladorJugador* cj = ControladorApp::getInstance()->getCJ();
//cout << "DSP DE SERIALIZAR, ANTES DE ENVIAR" << std::endl;
//cout << "mensaje serializado: " << mensaje << std::endl;
	try{
//printf("ENVIO EVENTO JUGADOR->SERVIDOR\n");
		return this->entradaServidor->enviar(v);
	} catch (ExceptionConex& e){
		if (cj->JugadorEstaConectado()) {
//printf ("fallo el socket enviar\n");
			ControladorApp::getInstance()->setEstado("Fallo la conexion con el servidor.");
//			this->entradaServidor->setTimeout(SEGS_TIMEOUT,0);
//			if(this->entradaServidor->timeoutCumplido()){
//cout << "TIMEOUT CUMPLIDO" << std::endl;
			//ControladorApp::getInstance()->salidaPorDesconexion();
			ControladorApp::getInstance()->getCJ()->desconectarASAP(true);
		//Logger::error(T e.what());
		//this->detenerEntrada();
			return false;	
		}
	}	
}

bool ServidorRemoto::activo() {
	return entradaServidor->conectado();
}

void ServidorRemoto::detenerEntrada() {
	this->parar();
	entradaServidor->desconectar();
}


void ServidorRemoto::keepAlive(){
//	printf("SERVIDOR REMOTO ALIVE SIGNAL\n");
	this->temporizador.setTiempoInicial();
}

bool ServidorRemoto::isAlive(){
	return (!this->temporizador.puedeRealizarAccion());
}
