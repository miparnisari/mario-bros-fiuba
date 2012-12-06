#ifndef LOADTEXTURA_H
#define LOADTEXTURA_H
#define ERROR "ERROR"
#include <string>

using namespace std;

class LoadTextura
{
	public:
		LoadTextura();
		virtual ~LoadTextura();
		void setTextura(string param);
		void setFile(string param);
				
		string getTextura();
		string getFile();
		
	
	private:
		string file;
		string textura;
};

#endif /* LOADTEXTURA_H */ 
