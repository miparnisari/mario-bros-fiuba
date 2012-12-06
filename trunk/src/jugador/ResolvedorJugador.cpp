#include "ResolvedorJugador.h"
#include "ControladorJugador.h"
#include "../app/ControladorApp.h"
#include "../server/JugadorRemoto.h"

const string ResolvedorJugador::TAG = "ResolvedorJugador";

ResolvedorJugador::ResolvedorJugador(): Resolvedor()
{
	
}

ResolvedorJugador::~ResolvedorJugador()
{
}

void ResolvedorJugador::iniciarJuego(ID unID){
	ControladorJugador* cj = ControladorApp::getInstance()->getCJ();
	cj->setID(unID);
}


void ResolvedorJugador::avisarDesconeccionJugador (ID unID){
	ControladorApp::getInstance()->setEstado("Se desconecto jugador de ID: " + unID );
	// Saco a la animacion de la lista
}

void ResolvedorJugador::personajeSelect(ID unID, std::string personaje){
	parJugador par(personaje, unID);
	
	ControladorJugador* cj = ControladorApp::getInstance()->getCJ();
	cj->agregarProtagonista(&par);
}

void ResolvedorJugador::OKServidor(ID unID){
	/*printf("OKServidorantes\n");
	EventoOKServidor* evOK = new EventoOKServidor(unID);
	try {
		ControladorApp::getInstance()->getCJ()->getJugador()->getServidorRemoto()->enviar(evOK);
	} catch (ExceptionConex& e){
		Logger::error(TAG, e.what());
		ControladorApp::getInstance()->setEstado(e.what());
		return;
	}
	printf("OKServidor despues\n");*/
}

void ResolvedorJugador::moverVista(ID unID, Point* posicion, std::string tipo){
	ControladorJugador* cj = ControladorApp::getInstance()->getCJ();
	cj->moverVista(unID, posicion, tipo);
}

void ResolvedorJugador::moverVistasLoop(VectorEventoMV* vectorEventos){
	
	for (IterVectorEventoMV it = vectorEventos->begin() ; it != vectorEventos->end() ; ++it){
		(*it)->actuar(this);
	}	
}

void ResolvedorJugador::setNivelActivo(ID unID, std::string nivel){
	ControladorApp::getInstance()->setNivelActivo(nivel);
}

void ResolvedorJugador::cargarLista(ListaParJugador* unaLista){
	ControladorJugador* cj = ControladorApp::getInstance()->getCJ();
	cj->comenzarJuego(unaLista);
	ControladorApp::getInstance()->desactivarMenu();
	ControladorApp::getInstance()->activarJugador();
	ControladorApp::getInstance()->setEstado("Jugando");
}

void ResolvedorJugador::desocuparVistaPersonaje(ID unID){
	ControladorJugador* cj = ControladorApp::getInstance()->getCJ();
	cj->desocuparVistaPersonaje(unID);
}

void ResolvedorJugador::keepAlive(ID unID){
	Jugador* j = ControladorApp::getInstance()->getCJ()->getJugador();
	if (!j) return;
	ServidorRemoto* sr = j->getServidorRemoto();
	sr->keepAlive();
}

void ResolvedorJugador::moverVistaEnemigo(std::string tipo,ID unID, Point* posicion, std::string tipoMov){
	ControladorJugador* cj = ControladorApp::getInstance()->getCJ();
	cj->moverVistaEnemigo(tipo, unID, posicion, tipoMov);
}

void ResolvedorJugador::crearPersonajeAnimado(std::string tipo, ID myID, Point* miPos) {
	AnimacionAuto* animacion = ControladorApp::getInstance()->getCJ()->cargarPersonajeAnimado(tipo, myID, miPos);
	if (animacion)
		ControladorApp::getInstance()->getCJ()->agregarVista(animacion);
}

void ResolvedorJugador::crearEnemigo(std::string tipo, ID myID, Point* miPos){
	Point* copiaPos = new Point (miPos->x, miPos->y);
	AnimacionProtagonista* animacion;

	animacion = ControladorApp::getInstance()->getCJ()->cargarEnemigo(tipo, myID, copiaPos);
	if (animacion) {
		ControladorApp::getInstance()->getCJ()->agregarVistaEnemigo(tipo, myID, animacion);
	}

}

void ResolvedorJugador::reproducirMusica(std::string tag){
	this->SH.reproducirMusica(tag);
}

void ResolvedorJugador::reproducirSonido(std::string tag){
	this->SH.reproducirSonido(tag);
}

void ResolvedorJugador::cargarMusica(std::string ruta, std::string tag){
	this->SH.cargarMusica(ruta, tag);
}

void ResolvedorJugador::cargarSonido(std::string ruta, std::string tag){
	this->SH.cargarSonido(ruta, tag);
}

void ResolvedorJugador::eliminarVistaEnemigo(std::string unNombre, ID unID){
	ControladorApp::getInstance()->getCJ()->eliminarVistaEnemigo(unNombre, unID);
}

void ResolvedorJugador::dibujarVidas(int cantVidas){
	ControladorApp::getInstance()->getCJ()->modificarVidas(cantVidas);	
}

void ResolvedorJugador::dibujarBonus(std::string elemento, bool activo){
	ControladorApp::getInstance()->getCJ()->setEstadoBonus(elemento, activo);
}

void ResolvedorJugador::terminarJuego(std::string estado){
	ControladorApp::getInstance()->getCJ()->terminarJuego(estado);
}

void ResolvedorJugador::detenerMusica(){
	this->SH.detenerMusica();
}

void ResolvedorJugador::setPosVistaNivel(Point* pos){
	ControladorApp::getInstance()->getCJ()->setPosVistaNivel(pos);
}
