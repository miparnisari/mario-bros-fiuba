#include "JugadorRemoto.h"
const string JugadorRemoto::TAG = "JugadorRemoto";

JugadorRemoto::JugadorRemoto(Socket* cliente, colaEventos* colaBloq, ID id):Hilo() {
	entradaJugadores = cliente;
	colaB = colaBloq;
	myID = id;
	noEstoyEnElJuego = true;
	temporizador = Temporizador();
	temporizador.setIntervalo(TIEMPO_ESPERA_SERVIDOR);
}

JugadorRemoto::~JugadorRemoto() {
//	this->detenerEntrada();
	delete this->entradaJugadores;
}


void JugadorRemoto::correr() {
	while (corriendo()) {
		usleep(20);
		VectorChar datos;
		datos.clear();
		try{
			this->entradaJugadores->recibirDatos(datos);
		}catch (ExceptionConex& e){
			Logger::fatal(TAG, "Error al recibir datos.");
			this->detenerEntrada();
			break;
		}
		
		Evento* evento = FactoryEventos::construir(datos);
		// Encolo eventos
		try{
//printf("RECIBO UN EVENTO EN EL SERVIDOR\n");
			colaB->push(evento);
		} catch (BLQueueException& e) {
			Logger::fatal(TAG, "Error en la cola bloqueante.");
			usleep(1000); //Esto se agrego 
			this->detenerEntrada();
			break;
		}
		
	}
}

bool JugadorRemoto::activo() {
	return entradaJugadores->conectado();
}

void JugadorRemoto::detenerEntrada() {
	this->parar();
//	entradaJugadores->desconectar();
}

bool JugadorRemoto::enviar(Evento* evento) {
//cout << "Jugador remoto enviar" << std::endl;
	try{
		return this->entradaJugadores->enviar(evento->serializar());
	} catch (ExceptionConex& e){
		Logger::error(TAG, e.what());
		this->detenerEntrada();
		return false;
	}
}

ID JugadorRemoto::getID(){
	return myID;
}

void JugadorRemoto::detenerJugador(){
	this->parar();
}

void JugadorRemoto::desconectarJugador(){
	this->entradaJugadores->desconectar();
}

void JugadorRemoto::keepAlive(){
	noEstoyEnElJuego = false;
	this->temporizador.setTiempoInicial();
}

bool JugadorRemoto::isAlive(){
	// Si no paso el tiempo de chequeo entonces la conex se vino abajo
	if (noEstoyEnElJuego) return true;
	return (!this->temporizador.puedeRealizarAccion());
}
