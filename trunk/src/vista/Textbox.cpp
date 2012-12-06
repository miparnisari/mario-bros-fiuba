#include "Textbox.h"

#include "../other/Logger.h"
#include "../excepciones/Excepciones.h"

using namespace std;

const string Textbox::TAG = "Textbox";

Textbox::Textbox(string id, int x, int y, int width, int height, string defaultText, string unaFont, int fontSize) 
: ComponenteSinImagen(id, x, y, width, height) {
	
	TTF_Init();
	SDL_EnableUNICODE(SDL_ENABLE);

	this->active = false;
	this->fullText = defaultText;
	this->defaultText = defaultText;
	this->fontSize = fontSize;
	this->posCursor = box.x;
	this->cursorVisible = false;
	
	this->font = TTF_OpenFont(unaFont.c_str(), fontSize);
	if (! font) {
		Logger::error(TAG, "No se pudo abrir la fuente: " + string(unaFont));
		SDL_EnableUNICODE( SDL_DISABLE );
		TTF_Quit();
		throw ExceptionCargaTTF(unaFont);
	}
	
}

string Textbox::getData() {
	return this->fullText;
}

void Textbox::refrescar(SDL_Surface* destino) {
	if (this->active) {
		this->cursorVisible = true;
	}
	this->drawBox(destino);
	this->drawText(destino);
	if (this->active && this->cursorVisible) {
		this->drawCursor(destino);
	}
}

void Textbox::drawBox(SDL_Surface* destino) {
	// Pinto un bordecito negro
	SDL_Rect border;
	border.x = box.x -1;
	border.y = box.y -1;
	border.w = box.w +2;
	border.h = box.h +2;
	SDL_FillRect(destino, &border, BLACK);
	
	// Pinto el fondo del Textbox
	if (this->active) {
		SDL_FillRect(destino, &box, CYAN);
	}
	else {
		SDL_FillRect(destino, &box, WHITE);
	}
}

void Textbox::drawText(SDL_Surface* destino) {
	/*
	 * BASADO EN: 
	 * http://code.google.com/p/grupotp7542taller1/source/browse/trunk/TanksGame/GraphicComponents/ui/TextBox.cpp
	 * 
	 */
	 
	SDL_Rect boxWindow = this->box;
	SDL_Color textColor = Componente::translate_color(BLACK);
	
	// Si no hay texto y el textBox esta inactivo, ponemos el texto default
	if (this->fullText.empty() && ! this->active) {
		this->fullText = defaultText;
	}
	
	// El mensaje y la ventana que lo va a encuadrar
	SDL_Surface* message = NULL;
	SDL_Rect messageWindow = boxWindow;
	messageWindow.x = 0;
	messageWindow.y = 0;

	int messageWidth = 0;
	int messageHeight = 0;
	
	if (TTF_SizeText(font, fullText.c_str(), &messageWidth, &messageHeight) != -1) {
	
		// Si la longitud del texto es > a la longitud de la Textbox,
		// movemos la ventana sobre el texto para mostrar un sufijo del texto
		if (messageWidth > boxWindow.w ) {
			int dif = messageWidth - boxWindow.w;
			messageWindow.x += dif;
		}
		
		// Movemos el cursor
		if (this->active) {
			this->posCursor = messageWidth + boxWindow.x - messageWindow.x -1;
		}
		
		// Render del mensaje
		message = TTF_RenderText_Solid(font, this->fullText.c_str(), textColor);
		SDL_BlitSurface(message, &messageWindow, destino, &boxWindow);

	}
	SDL_FreeSurface(message);
	
}

void Textbox::drawCursor(SDL_Surface* destino) {
	// El cursor es una linea vertical angosta y alta
	SDL_Rect rect;
	rect.x = this->posCursor + 1;
	rect.y = this->box.y + 1;
	rect.h = fontSize - 1;
	rect.w = 1;
	
	SDL_FillRect(destino, &rect, BLACK);
}

bool Textbox::manejarEventos(SDL_Event event) {
	
	// Si se presiono el boton izquierdo del mouse
	if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
		
		int x = event.button.x;
		int y = event.button.y;
		
		// Si el mouse esta arriba de la Textbox, activamos la Textbox
		if( ( x > box.x ) && ( x < box.x + box.w ) && ( y > box.y ) && ( y < box.y + box.h ) )
			this->active = true;
		else {
			this->active = false;
			return false;
		}
	}
		
	// Si se presiono una tecla y la Textbox estaba activa
	if (event.type == SDL_KEYDOWN && this->active)
	{
		// Si la tecla fue una letra
		if(event.key.keysym.sym >= SDLK_SPACE && event.key.keysym.sym <= SDLK_z)
		{
			// Agregamos el caracter al final
			this->fullText.push_back((char)event.key.keysym.unicode);
		}
		if( (event.key.keysym.sym == SDLK_BACKSPACE) && (! this->fullText.empty()) )
		{
			// Quitamos el caracter del final
			this->fullText.erase(this->fullText.length() - 1);
		}

	}
	
	return true;
}

Textbox::~Textbox() {
	SDL_EnableUNICODE( SDL_DISABLE );
	TTF_CloseFont(font);
	TTF_Quit();
}
