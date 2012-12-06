#include "EspacioParaTexto.h"

using namespace std;

EspacioParaTexto::EspacioParaTexto(string id, int x, int y, int w, int h)
	: ComponenteSinImagen(id,x,y,w,h)
{	
	TTF_Init();
	SDL_EnableUNICODE(SDL_ENABLE);
	this -> font = TTF_OpenFont(FONT, FONT_SIZE);
}


EspacioParaTexto::~EspacioParaTexto()
{
	SDL_EnableUNICODE( SDL_DISABLE );
	TTF_CloseFont(font);
	TTF_Quit();
}

void EspacioParaTexto::limpiarTexto() {
	this -> texto.clear();
}

void EspacioParaTexto::modificarTexto(vector <ParTexto> nuevoTexto) {
	this -> limpiarTexto();
	this -> texto = nuevoTexto;
}

void EspacioParaTexto::agregarTexto(ParTexto par) {
	this -> texto.push_back(par);
}

void EspacioParaTexto::refrescar(SDL_Surface* destino) {
	SDL_Surface* textoAMostrar = NULL;
	int distancia = (this -> box.h - TTF_FontHeight(this -> font)) / this -> texto.size();
	int incremento = 0;
	string construccion;
	SDL_Color textColor = Componente::translate_color(BLACK);

	//Ahora debemos meter toda la información en el tamaño del recuadro. 
	//La función asegura que no se salgan del limite superior e inferior.
	for (int i=0; i < this -> texto.size(); i++) {
		SDL_Rect offset;
		offset.x = this -> box.x;
		offset.y = (this -> box.y + incremento);
		offset.h = this -> box.h;
		offset.w = this -> box.w;
		construccion = this -> texto[i].first + this -> texto[i].second;
		textoAMostrar = TTF_RenderText_Solid(this -> font, construccion.c_str() , textColor);

		SDL_BlitSurface(textoAMostrar, NULL, destino, &offset);
		SDL_FreeSurface(textoAMostrar);
		incremento += distancia;
	}
}

bool EspacioParaTexto::manejarEventos(SDL_Event event) {
	// No hace nada
	return true;
}
