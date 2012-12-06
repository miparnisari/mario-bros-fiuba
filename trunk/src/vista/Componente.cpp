#include "Componente.h"

using namespace std;

Componente::Componente(string unId, int unX, int unY, int unW, int unH ) {
	box.x = unX;
	box.y = unY;
	box.w = unW;
	box.h = unH;
	this->id = unId;
}

string Componente::getID() {
	return id;
}

string Componente::getData() {
	return "";
}

Componente::~Componente() {
}

SDL_Surface* Componente::renderizarTexto(TTF_Font* fuente, string texto, SDL_Color color) {
// Verifica que el texto no se salga de los margenes laterales del componente.
// Si no es asi devuelve el surface del texto completo.
// Si el texto excede los limites el mismo se devuelve el prefijo mas largo que quepa.
	if (fuente == NULL || texto.empty()) return NULL;

	bool entra = false;
	string textoModificado(texto);

	int anchoTexto, altoTexto;
	while (! entra ) {
		if (TTF_SizeText(fuente,textoModificado.c_str(),&anchoTexto,&altoTexto) == -1) {
			return NULL;
		} else {
			if ( anchoTexto <= (this -> box.w) ) {
				entra = true;
			} else {
				//Tengo que recortar el texto
				textoModificado.assign(textoModificado,0,textoModificado.size()-1);
			}
		} 
	}
	return TTF_RenderText_Solid(fuente, textoModificado.c_str(), color);
}

SDL_Color Componente::translate_color(Uint32 int_color) {
	/*
	 * Fuente:
	 * http://www.gamedev.net/topic/291015-cannot-convert-from-uint32-to-sdl_color/
	 * 
	 */
	SDL_Color color;
 
	if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
		color.r = (int_color & 0x00ff0000)/0x10000;
		color.g = (int_color & 0x0000ff00)/0x100;
		color.b = (int_color & 0x000000ff);
		color.unused = 0;
	} else {
		color.r = (int_color & 0x000000ff);
		color.g = (int_color & 0x0000ff00)/0x100;
		color.b = (int_color & 0x00ff0000)/0x10000;
		color.unused = 0;
	}
	return color;
}
