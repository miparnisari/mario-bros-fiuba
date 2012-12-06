#include "Enemigo.h"

#define tiempoVida 5

Enemigo::Enemigo(Point* punto, int ancho, int alto, string Nombre, ID unID, float piso)
	: Personaje(punto, ancho, alto, Nombre, piso)
{
	myID = unID;
	activo = true;
	modificado = false;
	morir = false;
	this->temp = NULL;
	//this->temp->setIntervalo(tiempoVida);
}


void Enemigo::vivir(){
}
/*
MovimientoAutomatico* Enemigo::getMovimiento(){
	return (this->movimiento);
}

void Enemigo::aplicarRozamiento(float rozamiento){
	if (this->movimiento)
		this->movimiento->setRozamiento(rozamiento);
}
*/
 
void Enemigo::mover(int result){}

void Enemigo::setModificado(bool estado){
	modificado = estado;
}

void Enemigo::setActivo(bool estado){
	activo = estado;
}

void Enemigo::setMorir(bool estado){
	morir = estado;	
}

bool Enemigo::getMorir(){
	return morir;	
}

bool Enemigo::getModificado(){
	return modificado;
}

bool Enemigo::getActivo(){
	return activo;
}

void Enemigo::aplicarPow(){
	// Cada enemigo redefine el pow si lo afecta
}

std::string Enemigo::getTipoMovimiento(){
	std::string tipoMov = "quietoder"; //Por defecto devolvemos quietoder
	return tipoMov;
}
