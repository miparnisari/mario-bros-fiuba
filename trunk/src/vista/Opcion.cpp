#include "Opcion.h"
#include "../other/Logger.h"
#include "../excepciones/Excepciones.h"

#define FONTHEIGHT 16

using namespace std;

const string Opcion::TAG = "Opcion";

Opcion::Opcion(string id, string unaFont, int fontSize)
	: ComponenteSinImagen(id,0,0,0,0)
{
	TTF_Init();
	SDL_EnableUNICODE(SDL_ENABLE);
	
	this->seleccionada = false;
	this->texto = id;
	this->fontName = unaFont;
	this->datosAsociados = NULL;
	this->animAsociada = NULL;
	
	this->font = TTF_OpenFont(fontName.c_str(), fontSize);
	if (! font) {
		Logger::error(TAG, "No se pudo abrir la fuente: " + fontName);
		throw ExceptionCargaTTF(fontName);
	}
	
}

const bool Opcion::estaSeleccionada() {
	return (this->seleccionada);
}

void Opcion::setDatosAsociados(int x, int y, int w, int h, vector <ParTexto> datos) {
	this -> datosAsociados = new EspacioParaTexto("Texto para opciones", x, y, w, h);
	this -> datosAsociados -> modificarTexto(datos);
}

void Opcion::setAnimAsociada(int x, int y, int w, int h, string nomArch, vector<st_Animacion*> vectorAnims, std::string nombrePers) {
	// El ancho y el alto deben ser los de un frame de la animacion
	string new_Id = (this->id).append ("_ANIMASOCIADA");
	this->animAsociada = new EspacioParaDibujar (new_Id, x, y, w, h);
	this->animAsociada->setAnimacion (w, h, nomArch, vectorAnims, nombrePers);
}

void Opcion::setDimensiones(int unX, int unY, int unW, int unH) {
	this->box.x = unX;
	this->box.y = unY;
	this->box.w = unW;
	this->box.h = unH;
}

void Opcion::refrescar(SDL_Surface* destino) {
	SDL_Color textColor = Componente::translate_color(BLACK);
	this->textoAmostrar = renderizarTexto(this->font, this->texto, textColor);
	// Dibujamos la opcion
	if (this->seleccionada) {
		SDL_FillRect(destino, &this->box, CYAN);
		
		// Dibujamos la animacion asociada (si la hay)
		if (this->animAsociada) {
			this->animAsociada->refrescar(destino);
		}
		
		// Escribimos los datos asociados a la opcion (si los hay)
		//Los datos están en la opción así que sólo hay que refrescarlos.
		if (this->datosAsociados) {
			this->datosAsociados->refrescar(destino);
		}
	}
	SDL_BlitSurface(this->textoAmostrar, NULL, destino, &this->box);
	SDL_FreeSurface(this->textoAmostrar);
}

bool Opcion::manejarEventos(SDL_Event event) {
	// Si se presiono el boton izquierdo del mouse
	if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
		
		int x = event.button.x;
		int y = event.button.y;
		
		// Si el mouse esta arriba de la Opcion, la marcamos como seleccionada
		if( ( x > box.x ) && ( x < box.x + box.w ) && ( y > box.y ) && ( y < box.y + box.h ) )
			this->seleccionada = true;
		else
			this->seleccionada = false;
	}
	
	return true;
}

string Opcion::getData() {
	return (this->texto);
}

void Opcion::seleccionar() {
	this -> seleccionada = true;
}

void Opcion::desmarcar() {
	this -> seleccionada = false;
}

void Opcion::setAncho(int ancho) {
	this -> box.w = ancho;
}

Opcion::~Opcion() {
	if (datosAsociados) delete (datosAsociados);
	if (animAsociada) delete (animAsociada);
	
	SDL_EnableUNICODE( SDL_DISABLE );
	TTF_CloseFont(font);
	TTF_Quit();
}
