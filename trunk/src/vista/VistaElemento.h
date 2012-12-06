#ifndef VISTAELEMENTO_H
#define VISTAELEMENTO_H

#include "Imagen.h"

class VistaElemento: public Imagen
{
	public:
		VistaElemento(std::string nombreArchivo, Posicionable* elemento, int prior, int tamX, int tamY, ID unID, std::string nombreElem);
		~VistaElemento();
};

#endif /* VISTAELEMENTO_H */ 
