#include "Solapa.h"

using namespace std;

const string Solapa::TAG = "Solapa";

Solapa::Solapa(string n) {
	this-> nombre = n;
	this-> botonAsociado = new Boton("",0,0,0,0,NULL,n,FONT,FONT_SIZE);
	this-> activa = false;
}

Solapa::~Solapa() {
	delete(this->botonAsociado);

	// Eliminamos los componentes de la solapa
	list<Componente*>::iterator it;
	for (it = componentes.begin(); it != componentes.end(); ++it) {
		delete(*it);
		*it = NULL;
	}
}

void Solapa::setBotonAsociado(int x, int y, int w, int h) {
	this->botonAsociado->setDimensiones(x,y,w,h);
}

void Solapa::setActive(bool estado) {
	this->activa = estado;
	this->botonAsociado->setActive(estado);
}

const bool Solapa::isActive() {
	return (this->activa);
}

const string Solapa::getNombre() {
	return (this->nombre);
}

list<Componente*>& Solapa::getComponentes() {
	// Devuelvo una referencia a la lista
	return (this-> componentes);
}

Boton* Solapa::getBotonAsociado() {
	return (this-> botonAsociado);
}

void Solapa::agregarComponente(Componente* unComp){
    this->componentes.push_back(unComp);
}

void Solapa::eliminarComponente(std::string unID) {
	for(list<Componente*>::iterator it = this->componentes.begin(); it != this->componentes.end() ; ++it) {
		if ( (*it) -> getID() == unID ) {
			it = componentes.erase(it);
		}
	}

	//throw ExceptionComponenteNoEncontrado();
}

void Solapa::drawBackground(SDL_Surface* destino) {
	SDL_Rect rect;
	rect.x = MENU_INNER_BORDER;
	rect.y = MENU_INNER_BORDER + ALTO_BOTON;
	rect.w = SCREEN_WIDTH - 2*MENU_INNER_BORDER;
	rect.h = SCREEN_HEIGHT - 2*MENU_INNER_BORDER - ALTO_BOTON;
	
	SDL_FillRect(destino, &rect, DARK_GREY);
}

void Solapa::refrescar(SDL_Surface* destino) {
	
	if (this->activa) {
		this->botonAsociado->setActive(true);
		this->drawBackground(destino);
		
		list<Componente*>::iterator it = this->componentes.begin();
		for (it ; it != this->componentes.end(); ++it) {
			(*it)->refrescar(destino);
		}
	}
	
	this->botonAsociado->refrescar(destino);

}

void Solapa::manejarEventos(SDL_Event event) {
	
	//if (this->botonAsociado->fuePresionado(event))
		//this->setActive(true);
	
	// Cada componente manejara su evento
	list<Componente*>::iterator it = componentes.begin();
	for (it ; it != componentes.end(); ++it) {
		(*it)->manejarEventos(event);
	}
}
