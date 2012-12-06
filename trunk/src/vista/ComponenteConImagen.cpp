#include "ComponenteConImagen.h"

#include "../excepciones/Excepciones.h"
#include "../other/Logger.h"


using namespace std;

const string ComponenteConImagen::TAG = "ComponenteConImagen";

ComponenteConImagen::ComponenteConImagen(string id, int unX, int unY, int w, int h, string filename) : Componente(id,unX,unY,w,h) {
	this->clip = NULL;
	this->img = cargarImagen(filename);
	if (this->img == NULL){
		Logger::error(TAG,  "No se pudo crear la imagen: " + filename);
		throw ExceptionCargaImagen(filename);
	}
}

SDL_Surface* ComponenteConImagen::cargarImagen( string filename ) {
    SDL_Surface* loadedImage = NULL;
    
    SDL_Surface* optimizedImage = NULL;
    
    loadedImage = IMG_Load( filename.c_str() );
    
    if( loadedImage != NULL )
    {
        optimizedImage = SDL_DisplayFormatAlpha( loadedImage );
        
        SDL_FreeSurface( loadedImage ); 
	}

    return optimizedImage;

}

SDL_Rect* ComponenteConImagen::getCuadro() {
	return clip;
}

SDL_Surface* ComponenteConImagen::getImg() {
	return img;
}

void ComponenteConImagen::refrescar(SDL_Surface* destino) {
	SDL_Rect offset;
	
	// Obtener los offsets del componente
	offset.x = box.x;
	offset.y = box.y;
	offset.w = box.w;
	offset.h = box.h;

	SDL_BlitSurface( this->img, this->clip, destino, &offset );

}

ComponenteConImagen::~ComponenteConImagen() {
	SDL_FreeSurface( img );
}
