#ifndef PLATAFORMAINCLINADA_H
#define PLATAFORMAINCLINADA_H

//#include "Plataforma.h"
#include "Elemento.h"
#include "Protagonista.h"
#include "../other/Logger.h"
#include "../comun/Definiciones.h"

typedef struct _eje{
	Point direccion;
	Point v1;
	Point v2;
	Point MinMax;
} Eje; 

class Personaje;

class PlataformaInclinada : public Elemento {

	public:
		PlataformaInclinada(Point* unaPos, int ancho, int alto,  int angulo);
		~PlataformaInclinada();
		bool verticeDentro(float xVert, float yVert, Point* p, int ancho, int alto);
		int colisionaCon(Personaje* pers);
		int colisionConPersonaje(Personaje* pers);
		int aplicarColision(Personaje* pers, int res, Point posAnterior);
	private:
		void calcularVertices();
		void calcularEjes();
		static const string TAG;
		// Angulo de rotacion en grados
		int angulo;
		Point supDer;
		Point infDer;
		Point supIzq;
		Point infIzq;
		
		Eje ejeVertical;
		Eje ejeHorizontal;
		list<Eje*> ejes;
};

#endif /* PLATAFORMAINCLINADA_H */
