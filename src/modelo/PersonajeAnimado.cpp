#include "PersonajeAnimado.h"
const string PersonajeAnimado::TAG = "PersonajeAnimado";

PersonajeAnimado::PersonajeAnimado(Point* punto, int ancho, int alto, string nombre, float piso)
	: Personaje(punto, ancho, alto, nombre, piso)
{
	this->temp = Temporizador();
	this->movimiento = NULL;
	this->activo = true;
}

PersonajeAnimado::~PersonajeAnimado()
{
	delete(this->movimiento);
}

void PersonajeAnimado::setActivo(bool estado) {
	this->activo = estado;
}

bool PersonajeAnimado::getActivo() {
	return activo;
}

MovimientoAutomatico* PersonajeAnimado::getMovimiento(){
	return (this->movimiento);
}

void PersonajeAnimado::aplicarRozamiento(float rozamiento){
	if (this->movimiento)
		this->movimiento->setRozamiento(rozamiento);
}

void PersonajeAnimado::vivir(){
	//if (this->temp->puedeRealizarAccion()) this->animar();
}

void PersonajeAnimado::animar(){
	//Esto depende de que debe hacer el personaje.
	//De ser necesario diferentes comportamiento, se podria tener una clase Accion
}

void PersonajeAnimado::mover(int result){}

