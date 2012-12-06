#include "VistaNivel.h"
#include <iostream>

VistaNivel::VistaNivel(std::string nombre, Posicionable* elemento, int scroll, int ancho, int alto, int anchoNivel, int altoNivel, int prior, ID unID, std::string nombrePers)
: Imagen(nombre, elemento, prior, alto, ancho, unID, nombrePers){
	this->visor.x = 0;
	this->visor.y = 0;
	this->visor.w = ancho;
	this->visor.h = alto;
	this->scroll = scroll;

	this->anchoPantalla = ancho;
	this->altoPantalla = alto;

	this->lvlWidth = anchoNivel;
	this->lvlHeight = altoNivel;

	double factX = Imagen::setFactorXResize( lvlWidth );
	double factY = Imagen::setFactorYResize( lvlHeight );
	this->resizearImg( factX, factY );
	// Se tiene que setear con un metodo
	this->protagonista = NULL;
}

VistaNivel::~VistaNivel()
{
	SDL_FreeSurface( this->img );
	delete (this->posicionable);
}

void VistaNivel::set_vistaProt(Imagen* pers){
	this->protagonista = pers;
}

SDL_Rect* VistaNivel::getCuadro(){
	
	if (!protagonista) std::cout << "Protagonista es NUll en vistanivel" << std::endl;
	if ((((protagonista->getPos()->x + protagonista->getAncho()) - visor.x) > (this->anchoPantalla - this->scroll)) && 
	     (protagonista->getPos()->x + this->scroll - protagonista->getAncho() < this->ancho)){

		visor.x += ((protagonista->getPos()->x + protagonista->getAncho()) - visor.x) - (this->anchoPantalla - this->scroll);
		if(visor.x > this->ancho - this->anchoPantalla)
			visor.x = this->ancho - this->anchoPantalla;
			
	}
	
	
	if (((protagonista->getPos()->x - visor.x) < this->scroll ) && 
           (protagonista->getPos()->x + protagonista->getAncho() > this->scroll)){

		visor.x += (protagonista->getPos()->x - visor.x) - this->scroll;
		if(visor.x < 0)
			visor.x = 0;
	}

	if ((((protagonista->getPos()->y + protagonista->getAlto())- visor.y) > (this->altoPantalla - this->scroll)) &&
		 (protagonista->getPos()->y + this->scroll - protagonista->getAlto() < this->alto)){

		visor.y += ((protagonista->getPos()->y  + protagonista->getAlto()) - visor.y) - (this->altoPantalla - this->scroll);
		if(visor.y > this->alto - this->altoPantalla)
			visor.y = this->alto - this->altoPantalla;
	
	}
	
	if (((protagonista->getPos()->y - visor.y) < this->scroll) && 
	    (protagonista->getPos()->y + protagonista->getAlto() > this->scroll)){
		visor.y += (protagonista->getPos()->y - visor.y) - this->scroll;

		if(visor.y < 0)
			visor.y = 0;

	}
	
	Point p(visor.x, visor.y);
//	std::cout << "Pos:" << *(protagonista->getPos()) << std::endl;
//	std::cout << "Visor:" << p << std::endl;
	return &visor;
}

void VistaNivel::setVisor(Point* p){
	visor.x = p->x;
	visor.y = p->y;
}
