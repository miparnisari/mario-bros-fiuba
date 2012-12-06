#ifndef LOADPERSONAJE_H
#define LOADPERSONAJE_H
#define ERROR "ERROR"
#include <string>
#include <list>
#include "loadAnimacion.h"

using namespace std;

class LoadPersonaje
{
	public:
		LoadPersonaje();
		virtual ~LoadPersonaje();
		void setX(string param);
		void setY(string param);
		void setNombre(string param);
		void setAncho(string param);
		void setAlto(string param);
		void setImagen(string param);
		void setMargenScroll(string param);
		void setVelocidad(string param);
		void setPotenciaSalto(string param);
		void cargarAnimacion(LoadAnimacion* animacion);
		
		string getX();
		string getY();
		string getNombre();
		string getAncho();
		string getAlto();
		string getImagen();
		string getVelocidad();
		string getMargenScroll();
		string getPotenciaSalto();
		
		list<LoadAnimacion*> animaciones;
		
	private:
		string nombre;
		string x,y;
		string ancho,alto;
		string imagen;
		string velocidad;
		string margenScroll;
		string potenciaSalto;
		
};

#endif /* LOADPERSONAJE_H */ 
