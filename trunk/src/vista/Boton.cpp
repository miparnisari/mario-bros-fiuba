#include "Boton.h"

#include "../other/Logger.h"
#include "../excepciones/Excepciones.h"

using namespace std;

const string Boton::TAG = "Boton";

// 		Boton(std::string id, int x, int y, int w, int h, EventoBoton* ev, std::string texto, std::string font, int fontSize);

Boton::Boton(string id, int x, int y, int w, int h, EventoBoton* ev, string texto, string font, int fontSize ) 
: ComponenteSinImagen (id, x, y, w, h) {
	box.x = x;
	box.y = y;
	box.w = w;
	box.h = h;
	this->evento = ev;
	this->texto = texto;
	this->active = false;
	
	TTF_Init();
	SDL_EnableUNICODE(SDL_ENABLE);
	
	this->font = TTF_OpenFont(font.c_str(), fontSize);
	if (! this->font) {
		Logger::error(TAG, "No se pudo abrir la fuente: " + font);
		SDL_EnableUNICODE( SDL_DISABLE );
		TTF_Quit();
		throw ExceptionCargaTTF(font);
	}

}

bool Boton::manejarEventos(SDL_Event event) {

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
				this->active = true;
				// Llamo a la funcion que tiene asignado este boton
				if (this->evento) this->evento->actuar();
				return true;
            }
		}
    }
	return false;

}

Boton::~Boton() {
	SDL_EnableUNICODE( SDL_DISABLE );
	TTF_CloseFont(font);
	TTF_Quit();
	delete evento;
}

void Boton::setDimensiones(int x, int y, int w, int h) {
	box.x = x;
	box.y = y;
	box.w = w;
	box.h = h;
}

void Boton::setActive(bool estado) {
	this->active = estado;
}

void Boton::refrescar(SDL_Surface* destino) {
	if (this->active) {
		this->drawPressed(destino);
		this->setActive(false);
	}
	else
		this->drawUnpressed(destino);
}

void Boton::writeText(SDL_Surface* destino) {
	SDL_Color textColor = translate_color(BLACK);
	SDL_Surface* message = renderizarTexto(font, this->texto.c_str(), textColor);
	
	SDL_Rect offset = this->box;
	
	// Escribimos el texto sobre el boton (centrado)
	offset.x = box.x + (box.w - message->w)/2;
	offset.y = box.y + (box.h - message->h)/2;
	
	SDL_BlitSurface(message, NULL, destino, &offset);
	SDL_FreeSurface(message);

}

void Boton::drawPressed(SDL_Surface* destino) {
	SDL_Rect offset = this->box;
	SDL_FillRect(destino, &offset, DARK_GREY);
	this->writeText(destino);
}

void Boton::drawUnpressed(SDL_Surface* destino) {
	SDL_Rect offset = this->box;
	SDL_FillRect(destino, &offset, GREY);
	this->writeText(destino);
}

bool Boton::fuePresionado(SDL_Event event) {
    // Si el mouse fue presionado
    if( event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) 
    {
            // Obtengo los offsets del mouse
            int x = event.button.x;
            int y = event.button.y;

            // Si el mouse esta dentro del boton
            if( ( x > box.x ) && ( x < box.x + box.w ) && ( y > box.y ) && ( y < box.y + box.h ) )
            {
				this->active = true;
                return true;
            }
    }
    
    this->active = false;
    return false;
}
