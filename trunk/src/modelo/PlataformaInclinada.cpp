#include "PlataformaInclinada.h"

const string PlataformaInclinada::TAG = "PlataformaInclinada";

PlataformaInclinada::PlataformaInclinada(Point* unaPos, int ancho, int alto, int angulo):  Elemento(unaPos) {
	this->angulo = angulo;
	this->ancho = ancho;
	this->alto = alto;
	calcularVertices();
	calcularEjes();
}

PlataformaInclinada::~PlataformaInclinada(){
	list<Eje*>::iterator it;
	for (it = ejes.begin(); it != ejes.end(); ++it) {
		delete(*it);
	}
	ejes.clear();
}

int PlataformaInclinada::aplicarColision(Personaje* pers, int res, Point posAnterior){
	
	Point pV = posAnterior.proyectar(&(ejeVertical.direccion));
	double VpV = ejeVertical.direccion.dotProduct(&pV);
	
	Point pH = posAnterior.proyectar(&(ejeHorizontal.direccion));
	double VpH = ejeHorizontal.direccion.dotProduct(&pH);

	bool arriba = (VpV < ejeVertical.MinMax.x);
	bool derecha = (VpH > ejeHorizontal.MinMax.y);

	if (0 < angulo and angulo < 90){

		if (arriba and !derecha){ 
			
			pers->getMovimiento()->getPos()->y = posAnterior.y;
			pers->getMovimiento()->setSaltando(false);
			pers->getMovimiento()->sePuedeSaltar = true;
			pers->getMovimiento()->detenerCaida();
			if (pers->getPos()->x > posAnterior.x) pers->getMovimiento()->getPos()->y -= 0.5;

		} else if (!arriba and !derecha) {
			pers->getMovimiento()->getPos()->y = posAnterior.y; //+ 1;
			pers->getMovimiento()->getPos()->x = posAnterior.x;
			if (pers->getMovimiento()->getPos()->x < posAnterior.x){ //+ 1;
				pers->getMovimiento()->caer();
			}
		}

		else if (derecha and arriba){
			
			pers->getMovimiento()->setSaltando(false);
			pers->getMovimiento()->sePuedeSaltar = true;
			pers->getMovimiento()->detenerCaida();
			pers->getMovimiento()->getPos()->y = posAnterior.y;
			// Se esta moviendo a la izquierda
			if (this->infDer.y < posAnterior.y + pers->getAlto()){
				pers->getMovimiento()->getPos()->x = posAnterior.x + 0.5;
				pers->getMovimiento()->getPos()->y = posAnterior.y + 0.5;
			} else if (pers->getMovimiento()->getPos()->x < posAnterior.x){
				pers->getMovimiento()->getPos()->x = posAnterior.x;
				pers->getMovimiento()->getPos()->y -= 1.5 ; // TODO segun angulo
			}

		} else if (derecha and !arriba){
		
			pers->getMovimiento()->setSaltando(false);
			
			if (this->infDer.y > posAnterior.y ){
				
				pers->getMovimiento()->getPos()->x = posAnterior.x + 0.5;
				pers->getMovimiento()->getPos()->y = posAnterior.y + 0.5;
			}
		}
	}
	
	else if (360 > angulo and angulo > 270){
		
		//printf("VpV %f, VpH %f\n", VpV, VpH);
		
		arriba = (VpH < ejeHorizontal.MinMax.x);
		derecha = (VpV < ejeVertical.MinMax.y);
	
		if (!arriba and !derecha){	
		
			pers->getMovimiento()->getPos()->y = posAnterior.y; //+ 1;
			pers->getMovimiento()->getPos()->x = posAnterior.x;
			if (pers->getMovimiento()->getPos()->x > posAnterior.x){ //+ 1;
				pers->getMovimiento()->caer();
			}
		} if (arriba and !derecha){

		} if (arriba){
			pers->getMovimiento()->getPos()->y = posAnterior.y;
			if ( this->infIzq.y > posAnterior.y + pers->getAlto() and pers->getMovimiento()->getPos()->x > posAnterior.x){
				pers->getMovimiento()->getPos()->x = posAnterior.x;
				
				pers->getMovimiento()->getPos()->y -= 1.5 ; // TODO segun angulo
				pers->getMovimiento()->setSaltando(false);
				pers->getMovimiento()->sePuedeSaltar = true;
				pers->getMovimiento()->detenerCaida();
			}
			else if (this->infIzq.y > posAnterior.y + pers->getAlto() or derecha){
			
				pers->getMovimiento()->setSaltando(false);
				pers->getMovimiento()->sePuedeSaltar = true;
				pers->getMovimiento()->detenerCaida();
				if (pers->getMovimiento()->getPos()->x < posAnterior.x){
					
					pers->getMovimiento()->getPos()->y -= 1.5 ; // TODO segun angulo
				} else pers->getMovimiento()->getPos()->x = posAnterior.x;

			} else{
				
				pers->getMovimiento()->detenerCaida();
				pers->getMovimiento()->getPos()->x = posAnterior.x - 1.5;
				pers->getMovimiento()->getPos()->y = posAnterior.y + 1.5;
			}
		}
		if (!arriba and derecha){
			;
			pers->getMovimiento()->getPos()->y = posAnterior.y;
			
			pers->getMovimiento()->setSaltando(false);
			pers->getMovimiento()->sePuedeSaltar = true;
			pers->getMovimiento()->detenerCaida();
			if (pers->getMovimiento()->getPos()->x < posAnterior.x){
				
				pers->getMovimiento()->getPos()->y -= 1.5 ; // TODO segun angulo
			} else pers->getMovimiento()->getPos()->x = posAnterior.x;
		}
	}
	
	return 0;
}

