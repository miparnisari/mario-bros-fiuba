#include "loadpersonaje.h"


LoadPersonaje::LoadPersonaje()
{
	nombre = ERROR;
	x = ERROR;
	y = ERROR;
}

void LoadPersonaje::setX(string param){
	x = param;
}

void LoadPersonaje::setY(string param){
	y = param;
}

void LoadPersonaje::setNombre(string param){
	nombre = param;
}

void LoadPersonaje::setAncho(string param){
	ancho = param;
}

void LoadPersonaje::setAlto(string param){
	alto = param;
}

void LoadPersonaje::setImagen(string param){
	imagen = param;
}

void LoadPersonaje::setVelocidad(string param){
	velocidad = param;
}

void LoadPersonaje::setMargenScroll(string param){
	margenScroll = param;
}

void LoadPersonaje::setPotenciaSalto(string param){
	potenciaSalto = param;
}

void LoadPersonaje::cargarAnimacion(LoadAnimacion* animacion){
	animaciones.push_front(animacion);
}

string LoadPersonaje::getX(){
	return x;
}

string LoadPersonaje::getY(){
	return y;
}

string LoadPersonaje::getNombre(){
	return nombre;
}

string LoadPersonaje::getAncho(){
	return ancho;
}

string LoadPersonaje::getAlto(){
	return alto;
}

string LoadPersonaje::getImagen(){
	return imagen;
}

string LoadPersonaje::getVelocidad(){
	return velocidad;
}

string LoadPersonaje::getMargenScroll(){
	return margenScroll;
}

string LoadPersonaje::getPotenciaSalto(){
	return potenciaSalto;
}

LoadPersonaje::~LoadPersonaje() {
	for (list<LoadAnimacion*>::iterator iter = animaciones.begin(); iter != animaciones.end(); ++iter)
		delete(*iter);
}

