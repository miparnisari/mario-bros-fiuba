#ifndef TEXTBOX_H_
#define TEXTBOX_H_

#include "ComponenteSinImagen.h"
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "../comun/Definiciones.h"

class Textbox : public ComponenteSinImagen {
	
	private:
		static const std::string TAG;
		int 		posCursor;
		int 		fontSize;
		bool 		active;
		bool 		cursorVisible;
		std::string fullText;
		std::string defaultText;
		TTF_Font* 	font;
		
		void drawBox(SDL_Surface* destino);
		void drawText(SDL_Surface* destino);
		void drawCursor(SDL_Surface* destino);

	public:
		Textbox(std::string id, int posX, int posY, int width, int height, std::string defaultText, std::string font, int fontSize);
		~Textbox();
		
		bool manejarEventos(SDL_Event event);
		void refrescar(SDL_Surface* destino);
		
		std::string getData();

};

#endif /* TEXTBOX_H_ */
