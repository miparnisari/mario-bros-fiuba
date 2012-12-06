#ifndef EXCEPTIONIO_H_
#define EXCEPTIONIO_H_
#include <iostream>
#include <exception>
#include <string>
#include <sstream>

using namespace std;

class ExceptionIO : public exception {
	
	private:
		string mensaje;
		string nombreArchivo;
	
	public:
		ExceptionIO(string nombreArchivo) {
			this->mensaje =  "No se pudo abrir el archivo: ";
			this->nombreArchivo = nombreArchivo;
		}

		string what() {
			std::stringstream ss;
			ss << mensaje << nombreArchivo;
			string s = ss.str();
			return s;
		}

		~ExceptionIO() throw () {
		}

};

#endif /* EXCEPTIONIOH_ */
