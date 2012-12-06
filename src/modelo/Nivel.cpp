#include "Nivel.h"
#define MARGEN 150
#include "../app/ControladorApp.h"

using namespace std;

const string Nivel::TAG = "Nivel";

Nivel::Nivel(int ancho, int alto, int piso) 
{
	this->alto = alto;
	this->ancho = ancho;
	this->piso = piso;
}

Nivel::~Nivel() {

	for (list<Protagonista*>::iterator it = listaPersonajes.begin(); it != listaPersonajes.end(); ++it) {
		delete (*it);
	}
	for (list<Personaje*>::iterator it = listaPersEnJuego.begin(); it != listaPersEnJuego.end(); ++it) {
		delete (*it);
	}
	for (list<Elemento*>::iterator it = listaElementos.begin(); it != listaElementos.end(); ++it) {
		delete (*it);
	}
	for (IterEnemigos iterEneg = mapEnemigos.begin(); iterEneg != mapEnemigos.end(); ++iterEneg) {
		delete (*iterEneg).second;
	}
	Logger::info(TAG, "Eliminando objetos de la lista de personajes y protagonistas.");
}

int Nivel::getAncho(){
	return this->ancho;
}
		
int Nivel::getAlto(){
	return this->alto;
}

int Nivel::getPiso() {
	return this->piso;
}

void Nivel::vivir() {
	
	for (list<Personaje*>::iterator it = listaPersEnJuego.begin(); it != listaPersEnJuego.end(); ++it) {
		(*it)->vivir();
	
	}
	for (list<Elemento*>::iterator it = listaElementos.begin(); it != listaElementos.end(); ++it) {
		(*it)->vivir();
	}

	for (IterEnemigos iterEneg = mapEnemigos.begin(); iterEneg != mapEnemigos.end(); ++iterEneg) {
		(*iterEneg).second->vivir();
	}
}

void Nivel::agregarPersonaje(Protagonista* pers) {
	listaPersonajes.push_back(pers);
}

void Nivel::agregarPersEnJuego(Personaje* pers) {
	listaPersEnJuego.push_back(pers);
}

void Nivel::agregarElemento(Elemento* elem) {
	listaElementos.push_back(elem);
}

Protagonista* Nivel::getProtagonista(ID cliente) {
	list<Personaje*>::iterator it = listaPersEnJuego.begin();
	for (it; it != listaPersEnJuego.end(); ++it) {
		if( (*it)->getID() == cliente ) {
			return (Protagonista*) (*it);
		}
	}
	
	return NULL;
}

void Nivel::agregarProtagonista(parJugador jug){
	bool encontrado = false;
	Protagonista* prot ;
	list<Protagonista*>::iterator it = listaPersonajes.begin();
	while((it != listaPersonajes.end()) and !encontrado) {
		if(!((*it)->getNombre()).compare(jug.first)){
			encontrado = true;
			prot = (*it);
			listaPersonajes.erase(it);
		}
		else
			++it;
	}
	if( !encontrado ){
		Logger::error(TAG, "No se pudo encontrar el protagonista.");
	}
	else{
		prot->setID(jug.second);
		listaPersEnJuego.push_back(prot);
	}
}


bool Nivel::puedeMover(ID unID, Point* posNueva) {
	return (this -> puedeMoverEnX(unID, posNueva) and this -> puedeMoverEnY(unID, posNueva));
}

bool Nivel::verificarPiso(int alto, Point posicion){
	if((posicion.y < 0) || ((posicion.y + alto) > piso))
		return false;

	return true;
}

bool Nivel::puedeMoverEnY(ID unID,Point* posNueva) {
	//Cheque si puede moverse a la nueva posicion en y
	Personaje* pers = this->getProtagonista(unID);
	
	//Verificar bordes
 	if((posNueva->y < 0) || ((posNueva->y + pers->getAlto()) > piso)){
			
		if((pers->getPos()->y + pers->getAlto()) >= pers->getMovimiento()->getPiso()){
			pers->getMovimiento()->sePuedeSaltar = true;
			pers->getMovimiento()->setSaltando(false);
		}
		return false;
    }
	return true;
}

bool Nivel::puedeMoverEnX(ID unID,Point* posNueva) {
	//Cheque si puede moverse a la nueva posicion en X
	Personaje* pers = this->getProtagonista(unID);

	//Verificar bordes
 	if((posNueva->x < 0) || ((posNueva->x + pers->getAncho()) > this->ancho)){
		
		return false;
   }
	return true;
}

int Nivel::detectarColision(Personaje* pers, Point posAnterior){
	
	int resultado;
	int detener = 0;
	for (list<Personaje*>::iterator it = listaPersEnJuego.begin(); it != listaPersEnJuego.end(); ++it) {
		if((*it) != pers){
			resultado = (*it)->colisionaCon(pers);
			if(resultado != 0){
				detener = (*it)->aplicarColision(pers, resultado, posAnterior);
			}
		}
	}
	
	for (IterEnemigos iterEneg = mapEnemigos.begin(); iterEneg != mapEnemigos.end(); ++iterEneg) {
		
		if((*iterEneg).second != pers){
			
			resultado = ((*iterEneg).second->colisionaCon(pers) || (pers)->colisionaCon((*iterEneg).second));
			if(resultado != 0){
			
				detener =(*iterEneg).second->aplicarColision(pers,resultado, posAnterior);
			}
		}
	}
	
	for (list<Elemento*>::iterator it = listaElementos.begin(); it != listaElementos.end(); ++it) {
			resultado = ((*it)->colisionaCon(pers) || (pers)->colisionaCon(*it));
			if(resultado != 0){
				detener = (*it)->aplicarColision(pers,resultado, posAnterior);
			}
	}
			
	return detener;
	
}

