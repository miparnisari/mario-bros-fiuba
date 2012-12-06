#include "VistaElementoRotado.h"


VistaElementoRotado::VistaElementoRotado(std::string nombreArchivo, Posicionable* elemento, int prior, int tamX, int tamY, ID unID,std::string nombreElem, int angulo)
	: Imagen(nombreArchivo, elemento, prior, tamY, tamX, unID, nombreElem)
{
	double factX = this->setFactorXResize(tamX);
	double factY = this->setFactorYResize(tamY);
	this->resizearImg(factX, factY);
	Point* posicion = this->getPos();
	Point posVieja(this->getPos()->x, this->getPos()->y);
	if (angulo != 0){
		//if (0 < angulo and angulo <= 90)
			double radianes = angulo * PI / 180;
		//else if (270 <= angulo and angulo <= 360)
		//	radianes = (360 - angulo) * PI / 180;

		this->rotarImg(angulo);
		if ( angulo > 270){
	//		std::cout << "Pos Inclinada antes de sumar: " << *posicion << "\n";
			posicion->x += sin(radianes) * this->alto;
		} else {
	//		std::cout << "Pos Inclinada antes de sumar: " << *posicion << "\n";
			posicion->y -= sin(radianes) * this->ancho;
		}
	//	std::cout << "Pos Inclinada: " << *posicion << "\n";
	}
	
//	printf("ANCHO: %d\n", this->ancho);
//	printf("ALTO: %d\n", this->alto);
			
		Point supDer;
		Point infDer;
		Point supIzq;
		Point infIzq;
		
	supIzq.x = posVieja.x;
	supIzq.y = posVieja.y;
	double radian = (angulo * PI) / 180;
	
	// Le sumo una vuelta completa
	if (angulo < 0) angulo += 360; 
		
	supDer.x = supIzq.x + cos(radian) * this->ancho;
	supDer.y = supIzq.y - sin(radian) * this->ancho;
	
	infDer.x = supDer.x + sin(radian) * this->alto;
	infDer.y = supDer.y + cos(radian) * this->alto;
	
	infIzq.x = supIzq.x + sin(radian) * this->alto;
	infIzq.y = supIzq.y + cos(radian) * this->alto;	
}


VistaElementoRotado::~VistaElementoRotado()
{
	SDL_FreeSurface( this->img );
}

