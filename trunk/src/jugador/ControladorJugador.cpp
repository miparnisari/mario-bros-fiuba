#include "ControladorJugador.h"
#include "ManejadorEventosJugador.h"
#include "../vista/MenuPrincipal.h"
#include "../app/ControladorApp.h"
#include "../vista/VistaNivel.h"

const string ControladorJugador::TAG = "ControladorJugador";

using namespace std;

ControladorJugador::ControladorJugador()
{
	this->myID = ID_INVALIDO;
	this->loader = NULL;
	this->activo = false;
	this->jugadorConectado = true;
	this->ID_Recibido = false;
	this->respuesta = false;
	this->jugador = NULL;
	this->manejador = NULL;
	this->vistaVidas = NULL;
	this->desconectar = false;
}

ControladorJugador::~ControladorJugador() {
	delete this->manejador;
	delete this->loader;
}

bool fnCompar(Imagen* first, Imagen* second) {
	if (first->getPrioridad() < second->getPrioridad()) return true;
	else return false;
}

void ControladorJugador::agregarVista(Imagen* image) {
	AnimacionesEnJuego.push_back(image);
	AnimacionesEnJuego.sort(fnCompar);
}

void ControladorJugador::agregarVistaGeneral(Imagen* image) {
	listaAnimaciones.push_back(image);
}

//TODO no hace nada??
void ControladorJugador::setVistaPrincipal(Imagen* vistaPrincipal){
	
}

bool ControladorJugador::refrescar(Pantalla* p){
	if (!p) return false;
	m.lock();
	bool r = p->refrescar(AnimacionesEnJuego, vistasEnemigos, vistaVidas, vistasBonus);
	m.unlock();
	return r;
}

void ControladorJugador::moverVista(ID unID, Point* posicion, string tipo){
	m.lock();
	bool encontrado = false;
	IterlistaVistas it = AnimacionesEnJuego.begin();
	while(!encontrado and (it) != AnimacionesEnJuego.end()){
		// Poner id invalido a las cosas que no corresponden a un jugador
		if ((*it)->getID() == unID) encontrado = true;
		else ++it;
	}
	
	if (!encontrado) return;
	// Si tiene lo encontre es porque es una animacion protagonista -> cast
	((AnimacionProtagonista*)(*it))->setEstadoAnimacion(tipo);
	(*it)->setPos(posicion);
	// setPos se copia los valores de la nueva pos, no asigna puntero
	m.unlock();
}

bool ControladorJugador::estaActivo(){
	return (this->activo);
}

void ControladorJugador::activar(){
	activo = true;
}

void ControladorJugador::desactivar(){
	activo = false;
	if (jugador) 
		this->jugador->setActivo(false);
}

void ControladorJugador::setIDRecibido (bool estado) {
	ID_Recibido  = estado;
}

void ControladorJugador::setID(ID unID){
	myID = unID;
	setIDRecibido(true);
	this->jugador->setID(unID);
}

void ControladorJugador::setRespuesta(bool estado){
	respuesta = estado;
}

ID ControladorJugador::getID(){
	return myID;
}

void ControladorJugador::manejarEventos(){
	this->manejador->manejarEventos();
}

void ControladorJugador::enviarPersonaje(ID id, string personajeElegido){
	if (this->jugador) {
		EventoPersonajeSelect* ev = new EventoPersonajeSelect(id, personajeElegido);
		
		try {
			this->jugador->getServidorRemoto()->enviar(ev);
		} catch (ExceptionConex& e){
			Logger::error(TAG, e.what());
			ControladorApp::getInstance()->setEstado(e.what());
			return;
		}
		Utilitario u;
		while (!respuesta) {
			usleep(1000);
		}
		if (!respuesta) return;
		respuesta = false;
	}
}

void ControladorJugador::comenzarJuego(ListaParJugador* jugadores) {
	
	string nivel = ControladorApp::getInstance()->getNivelActivo();
	string path;
	path.assign("./"); path.append(DIR); path.append("/niveles/"); path.append(nivel); path.append(EXT_YAML);
	try {
		cargarJuego(path,"defecto.yaml",*jugadores);
	} catch (exception& e) {
		ControladorApp::getInstance()-> setEstado("Se produjo un problema al cargar los archivos del nivel. Intente nuevamente");
		ControladorApp::getInstance()-> activarMenu();
		Logger::error(TAG, e.what());
		return;
	}
	ControladorApp::getInstance()->desactivarMenu();
	ControladorApp::getInstance()->activarJugador();
}

