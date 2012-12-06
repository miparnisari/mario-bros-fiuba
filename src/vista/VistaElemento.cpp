#include "VistaElemento.h"


VistaElemento::VistaElemento(std::string nombreArchivo, Posicionable* elemento, int prior, int tamX, int tamY, ID unID,std::string nombreElem)
	: Imagen(nombreArchivo, elemento, prior, tamY, tamX, unID, nombreElem)
{
	double factX = this->setFactorXResize(tamX);
	double factY = this->setFactorYResize(tamY);
	this->resizearImg(factX, factY);
}


VistaElemento::~VistaElemento()
{
	SDL_FreeSurface( this->img );
}

