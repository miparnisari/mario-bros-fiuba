#include "AnimacionProtagonista.h"

const string AnimacionProtagonista::TAG = "AnimacionProtagonista";

using namespace std;

AnimacionProtagonista::AnimacionProtagonista(string nombre, Posicionable* animado, int prior,int alto, int ancho, vector<st_Animacion*> vectorAnimaciones, ID id, string nombrePers)
							: Animacion(nombre, animado, prior, alto, ancho, vectorAnimaciones,id, nombrePers){
	Logger::debug(TAG, "Constructor de animacion");
	this-> estadoAnimacion = "quietoder";
	this->margenScroll = 0;
	Logger::debug(TAG, "Construye clips.");
}

AnimacionProtagonista::~AnimacionProtagonista() {
	// Libero la memoria pedida de los struct st_Animacion, ya que
	// en el map guardo punteros a los mismo.
	// La memoria se pide en Loader::cargarAnimacionesProt
	// Y en Loader::cargarAnimacionesPers
	SDL_FreeSurface( this->img );
	map<std::string, st_Animacion* >::iterator iter;
	for (iter = animaciones.begin(); iter != animaciones.end(); ++iter)
		delete (iter->second);
		
	animaciones.clear();
}

SDL_Rect* AnimacionProtagonista::getCuadro(){
	
	this->frame = seleccionarImagen(this->frame);
	SDL_Rect* cuadro = &((clips[estadoAnimacion]).at(frame));

	return cuadro;
}

int AnimacionProtagonista::getMargenScroll(){
	return this->margenScroll;
}

void AnimacionProtagonista::setMargenScroll(int scroll){
	this->margenScroll = scroll;
}

int AnimacionProtagonista::seleccionarImagen(int frameActual){
	int cantFrames = animaciones[estadoAnimacion]->cantidad;
	int pos =  (frameActual < cantFrames - 1) ? frameActual + 1 : 0;

	return pos;
}

void AnimacionProtagonista::setEstadoAnimacion(string estado){
	this->estadoAnimacion = estado;
}
