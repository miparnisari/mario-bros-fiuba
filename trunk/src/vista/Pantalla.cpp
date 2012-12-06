#include "Pantalla.h"
#include "../excepciones/Excepciones.h"

const string Pantalla::TAG = "Pantalla";

Pantalla::Pantalla(int width, int height, int bpp, std::string titulo) {
	
	this->ancho = width;
	this->alto = height;
		
	//Configurar la pantalla
	screen = SDL_SetVideoMode(width, height, bpp, SDL_SWSURFACE );
	
	if (!screen){
		Logger::fatal(TAG, "No se pudo crear la pantalla.");
		throw ExceptionCargaPantalla();
	}
	
	SDL_WM_SetCaption( titulo.c_str() , NULL );
	
}

SDL_Surface* Pantalla::getScreen() {
	return (this->screen);
}


bool Pantalla::refrescar(listaVistas lista, VistasEnemigos map, AnimacionProtagonista* vistaVidas, list<st_VistasBonus*> vistasBonus){
	
	if (lista.empty()) return false;
	
	SDL_Rect offset;
	
	list<Imagen*>::iterator it = lista.begin();
	
	Imagen* vistaNivel = (*it);
	
	offset.x = (vistaNivel->getPos())->x;
	offset.y = (vistaNivel->getPos())->y;
//	std::cout << "VistaNivel:" << (*vistaNivel->getPos()) << "\n";

	SDL_BlitSurface( vistaNivel->getImg(), vistaNivel->getCuadro(), this->screen, &offset );
  
	++it;
	
	while(it != lista.end()) {

		//Obtener los offsets
		
		offset.x = ((*it)->getPos())->x - vistaNivel->getCuadro()->x;
		offset.y = ((*it)->getPos())->y - vistaNivel->getCuadro()->y;
		
		SDL_BlitSurface( (*it)->getImg(), (*it)->getCuadro(), this->screen, &offset );  
		  
    	++it;
   	}

	

	// Dibujo a todos los enemigos
   	for (IterVistasEnemigos iterEnemigos = map.begin() ; iterEnemigos != map.end() ; ++iterEnemigos){
		Imagen* img = iterEnemigos->second;
		offset.x = (img->getPos())->x - vistaNivel->getCuadro()->x;
		offset.y = (img->getPos())->y - vistaNivel->getCuadro()->y;
		SDL_BlitSurface( img->getImg(), img->getCuadro(), this->screen, &offset );  
	} 
	
	for (list<st_VistasBonus*>::iterator it = vistasBonus.begin() ; it != vistasBonus.end() ; ++it){
		if((*it)->activo){
			offset.x = ((*it)->imagen->getPos())->x;
			offset.y = ((*it)->imagen->getPos())->y;
			SDL_BlitSurface( (*it)->imagen->getImg(), (*it)->imagen->getCuadro(), this->screen, &offset );
		}
	}
	
	offset.x = (vistaVidas->getPos())->x;
	offset.y = (vistaVidas->getPos())->y;
	SDL_BlitSurface( vistaVidas->getImg(), vistaVidas->getCuadro(), this->screen, &offset );
	
	return true;
}

const int Pantalla::getAncho(){
	return this->ancho;
}

const int Pantalla::getAlto(){
	return this->alto;
}

Pantalla::~Pantalla(){
	SDL_Quit();
}

void Pantalla::delay(int num){
	SDL_Delay( num );
}