int Nivel::detectarColisionEnemigo(Personaje* pers, Point posAnterior){

	int resultado;
	int detener = 0;

	for (IterEnemigos iterEneg = mapEnemigos.begin(); iterEneg != mapEnemigos.end(); ++iterEneg) {

		if((*iterEneg).second != pers){

			resultado = ((*iterEneg).second->colisionaCon(pers) || (pers)->colisionaCon((*iterEneg).second));
			if(resultado != 0){
				detener =(*iterEneg).second->aplicarColision(pers,resultado, posAnterior);
			}
		}
	}
	
	for (list<Elemento*>::iterator it = listaElementos.begin(); it != listaElementos.end(); ++it) {
			resultado = ((*it)->colisionaCon(pers) || (pers)->colisionaCon(*it));
			if(resultado != 0){
				detener = (*it)->aplicarColision(pers,resultado, posAnterior);
			}
	}

	return detener;
}


int Nivel::detectarColision(Elemento* elem, Point posAnterior){
	int resultado;
	int detener = false;

	for (list<Elemento*>::iterator it = listaElementos.begin(); it != listaElementos.end(); ++it) {
		if(elem != (*it)){
			resultado = (*it)->colisionaCon(elem);
			if(resultado != 0)
				(*it)->aplicarColision(elem,resultado, posAnterior);
		}
	}
	return detener;
}

void Nivel::aplicarMovimiento(Personaje* pers){
/*	Point posicionAnterior;
	posicionAnterior.x = pers->getPos()->x;
	posicionAnterior.y = pers->getPos()->y;
	pers->mover(1);
	//Controla solo que no se vaya de las dimensiones del nivel
	if(!this->puedeMoverEnX(pers->getID(),pers->getPos())){
			pers->getPos()->x = posicionAnterior.x;
	}
	if(!this->puedeMoverEnY(pers->getID(),pers->getPos())){
		pers->getPos()->y = posicionAnterior.y;
	}

	this->detectarColision(pers, posicionAnterior);
*/
}

void Nivel::removerProtagonistaEnJuego(ID cliente){
	bool encontrado = false;
	Protagonista* protagonista = NULL;
	list<Personaje*>::iterator it = listaPersEnJuego.begin();
	while((it != listaPersEnJuego.end()) and !encontrado) {
		if( (*it)->getID() == cliente)
			encontrado = true;
		else
			++it;
	}
	if( encontrado ){
		protagonista = (Protagonista*)(*it);
		listaPersEnJuego.erase(it);	
		listaPersonajes.push_back(protagonista);
	}
}

void Nivel::resolverColisiones(){
	for (list<Personaje*>::iterator it = listaPersEnJuego.begin(); it != listaPersEnJuego.end(); ++it) {
		for (list<Elemento*>::iterator itElem = listaElementos.begin(); itElem != listaElementos.end(); ++itElem)
		(*it)->colisionaCon((*itElem));
	}
}

void Nivel::agregarEnemigo(Enemigo* enemigo){
	parJugador p(enemigo->getNombre(), enemigo->getID());
	this->mapEnemigos[p] = enemigo;
}

void Nivel::eliminarEnemigo(Enemigo* enemigo){
	IterEnemigos it;
	parJugador p(enemigo->getNombre(), enemigo->getID());
	it = mapEnemigos.find(p);
	if (it == mapEnemigos.end()) return;
	delete enemigo;
	mapEnemigos.erase (it);      
}

bool Nivel::dentroDeLimites(Point* pos){
	if ((pos->x < 0 - MARGEN or pos->x > this->ancho + MARGEN) or
	(pos->y < 0 - MARGEN or pos->y > this->alto + MARGEN)) return false;
	return true;
}

void Nivel::marcarInactivos(){
	// Reviso que enemigos se fueron de los limites del nivel
	Point* pos = NULL;
	for (IterEnemigos iterEneg = mapEnemigos.begin(); iterEneg != mapEnemigos.end(); ++iterEneg) {
		pos = (*iterEneg).second->getPos();
		if (pos!= NULL and !(this->dentroDeLimites(pos))){
			(*iterEneg).second->setMorir(true);
		}
	}
}

void Nivel::eliminarEnemigosInactivos(){
	this->marcarInactivos();
	
	IterEnemigos iterEneg = mapEnemigos.begin();
	while( iterEneg != mapEnemigos.end()) {
		if  ((*iterEneg).second->getMorir() == true ) {
			EventoEliminarEnemigo ev((iterEneg)->second);
			ControladorApp::getInstance()->getServidor()->eliminarEnemigo((iterEneg)->second);
			ControladorApp::getInstance()->getServidor()->enviarEventoJugadores(&ev);

			mapEnemigos.erase(iterEneg++);
		}
		++iterEneg;
	}
}

void Nivel::aplicarPow(){
	for (IterEnemigos iterEneg = mapEnemigos.begin(); iterEneg != mapEnemigos.end(); ++iterEneg) {
		(*iterEneg).second->aplicarPow();
	}
}

int Nivel::getProtagonistasVivos(){
	int i = 0;
	for (list<Personaje*>::iterator it = listaPersEnJuego.begin(); it != listaPersEnJuego.end(); ++it) {
		if ((*it)->getVidas() > 0) i++;
	}

	return i;
}
