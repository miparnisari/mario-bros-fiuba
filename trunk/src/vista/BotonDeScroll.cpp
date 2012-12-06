#include "BotonDeScroll.h"

using namespace std;

const int INCREMENT0 = 1;

BotonDeScroll::BotonDeScroll(string id, int x, int y, int w, int h, int inc)
:ComponenteSinImagen (id, x, y, w, h) {
	this -> incremento = INCREMENT0;
}

void BotonDeScroll::refrescar(SDL_Surface* destino) {
	// No hace nada
}

void BotonDeScroll::refrescarArriba(SDL_Surface* destino) {
	this->drawTriangleUp(destino);
}

void BotonDeScroll::refrescarAbajo(SDL_Surface* destino) {
	this->drawTriangleDown(destino);
}

void BotonDeScroll::drawTriangleDown(SDL_Surface* destino) {
	int x = box.x;
	int y = box.y;
	int w = box.w;
	int h = box.h;

	SDL_Rect rect;
	int k = 0;
	int i = y;
	while (i <= y+h) {
		rect.x = x + k;
		rect.y = y + k;
		rect.w = w - 2*k;
		if (rect.w == 0) break;
		rect.h = 1; 
		SDL_FillRect(destino, &rect, BLACK);
		k ++ ;
		i ++ ;
	}
}

void BotonDeScroll::drawTriangleUp(SDL_Surface* destino) {
	int x = box.x;
	int y = box.y;
	int w = box.w;
	int h = box.h;

	SDL_Rect rect;
	int k = 0;
	int i = y+h;
	while (i >= y) {
		rect.x = x + k;
		rect.y = i;
		rect.w = w - 2*k;
		if (rect.w == 0) break;
		rect.h = 1;
		SDL_FillRect(destino, &rect, BLACK);
		k ++ ;
		i --;
	}
}

int BotonDeScroll::getIncremento() {
	return (this->incremento);
}

bool BotonDeScroll::manejarEventos(SDL_Event event) {

	// Si se presiono el mouse
	if( event.type == SDL_MOUSEBUTTONDOWN)
	{
		if (event.button.button == SDL_BUTTON_LEFT )
		{
			// Obtengo los offsets del mouse
			int x = event.button.x;
			int y = event.button.y;

			// Si el mouse esta arriba del boton
			if( ( x > box.x ) && ( x < box.x + box.w ) && ( y > box.y ) && ( y < box.y + box.h ) )
			{
				//Debo mover el indice
				return true;
			}
		}
	}
	
	return false;
}

BotonDeScroll::~BotonDeScroll(){};

