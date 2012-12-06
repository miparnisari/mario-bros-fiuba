#include "BarraScroll.h"

#define ALTO_BOTON_SCROLL 20
#define INCREMENTO 2

using namespace std;

BarraScroll::BarraScroll(string id, int x, int y, int w, int h)
	: ComponenteSinImagen(id,x,y,w,h)
{
	this->botonArriba = new BotonDeScroll("arriba",x,y,w,ALTO_BOTON_SCROLL,INCREMENTO);
	this->botonAbajo = new BotonDeScroll("abajo",x,y+h-ALTO_BOTON_SCROLL,w,ALTO_BOTON_SCROLL,INCREMENTO);
}

BarraScroll::~BarraScroll()
{
	delete(botonArriba);
	delete(botonAbajo);
}

void BarraScroll::refrescar(SDL_Surface* destino) {
	
	// TO DO: pintar una barra vertical
	SDL_Rect rect = box;
	SDL_FillRect(destino, &rect, GREY);
	
	// Pintar los botones
	this->botonArriba->refrescarArriba(destino);
	this->botonAbajo->refrescarAbajo(destino);
	
	
}

bool BarraScroll::manejarEventos(SDL_Event event) {
	// No hace nada
	return true;
}

int getNegativo(int num) {
	return (num*(-1));
}

int BarraScroll::getIncremento(SDL_Event event) {
	int incremento = 0;
	
	// Si se presiono el boton de arriba
	if (this->botonArriba->manejarEventos(event) > 0) {
		incremento = this->botonArriba->getIncremento();
	}
	// Si se presiono el boton de abajo 
	else if (this->botonAbajo->manejarEventos(event) > 0) {
		incremento = getNegativo(this->botonAbajo->getIncremento());
	}
	
	return incremento;
}
