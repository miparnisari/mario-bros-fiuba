#ifndef EXCEPTIONCARGAMUSICA_H_
#define EXCEPTIONCARGAMUSICA_H_
#include <iostream>
#include <exception>
#include <string>
#include <sstream>

using namespace std;

class ExceptionCargaMusica : public exception {
	
	private:
		string mensaje;
		string archivoMusica;
	
	public:
		ExceptionCargaMusica(string archivoMusica) {
			this->mensaje =  "No se pudo cargar la musica: ";
			this->archivoMusica = archivoMusica;
		}

		string what() {
			std::stringstream ss;
			ss << mensaje << archivoMusica;
			string s = ss.str();
			return s;
		}

		~ExceptionCargaMusica() throw () {
		}

};

#endif /* EXCEPTIONCARGAMUSICA_H_ */
