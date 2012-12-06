#ifndef LOADANIMACION_H
#define LOADANIMACION_H
#define ERROR "ERROR"
#include <string>
#include <list>

using namespace std;

class LoadAnimacion
{
	public:
		LoadAnimacion();
		virtual ~LoadAnimacion();
		void setOffset(string param);
		void setCantidad(string param);
		void setNombre(string param);
		void setPeriodo(string param);
				
		string getOffset();
		string getCantidad();
		string getNombre();
		string getPeriodo();
		
	
	private:
		string nombre;
		string offset;
		string cantidad;
		string periodo;
		
};

#endif /* LOADPERSONAJE_H */ 