int PlataformaInclinada::colisionaCon(Personaje* pers){
	 /*- Tengo que revisar para todos los ejes las proyecciones de 
	 * los 4 puntos del protagonista, para ver si la menor ( y la mayor) 
	 * proyeccion caen dentro del rango de colision. */
	
	// 4 vertices del personaje
	//printf("COLISIONAR PLATAFORMA INCLINADA\n");
//		printf("CHEQUEO COLISION SAT \n");
	
	Point perSupIzq(pers->getPos()->x,pers->getPos()->y);
	Point perSupDer(pers->getPos()->x + pers->getAncho(), pers->getPos()->y);
	Point perInfIzq(pers->getPos()->x,pers->getPos()->y + pers->getAlto() );
	Point perInfDer(pers->getPos()->x + pers->getAncho(), pers->getPos()->y + pers->getAlto());
/*	
	printf ("VERTICES Protagonista\n");
	std::cout << "perSupIzq: " << perSupIzq << "\n";
	std::cout << "persupDer: " << perSupDer << "\n";
	std::cout << "perinfDer: " << perInfDer << "\n";
	std::cout << "perinfIzq: " << perInfIzq << "\n";
	
	printf ("Size Ejes %d \n", ejes.size());*/
	for(list<Eje*>::iterator eje = ejes.begin(); eje != ejes.end(); ++eje){
		bool proyeccionesDentro = false;
		// Proyecto los vertices sobre un eje
		Point proyecSupIzq = perSupIzq.proyectar(&((*eje)->direccion));
		Point proyecSupDer = perSupDer.proyectar(&((*eje)->direccion));
		Point proyecInfIzq = perInfIzq.proyectar(&((*eje)->direccion));
		Point proyecInfDer = perInfDer.proyectar(&((*eje)->direccion));
	/*
		std::cout << "proyecSupIzq: " << proyecSupIzq << "\n";
		std::cout << "proyecSupDer: " << proyecSupDer << "\n";
		std::cout << "proyecInfIzq: " << proyecInfIzq << "\n";
		std::cout << "proyecInfDer: " << proyecInfDer << "\n";*/
		
		// Producto escalar de las proyecciones sobre el (*eje)
		double VproyecSupIzq = (*eje)->direccion.dotProduct(&proyecSupIzq);
		double VproyecSupDer = (*eje)->direccion.dotProduct(&proyecSupDer);
		double VproyecInfIzq = (*eje)->direccion.dotProduct(&proyecInfIzq);
		double VproyecInfDer = (*eje)->direccion.dotProduct(&proyecInfDer);
		
/*		std::cout << "Min: " << (*eje)->min << " , Max: " << (*eje)->max << "\n";
		std::cout << "VproyecSupIzq: " << VproyecSupIzq << "\n";
		std::cout << "VproyecSupDer: " << VproyecSupDer << "\n";
		std::cout << "VproyecInfIzq: " << VproyecInfIzq << "\n";
		std::cout << "VproyecInfDer: " << VproyecInfDer << "\n"; */
			
		if ((*eje)->MinMax.x < VproyecSupIzq and VproyecSupIzq < (*eje)->MinMax.y) proyeccionesDentro = true;
		if ((*eje)->MinMax.x < VproyecSupDer and VproyecSupDer < (*eje)->MinMax.y) proyeccionesDentro = true;
		if ((*eje)->MinMax.x < VproyecInfIzq and VproyecInfIzq < (*eje)->MinMax.y) proyeccionesDentro = true;
		if ((*eje)->MinMax.x < VproyecInfDer and VproyecInfDer < (*eje)->MinMax.y) proyeccionesDentro = true;
		
		// Si ningun eje se encuentra contenido en el rango
		// de cualquier eje, entonces no estan colisionando.
//			printf("NO COLISION SAT \n");
		if (!proyeccionesDentro) return 0;
	}
	

	// solo sale si algun eje no colisiona, entonces hay colision
	return 1;
}

