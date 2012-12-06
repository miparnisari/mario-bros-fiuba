#include "MovimientoPersonaje.h"
#include <stdio.h>
//#define C1 0.05
#define C2 0.1

#define CSALTO 0.1
#define VELMAXIMACAIDA -0.1

const double G = -9.82;

MovimientoPersonaje::MovimientoPersonaje(Point* unaPosicion, int potencia, int vel, float piso)
	: Movimiento (unaPosicion, potencia, vel, piso)
{
	//posicion = unaPosicion;
	//velocidad.x = 0;
	//velocidad.y = 0;
	C1 = vel * 0.01;
	saltando = dobleSalto = false;
	cayendo = false;
	rebotando = false;
	puedeVolar = true; // esto deberia ser false inicialmente, y setearlo a gusto con el setter
	quiereVolar = false;
	quiereSubir = false;
	quiereBajar = false;
	sePuedeSaltar = false;
	estaSiendoEmpujado = false;
	presionada = false;

	//potenciaSalto = potencia;
	//posVertInicial = unaPosicion->y;
	rozamiento = 0;
}

void MovimientoPersonaje::aplicarFuerza(double fuerza){
   
   //if (!cayendo)
        velocidad.x = fuerza * C2;
	
}

void MovimientoPersonaje::caer() {
	
	caidaSinSalto = false;
    if (saltando && !cayendo /*&& (posicion->y - posVertInicial < -40)/* && (posicion->y < posFinal)*/ ) {
        velocidad.y = (-1) * POTENCIA_CAIDA;
        velocidad.x = 0;
        cayendo = true;
        saltando = false;
    }
}

void MovimientoPersonaje::subir() {
	this->posicion->y -= 0.1;
}

void MovimientoPersonaje::bajar() {
	this->posicion->y += 0.1;
}

void MovimientoPersonaje::detenerCaida() {
	caidaSinSalto = false;
	velocidad.y = 0;
}

void MovimientoPersonaje::detenerDesplazamiento() {
	velocidad.x = 0;
}

void MovimientoPersonaje::saltar(){
	
	if (estaSiendoEmpujado) {
		saltarAlto();
		return;
	}
	caidaSinSalto = false;

	if (! cayendo and ! saltando and sePuedeSaltar )  {
		velocidad.y = potenciaSalto * 3; //* CSALTO;
		saltando = true;
		cayendo = false;
		rebotando = false;
	}
	
	
}



void MovimientoPersonaje::rebotar(){
	
	if(!rebotando && sePuedeSaltar)
	velocidad.y = potenciaSalto * 2; //* CSALTO;
	rebotando = true;
	cayendo = false;
	
}

void MovimientoPersonaje::saltarAlto() {
	caidaSinSalto = false;
	estaSiendoEmpujado = false;

	if (! cayendo and ! saltando)  {
		velocidad.y = potenciaSalto * 5; //* CSALTO;
		saltando = true;
		cayendo = false;
		//posVertInicial = posicion->y;
	}
}

void MovimientoPersonaje::setPuedeVolar(bool estado) {
	this->puedeVolar = estado;
}

void MovimientoPersonaje::setQuiereVolar(bool estado) {
	this->quiereVolar = estado;
}

bool MovimientoPersonaje::getQuiereBajar() {
	return (this->quiereBajar);
}

bool MovimientoPersonaje::getQuiereSubir() {
	return (this->quiereSubir);
}

void MovimientoPersonaje::setQuiereSubir(bool estado) {
	//std::cout << "Setearon quiereSubir en: " << estado << endl;
	this->quiereSubir = estado;
}

void MovimientoPersonaje::setQuiereBajar(bool estado) {
	//std::cout << "Setearon quiereBajar en: " << estado << endl;
	this->quiereBajar = estado;
}

bool MovimientoPersonaje::topeSaltoAlcanzado() {
	return (velocidad.y < 0);
}

bool MovimientoPersonaje::getPresionada() {
	return presionada;
}

void MovimientoPersonaje::setPresionada(bool estado) {
	this->presionada = estado;
}

void MovimientoPersonaje::setPuedeSaltar(bool estado) {
	sePuedeSaltar = estado;
}

void MovimientoPersonaje::actualizar() {


	if (saltando || rebotando){
		velocidad.y += (0.001 * G); //Se disminuye la velocidad
	
		if(quiereVolar and topeSaltoAlcanzado() and presionada) {
	
			velocidad.y = 0;
		}
		
			
	}
	
	posicion->x += velocidad.x * C1;
	posicion->y -= velocidad.y * 0.01;
	
	/*
	if(saltando || cayendo ){
		if (posicion->y >= posVertInicial){
			posicion->y = posVertInicial;
			saltando = dobleSalto = false;
			cayendo = false;
			velocidad.y = 0;
		}
	}
	*/
    velocidad.x *= rozamiento;

    if (velocidad.y <=0) {

		estaSiendoEmpujado = false;
	}

}

void MovimientoPersonaje::setRozamiento(float rozamiento){
	this->rozamiento = rozamiento;
}

void MovimientoPersonaje::empujarEnY(double impulso) {
	this->velocidad.y = (impulso*potenciaSalto);
	estaSiendoEmpujado = true;
	saltando = false;
	cayendo = false;
}

double MovimientoPersonaje::getVelocidadX(){
	return velocidad.x;
}

double MovimientoPersonaje::getVelocidadY(){
	return velocidad.y;
}

void MovimientoPersonaje::setVelocidadX(double valor){
	velocidad.x = valor;
}
void MovimientoPersonaje::setVelocidadY(double valor){
	velocidad.y = valor;
}
