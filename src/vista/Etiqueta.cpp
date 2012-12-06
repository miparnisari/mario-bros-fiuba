#include "Etiqueta.h"
#include "../other/Logger.h"
#include "../excepciones/Excepciones.h"
#include <iostream>

using namespace std;

const string Etiqueta::TAG = "Etiqueta";

Etiqueta::Etiqueta(string id, int x, int y, int w, int h, string texto, string unaFont, int fontSize)
: ComponenteSinImagen (id, x, y, w, h ) {
	TTF_Init();
	SDL_EnableUNICODE(SDL_ENABLE);
	
	this->texto = texto;
	this->fontSize = fontSize;
	
	this->font = TTF_OpenFont(unaFont.c_str(), fontSize);
	if (! font) {
		Logger::error(TAG, "No se pudo abrir la fuente: " + string(unaFont));
		throw ExceptionCargaTTF(unaFont);
	}
	
	SDL_Color textColor = Componente::translate_color(BLACK);
	this->textoAmostrar = this -> renderizarTexto(this->font, this->texto, textColor);

}

void Etiqueta::refrescar(SDL_Surface* destino) {
	SDL_BlitSurface(textoAmostrar, NULL, destino, &this->box);
}

bool Etiqueta::manejarEventos(SDL_Event event) {
	// No hace nada
	return true;
}

Etiqueta::~Etiqueta() {
	SDL_FreeSurface(textoAmostrar);
	SDL_EnableUNICODE( SDL_DISABLE );
	TTF_CloseFont(font);
	TTF_Quit();
}
