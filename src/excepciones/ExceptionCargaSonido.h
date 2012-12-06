#ifndef EXCEPTIONCARGASONIDO_H_
#define EXCEPTIONCARGASONIDO_H_
#include <iostream>
#include <exception>
#include <string>
#include <sstream>

using namespace std;

class ExceptionCargaSonido : public exception {
	
	private:
		string mensaje;
		string archivoSonido;
	
	public:
		ExceptionCargaSonido(string archivoSonido) {
			this->mensaje =  "No se pudo cargar el sonido: ";
			this->archivoSonido = archivoSonido;
		}

		string what() {
			std::stringstream ss;
			ss << mensaje << archivoSonido;
			string s = ss.str();
			return s;
		}

		~ExceptionCargaSonido() throw () {
		}

};

#endif /* EXCEPTIONCARGASONIDO_H_ */
