#ifndef BARRADEESTADO_H_
#define BARRADEESTADO_H_

#include "ComponenteSinImagen.h"
#include "../comun/Mutex.h"

class BarraDeEstado : public ComponenteSinImagen {

	private:
		std::string defaultText;
		std::string textoEstado;
		TTF_Font* font;
		Mutex* mutex;

	public:
		BarraDeEstado(std::string id, int x, int y, int ancho, int alto, std::string unaFont, int fontSize, Mutex* unMut) 
		: ComponenteSinImagen(id, x, y, ancho, alto) {
			this -> defaultText = "Esperando un estado...";
			this -> mutex = unMut;
			textoEstado = defaultText;
			
			TTF_Init();
			SDL_EnableUNICODE(SDL_ENABLE);
	
			font = TTF_OpenFont(unaFont.c_str(), fontSize);
		}
		
		~BarraDeEstado() {
			SDL_EnableUNICODE( SDL_DISABLE );
			TTF_CloseFont(font);
			TTF_Quit();
		}
		
		bool manejarEventos(SDL_Event event) {
			// No hace nada
			return true;
		}
		
		void setText(std::string text) {
			mutex->lock();
			this->textoEstado = text;
			mutex->unlock();
		}
		
		void refrescar(SDL_Surface* destino) {
			mutex->lock();
			SDL_Rect offset = this->box;
			
			// Fondo
			SDL_FillRect(destino, &offset, BEIGE);
			
			// Escribimos el texto
			SDL_Color textColor = translate_color(BLACK);
			SDL_Surface* message = renderizarTexto(this->font, this->textoEstado, textColor);
			SDL_BlitSurface(message, NULL, destino, &offset);
			SDL_FreeSurface(message);
			
			// Pintamos la barrita que separa del resto del menu
			offset = this->box;
			offset.h = 1;
			SDL_FillRect(destino, &offset, BLACK );
			
			SDL_UpdateRect(destino,box.x,box.y,box.w,box.h);
			mutex->unlock();
		}
		
};

#endif /* BARRADEESTADO_H_ */
