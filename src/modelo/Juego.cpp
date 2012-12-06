#include "Juego.h"

const string Juego::TAG = "Juego";


Juego::Juego(Nivel* nivel) {
	this-> activo = true;
	this-> nivel = nivel;
}

Juego::~Juego() {
	delete (this-> nivel);
}

void Juego::simular() {
	if (this->nivel)
		this->nivel->vivir();

}

void Juego::agregarProtagonista(parJugador prot) {
	this->nivel->agregarProtagonista(prot);
}


void Juego::setActivo(bool param){
	this->activo = param;
}

Nivel* Juego::getNivel(){
	return this->nivel;
}

void Juego::setNivel(Nivel* nivel){
	this->nivel = nivel;
}

int Juego::detectarColision(ID cliente,Point posAnterior){
	Protagonista* prot = this->getProtagonista(cliente);
	return this->nivel->detectarColision(prot,posAnterior);
}

int Juego::detectarColision(Personaje* pers, Point posAnterior){
	return (this->nivel->detectarColision(pers,posAnterior));
}

int Juego::detectarColisionEnemigo(Personaje* pers, Point posAnterior){
	return (this->nivel->detectarColisionEnemigo(pers,posAnterior));
}

bool Juego::puedeMover(ID unID, Point* posNueva){
	
	if(this->nivel->puedeMover(unID, posNueva))
		return true;
	
	return false;	
}

bool Juego::puedeMoverEnX(ID unID, Point* posNueva) {
	return this->nivel->puedeMoverEnX(unID, posNueva);
}

bool Juego::puedeMoverEnY(ID unID, Point* posNueva) {
	return this->nivel->puedeMoverEnY(unID, posNueva);
}

int Juego::get_anchoNivel() {
	return this->nivel->getAncho();
}

int Juego::get_altoNivel() {
	return this->nivel->getAlto();
}

float Juego::getPiso(){
	return (this->nivel->getPiso());
}

Protagonista* Juego::getProtagonista(ID cliente) {
	if (!this->nivel){
		return NULL;
	}
	return (this->nivel->getProtagonista(cliente));
}

void Juego::removerProtagonistaEnJuego(ID unID){
	this->nivel->removerProtagonistaEnJuego(unID);
}

void Juego::resolverColisiones(){
	this->nivel->resolverColisiones();
}

bool Juego::verificarPiso(int alto, Point posicion){
	return (this->nivel->verificarPiso(alto,posicion));
}

void Juego::agregarEnemigo(Enemigo* enemigo){
	this->nivel->agregarEnemigo(enemigo);
}

void Juego::aplicarMovimiento(Personaje* pers){
	nivel->aplicarMovimiento(pers);	
}

void Juego::eliminarEnemigosInactivos(){
	nivel->eliminarEnemigosInactivos();
}

void Juego::aplicarPow(){
	nivel->aplicarPow();
}