void ControladorJugador::conectarJugador(string puerto, string host) {
	if (this->jugador) {
		Logger::info(TAG,"Jugador ya esta creado");
		ControladorApp::getInstance()->setEstado("Jugador ya fue creado.");
	}
	else {
		try {
			this->jugador = new Jugador(puerto, host);
			this->manejador = new ManejadorEventosJugador(jugador->getServidorRemoto());
			Utilitario u;
			while (! this->ID_Recibido) {
				usleep(1000);
			}
			// Espero a que el servidor me responda
		} catch (ExceptionConex& e) {
			Logger::error(TAG, e.what());
			ControladorApp::getInstance()->setEstado(e.what());
			throw(e);
		}
	}
}

void ControladorJugador::cargarJuego(string archConfig, string archDefecto, list<parJugador*> jugadores){
	try {
		this->loader = new LoaderJugador(archConfig);
		this->loader->cargarVistas(jugadores, myID);
		this->loader->cargarElementosJuego();
		vistaVidas = this->loader->cargarVidas();
		Utilitario u;
		std::string cantIni = u.convertirAString(CANT_VIDAS);
		vistaVidas->setEstadoAnimacion(cantIni);
		this->setEstadoBonus(CORAZON, true);
	//	this->setEstadoBonus(ESPERANDO, true);
		//delete(loader);
	} catch (exception& e) {
		Logger::fatal(TAG,"No se pudo crear el nivel por falta de archivos.");
		throw ExceptionIO("No se pudo crear el nivel por falta de archivos.");
	}
}

Jugador* ControladorJugador::getJugador(){
	return this->jugador;
}

void ControladorJugador::setJugador(Jugador* j){
	this->jugador = j;
}

void ControladorJugador::setEstadoConexJugador(bool unEstado){
	this->jugadorConectado = unEstado;
}

bool ControladorJugador::JugadorEstaConectado(){
	return 	this->jugadorConectado;
}

void ControladorJugador::agregarProtagonista(parJugador* par){
	bool encontrado = false;
	AnimacionProtagonista* prot = NULL;
	list<Imagen*>::iterator it = listaAnimaciones.begin();
	while((it != listaAnimaciones.end()) and !encontrado) {
		if(!((*it)->getNombrePers()).compare(par->first)){
			encontrado = true;
			prot = (AnimacionProtagonista*)(*it);
			listaAnimaciones.erase(it);	
		}
		else
			++it;
	}
	
	if( !encontrado ){
	//	Logger::error(TAG, "No se pudo encontrar el protagonista.");
	}
	else{
		prot->setID(par->second);
		AnimacionesEnJuego.push_back(prot);
	}
	// TODO: Tengo que instanciar la vista y agregarla con su ID
	// Informar por la barra de estados y marcarlo como no disponible en el server
}

void ControladorJugador::desocuparVistaPersonaje(ID unID){
	IterlistaVistas it = this->AnimacionesEnJuego.begin();
	bool encontrado = false;
	while ((it != this->AnimacionesEnJuego.end()) and (!encontrado)){
		if ((*it)->getID() == unID) encontrado =true;
		else ++it;
	}

	if (!encontrado) return;
	Imagen* imagen = (*it);
	this->AnimacionesEnJuego.erase(it);
	// Le vuelvo a poner el ID como invalido
	(*it)->setID(ID_INVALIDO);
	this->listaAnimaciones.push_back(imagen);
}

