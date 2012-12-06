#include "TextureHandler.h"
const string TextureHandler::TAG = "TextureHandler";

TextureHandler::TextureHandler(string tag) {
	texturas = new map<string, string>;
	error = tag;
}


TextureHandler::~TextureHandler() {
	delete texturas;
}

void TextureHandler::addTextura(string tag, string ruta){
	(*texturas)[tag] = ruta;
}

string TextureHandler::getTextura(string tag) {
	if (texturas->find(tag) == texturas->end() ){
		Logger::warn(TAG, "No se encuentra: " + tag);
		if (texturas->find(error) == texturas->end() ){
			Logger::fatal(TAG, "No se encontro la textura error default.");
			throw exception();
		}
		Logger::warn(TAG, "Seteando textura error: " + (*texturas)[error]);
		return ((*texturas)[error]);
	}
	
	return ((*texturas)[tag]);
}
