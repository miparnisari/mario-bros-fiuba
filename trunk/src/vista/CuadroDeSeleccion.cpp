#include "CuadroDeSeleccion.h"

const int CANT_OPCS_VISIBLES = 8;
const int ANCHO_BARRA_SCROLL = 30;
using namespace std;

CuadroDeSeleccion::CuadroDeSeleccion(string id, int x, int y, int w, int h)
	: ComponenteSinImagen(id,x,y,w,h)
{
	this->opcionMinimaVisible = 0;
	this->opcionMaximaVisible = CANT_OPCS_VISIBLES - 1;
	this->barraScroll = new BarraScroll("barraScroll", x+w, y-1, ANCHO_BARRA_SCROLL, h+2);
	this->opcionActual = NULL;
	this->espacioParaDibujar = NULL;
	this->espacioParaTexto = NULL;
	this->opcionActual = NULL;
}

CuadroDeSeleccion::~CuadroDeSeleccion()
{
	for (int i = 0; i < opciones.size(); ++i ) {
		delete(opciones[i]);
	}
	if(barraScroll) delete(this->barraScroll);
	if (espacioParaTexto) delete(espacioParaTexto);
	if (espacioParaDibujar) delete(espacioParaDibujar);
	this->opcionActual = NULL;
}

void CuadroDeSeleccion::drawBox(SDL_Surface* destino)
{
	// Fondo blanco
	SDL_Rect rect = this->box;
	SDL_FillRect(destino,&rect, WHITE);
	
	// Barra izquierda vertical
	rect.x = box.x - 1;
	rect.y = box.y - 1;
	rect.w = 1;
	rect.h = box.h + 1;
	SDL_FillRect(destino, &rect, BLACK );
	
	// Barra derecha vertical
	rect.x = box.x + box.w;
	rect.y = box.y - 1;
	rect.w = 1;
	rect.h = box.h + 1;
	SDL_FillRect(destino, &rect, BLACK );
	
	// Barra arriba horizontal
	rect.x = box.x - 1;
	rect.y = box.y - 1;
	rect.w = box.w;
	rect.h = 1;
	SDL_FillRect(destino, &rect, BLACK );
	
	// Barra abajo horizontal
	rect.x = box.x -1 ;
	rect.y = box.y + box.h ;
	rect.w = box.w;
	rect.h = 1;
	SDL_FillRect(destino, &rect, BLACK );
}

void CuadroDeSeleccion::drawOptions(SDL_Surface* destino) {
	int i = (this -> getOpcionMinimaVisible() < 0) ? 0 : this -> getOpcionMinimaVisible();
	int j = (opciones.size() <= opcionMaximaVisible) ? opciones.size() : opcionMaximaVisible+1;
	int k = i;
	for (i; i < j; i++) {
		float alturaOpcion = (this->box.h / (float)CANT_OPCS_VISIBLES);
		int alturaRedondeada = ceil(alturaOpcion);
		int y = box.y + (i-k)*(alturaRedondeada-1);
		
		opciones[i]->setDimensiones(box.x, y, box.w , alturaRedondeada);
		opciones[i]->refrescar(destino);
	}
}

void CuadroDeSeleccion::refrescar(SDL_Surface* destino) {
	
	// Dibujamos los 4 bordes del cuadro
	this->drawBox(destino);
	
	// Marcamos a la opcion activa como tal, para que la misma se dibuje pintada.
	if ( this -> opcionActual ) {
		this -> opcionActual -> seleccionar();
	}
	
	// Escribimos las opciones
	this->drawOptions(destino);
	
	// Dibujamos la barra de scroll
	this->barraScroll->refrescar(destino);
}

bool CuadroDeSeleccion::manejarEventos(SDL_Event event) {
	
	// Primero debo desmarcar todas porque el uso del scroll hace que compartan la posición de selección.
	for ( int k=0; k < this -> opciones.size(); k++) {
		opciones[k] -> desmarcar();
	}
	// Cada opcion maneja su evento
	int i = (this -> getOpcionMinimaVisible() < 0) ? 0 : this -> getOpcionMinimaVisible();
	int j = (opciones.size() <= opcionMaximaVisible) ? opciones.size() : opcionMaximaVisible +1;
	int k = i;
	for (i; i < j; i++) {
		float alturaOpcion = (this->box.h / (float)CANT_OPCS_VISIBLES);
		int alturaRedondeada = ceil(alturaOpcion);
		int y = box.y + (i-k)*(alturaRedondeada-1);
		
		opciones[i]->setDimensiones(box.x, y, this -> box.w , alturaRedondeada);
		opciones[i]->manejarEventos(event);
	}
	
	// Movemos la lista de opciones visibles hacia arriba o hacia abajo.
	int mov = this->barraScroll->getIncremento(event);
	if (mov > 0) {
		// Boton de arriba fue presionado
		if (this -> getOpcionMinimaVisible() > 0) {
			this -> setOpcionMinimaVisible (this -> getOpcionMinimaVisible() - mov);
			this -> setOpcionMaximaVisible (this -> getOpcionMaximaVisible() - mov);
		}
	}
	if (mov < 0) {
		// Boton de abajo fue presionado
		if (this -> getOpcionMaximaVisible() < opciones.size()-1) {
			this -> setOpcionMinimaVisible (this -> getOpcionMinimaVisible() - mov);
			this -> setOpcionMaximaVisible (this -> getOpcionMaximaVisible() - mov);
		}
	}
	
	//Me fijo cual fue apretada para dejarla como activa. Si ninguna fue apretada permanece la ultima activa.
	i = (this -> getOpcionMinimaVisible() < 0) ? 0 : this -> getOpcionMinimaVisible();
	j = (opciones.size() <= this -> getOpcionMaximaVisible()) ? opciones.size() : this -> getOpcionMaximaVisible() +1;
	for (i; i < j; i++) {
		if ( (opciones[i])-> estaSeleccionada() ) {
			this -> opcionActual = opciones[i];
			if (this -> espacioParaDibujar != NULL) {}
			if (this -> espacioParaTexto != NULL) {}
			break;
		}
	}

	return true;
}

void CuadroDeSeleccion::agregarOpcion(Opcion* o) {
	if (o == NULL) {
		return;
	}
	if (opcionActual == NULL) {
		this->opcionActual = o;
	}
	this->opciones.push_back(o);
}

int CuadroDeSeleccion::getOpcionMinimaVisible() {
	return opcionMinimaVisible;
}

int CuadroDeSeleccion::getOpcionMaximaVisible() {
	return opcionMaximaVisible;
}

bool CuadroDeSeleccion::setOpcionMinimaVisible(int num) {
	if (num >= 0) {
		this -> opcionMinimaVisible = num;
		return true;
	}
	return false;
}

string CuadroDeSeleccion::getData() {
	return (this->opcionActual->getData());

}

bool CuadroDeSeleccion::setOpcionMaximaVisible(int num) {
	if ( num < this -> opciones.size() ) {
		this -> opcionMaximaVisible = num;
		return true;
	}
	return false;
}
