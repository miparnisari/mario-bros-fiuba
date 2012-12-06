#include "EspacioParaDibujar.h"

#define PRIORIDAD 1
#define ID 123


EspacioParaDibujar::EspacioParaDibujar(string id, int x, int y, int w, int h)
	: ComponenteSinImagen(id,x,y,w,h) 
{
	this -> animacion = NULL;
}

EspacioParaDibujar::~EspacioParaDibujar() {
	delete(animacion);
}

void EspacioParaDibujar::drawBox(SDL_Surface* destino)
{
	SDL_Rect rect;
	
	// Barra izquierda vertical
	rect.x = box.x - 1;
	rect.y = box.y - 1;
	rect.w = 1;
	rect.h = box.h + 1;
	SDL_FillRect(destino, &rect, BLACK );
	
	// Barra derecha vertical
	rect.x = box.x + box.w -2;
	rect.y = box.y;
	rect.w = 1;
	rect.h = box.h;
	SDL_FillRect(destino, &rect, BLACK );
	
	// Barra arriba horizontal
	rect.x = box.x -1;
	rect.y = box.y -1;
	rect.w = box.w;
	rect.h = 1;
	SDL_FillRect(destino, &rect, BLACK );
	
	// Barra abajo horizontal
	rect.x = box.x -1;
	rect.y = box.y + box.h -1;
	rect.w = box.w;
	rect.h = 1;
	SDL_FillRect(destino, &rect, BLACK );
}

bool EspacioParaDibujar::manejarEventos(SDL_Event event) {
	// No debe hacer nada
	return true;
}

void EspacioParaDibujar::setAnimacion(int ancho, int alto, string nombreArchivo, vector<st_Animacion*> vectorAnimaciones,std::string nombre) {
	this -> animacion = new AnimacionAuto(nombreArchivo, NULL, PRIORIDAD, alto, ancho, vectorAnimaciones, ID, nombre);
}

void EspacioParaDibujar::refrescar(SDL_Surface* destino) {
	// Dibujo la imagen
	SDL_Surface* imgFuente = animacion->getImg();
	SDL_Rect* rectFuente = animacion->getCuadro();
	SDL_Rect rectDestino = this->box;
	rectDestino.w = rectFuente->w;
	rectDestino.h = rectFuente->h;
	SDL_BlitSurface(imgFuente, rectFuente, destino, &rectDestino);
	
	// Dibujo un borde rectangular negro
	this->drawBox(destino);
}
