#ifndef BARRASEPARADORA_H
#define BARRASEPARADORA_H

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

class BarraSeparadora {

	private:
		SDL_Rect box;
		Uint32 colorPintado;
		Uint32 colorDespintado;

	public:
	
		BarraSeparadora(int x, int y, int ancho, int alto, Uint32 pintado, Uint32 despintado) {
			box.x = x;
			box.y = y;
			box.w = ancho;
			box.h = alto;
			colorPintado = pintado;
			colorDespintado = despintado;
		}
		
		~BarraSeparadora() {}
		
		void pintar(SDL_Surface* destino) {
			SDL_FillRect(destino, &box, colorPintado);
		}
		
		void despintar(SDL_Surface* destino) {
			SDL_FillRect(destino, &box, colorDespintado);
		}
};

#endif /* BARRASEPARADORA_H */