void ControladorJugador::limpiarListas(){
	// Borro los elementos de las listas y las dejo vacias.
	IterlistaVistas it;
	for(it = this->AnimacionesEnJuego.begin(); it != this->AnimacionesEnJuego.end(); ++it){
		delete (*it);
	}
	AnimacionesEnJuego.clear();

	for(it = this->listaAnimaciones.begin(); it != this->listaAnimaciones.end(); ++it){
		delete (*it);
	}
	listaAnimaciones.clear();

	
	for(IterVistasEnemigos it = vistasEnemigos.begin(); it != vistasEnemigos.end(); ++it){
		delete (it->second);
	}
	vistasEnemigos.clear();
	
	for(list<st_VistasBonus*>::iterator it = vistasBonus.begin(); it != vistasBonus.end(); ++it){
		delete (*it)->imagen;
		delete (*it);
	}
	vistasBonus.clear();
	
	delete vistaVidas;
}

void ControladorJugador::desconectarASAP(bool valor){
	desconectar = valor;
}

void ControladorJugador::agregarVistaEnemigo(std::string tipo, ID unID, Imagen* vista){
	parJugador p(tipo, unID);
	m.lock();
	vistasEnemigos[p] = vista;
	m.unlock();
}

void ControladorJugador::moverVistaEnemigo(std::string tipo, ID unID, Point* posicion, std::string tipoMov){
	parJugador p(tipo, unID);

	m.lock();
	IterVistasEnemigos it = vistasEnemigos.find(p);
	if ( it == vistasEnemigos.end() ) {
		m.unlock();// printf ("moverVistaEnemigo m.unlock()\n");
		return;
	}

	( (AnimacionProtagonista*)(it->second) )->setEstadoAnimacion(tipoMov);

	( (it->second) )->setPos(posicion);
	// setPos se copia los valores de la nueva pos, no asigna puntero

	m.unlock();
}

AnimacionAuto* ControladorJugador::cargarPersonajeAnimado(std::string tipo, ID myID, Point* miPos){
	if (this->loader == NULL) {
		return NULL;
	}
	return this->loader->cargarPersonajeAnimado(tipo, myID, miPos);
}

AnimacionProtagonista* ControladorJugador::cargarEnemigo(std::string tipo, ID myID, Point* miPos){
	if (this->loader == NULL) {
		return NULL;
	}
	return this->loader->cargarEnemigo(tipo, myID, miPos);
}

void ControladorJugador::eliminarVistaEnemigo(std::string nombre, ID unID){
	parJugador p(nombre, unID);
	m.lock();
	IterVistasEnemigos it = vistasEnemigos.find(p);
	if (it == vistasEnemigos.end()){
		Logger::info(TAG, "No se encontro la vista: " + nombre);
		m.unlock();
		return;
	}

	// Se borra despues en el gameloop del jugador
	it->second->setActivo(false);
	m.unlock();
}

void ControladorJugador::eliminarVistasInactivas(){
	m.lock();
	IterVistasEnemigos it = vistasEnemigos.begin();
	while (it != vistasEnemigos.end()){
		if (it->second->getActivo() == false){
			delete (it->second);
			vistasEnemigos.erase(it++);
		} else {
			++it;
		}
	}
	m.unlock();
}

void ControladorJugador::agregarVistaBonus(st_VistasBonus* imagen){
	vistasBonus.push_back(imagen);
}

void ControladorJugador::modificarVidas(int cantVidas){
	Utilitario utilitario;
	this->vistaVidas->setEstadoAnimacion(utilitario.convertirAString(cantVidas));
}

AnimacionProtagonista* ControladorJugador::getVistaVidas(){
	return this->vistaVidas;
}

void ControladorJugador::setEstadoBonus(std::string elemento, bool estado){
	list<st_VistasBonus*>::iterator it = vistasBonus.begin();
	while(it != vistasBonus.end()){
		st_VistasBonus* st = (*it);
		if(st->nombre == elemento){
			st->activo = estado;
			return;
		}else ++it;
	}
	
}

void ControladorJugador::terminarJuego(std::string GanarOPerder){
	ControladorApp::getInstance()->setFinalizo(true);
	// activar vista bonus mensaje
	this->setEstadoBonus(GanarOPerder,true);
}

void ControladorJugador::setPosVistaNivel(Point* pos){
	m.lock();
	list<Imagen*>::iterator it = AnimacionesEnJuego.begin();
	VistaNivel* vistaNivel = (VistaNivel*) (*it);
	// se copia los valores
	vistaNivel->setVisor(pos);
	delete pos;
	m.unlock();
}
