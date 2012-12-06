#ifndef VISTAELEMENTOROTADO_H
#define VISTAELEMENTOROTADO_H

#include "Imagen.h"

class VistaElementoRotado: public Imagen
{
	public:
		VistaElementoRotado(std::string nombreArchivo, Posicionable* elemento, int prior, int tamX, int tamY, ID unID, std::string nombreElem, int angulo);
		~VistaElementoRotado();
};

#endif /* VISTAELEMENTOROTADO_H */ 
