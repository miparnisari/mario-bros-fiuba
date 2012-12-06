#ifndef EXCEPTIONCARGATTF_H_
#define EXCEPTIONCARGATTF_H_
#include <iostream>
#include <exception>
#include <string>
#include <sstream>

using namespace std;

class ExceptionCargaTTF : public exception {
	
	private:
		string mensaje;
		string archivoTTF;
	
	public:
		ExceptionCargaTTF(string archivoTTF) {
			this->mensaje =  "No se pudo cargar la fuente: ";
			this->archivoTTF = archivoTTF;
		}

		string what() {
			std::stringstream ss;
			ss << mensaje << archivoTTF;
			string s = ss.str();
			return s;
		}

		~ExceptionCargaTTF() throw () {
		}

};

#endif /* EXCEPTIONCARGATTF_H_ */