bool PlataformaInclinada::verticeDentro(float xVert, float yVert, Point* p, int ancho, int alto){
	/* Compruebo si la proyeccion del punto en cada uno de mis ejes
	 * se encuentra dentro del rango de la figura, entonces hay colison.
	 * Algoritmo SAT (Separation of Axis Theorem): */
	return true;
}

void PlataformaInclinada::calcularVertices(){

	supIzq.x = posicion->x;
	supIzq.y = posicion->y;
	double radian = (angulo * PI) / 180;
	
	// Le sumo una vuelta completa
//	if (angulo < 0) angulo += 360; 
		
	supDer.x = supIzq.x + cos(radian) * this->ancho;
	supDer.y = supIzq.y - sin(radian) * this->ancho;
	
	infDer.x = supDer.x + sin(radian) * this->alto;
	infDer.y = supDer.y + cos(radian) * this->alto;
	
	infIzq.x = supIzq.x + sin(radian) * this->alto;
	infIzq.y = supIzq.y + cos(radian) * this->alto;	

   
}

void PlataformaInclinada::calcularEjes(){
	
	
	// Cargo los puntos que generan los ejes
	ejeVertical.v1 = supIzq;
	ejeVertical.v2 = infIzq;
	ejeVertical.direccion = supIzq.segmento(&infIzq);
	ejeHorizontal.v1 = supIzq;
	ejeHorizontal.v2 = supDer;
	ejeHorizontal.direccion = supIzq.segmento(&supDer);

	// Agrego ejes a la lista
	ejes.push_back(&ejeVertical);
	ejes.push_back(&ejeHorizontal);

	
	for(list<Eje*>::iterator eje = ejes.begin(); eje != ejes.end(); ++eje){
		//proyecto los valores que crearon el segmento
		// y guardo sus valores para comparar cuando proyecte a personaje
		/*std::cout << "ANTES DE PROYETAR" << "\n";
		std::cout << "V1: " << eje->v1 << "\n";
		std::cout << "V2: " << eje->v2 << "\n";*/
		
		(*eje)->v1 = (*eje)->v1.proyectar(&((*eje)->direccion));
		(*eje)->v2 = (*eje)->v2.proyectar(&((*eje)->direccion));
		double a = (*eje)->direccion.dotProduct(&((*eje)->v1));
		double b = (*eje)->direccion.dotProduct(&((*eje)->v2));
		
		// Rango dentro del cual deben caer las proyecciones de los
		// vertices de los protagonistas para colisionar
		if (a > b){
			(*eje)->MinMax.x = b;
			(*eje)->MinMax.y = a;
		} else {
			(*eje)->MinMax.x = a;
			(*eje)->MinMax.y = b;
		}

	}
}

int PlataformaInclinada::colisionConPersonaje(Personaje* pers){
	return false;
}
