#ifndef LOADELEMENTOMAPA_H
#define LOADELEMENTOMAPA_H
#define ERROR "ERROR"
#include <string>

using namespace std;

class LoadElementoMapa
{
	public:
		LoadElementoMapa();
		virtual ~LoadElementoMapa();
		void setX(string param);
		void setY(string param);
		void setTextura(string param);
		void setAlto(string param);
		void setAncho(string param);
		void setRozamiento(string param);
		void setAngulo(string angulo);
				
		string getX();
		string getY();
		string getAncho();
		string getAlto();
		string getTextura();
		string getRozamiento();
		string getAngulo();
	
	private:
		string x, y, textura, alto, ancho, rozamiento, angulo;
	
};

#endif /* LOADELEMENTOMAPA_H */ 
