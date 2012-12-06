#include "AnimacionAuto.h"

const string AnimacionAuto::TAG = "AnimacionAuto";

AnimacionAuto::AnimacionAuto(std::string nombre, Posicionable* animado, int prioridad,int alto, int ancho, vector<st_Animacion*> vectorAnimaciones, ID unID, std::string nombrePers)
						: Animacion(nombre, animado, prioridad, alto, ancho, vectorAnimaciones, unID, nombrePers) {
	
	iterador = this->animaciones.begin();
	this->frame = 0;
	if (iterador == this->animaciones.end()){
		Logger::error(TAG, "Lista de animaciones vacia: " + nombre);
		throw ExceptionAnimation(nombre);
	}
	//Inicializo el temporizador
	this->temp.setIntervalo(iterador->second->periodo);
	temp.setTiempoInicial();
	Logger::info  (TAG , "Construccion correcta");
}

AnimacionAuto::~AnimacionAuto() {
	SDL_FreeSurface( this->img );
	// Libero la memoria pedida de los struct st_Animacion, ya que
	// en el map guardo punteros a los mismo.
	// La memoria se pide en Loader::cargarAnimacionesProt
	// Y en Loader::cargarAnimacionesPers
	std::map<std::string, st_Animacion* >::iterator iter;
	for (iter = animaciones.begin(); iter != animaciones.end(); ++iter)
		delete (iter->second);
		
	animaciones.clear();
}

void AnimacionAuto::nextAnimacion(){
	// Se encarga de incrementar el iterador ciclicamente y setear el temporizador

	temp.setIntervalo((*iterador).second->periodo);

	++iterador;

	if (iterador == this->animaciones.end()){
		iterador = this->animaciones.begin() ;
	}
}

int AnimacionAuto::seleccionarImagen(int frameActual){
	int  pos = 0;
	bool cambiaAnimacion = false;

	if (temp.puedeRealizarAccion()){
		int cantFrames = iterador->second->cantidad;
		pos =  (frameActual < cantFrames - 1) ? frameActual + 1 : 0;
		// Si la posicion es cero, es porque se cambia de animacion
		if (pos == 0) cambiaAnimacion = true;
	}

	if (cambiaAnimacion) {
		nextAnimacion();
		temp.setTiempoInicial();
	}
	
	return pos;
}

SDL_Rect* AnimacionAuto::getCuadro(){

	this->frame = seleccionarImagen(this->frame);
	SDL_Rect* cuadro = &((clips[iterador->second->ejecucion]).at(frame));
	return cuadro;
}
