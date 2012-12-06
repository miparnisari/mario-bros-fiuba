#ifndef EXCEPTIONANIMATION_H_
#define EXCEPTIONANIMATION_H_
#include <iostream>
#include <exception>
#include <string>
#include <sstream>

using namespace std;

class ExceptionAnimation : public exception {
	
	private:
		string mensaje;
		string nombreArchivo;
	
	public:
		ExceptionAnimation(string nombreArchivo) {
			this->mensaje =  "Error asociado a la animacion: ";
			this->nombreArchivo = nombreArchivo;
		}

		string what() {
			std::stringstream ss;
			ss << mensaje << nombreArchivo;
			string s = ss.str();
			return s;
		}

		~ExceptionAnimation() throw () {
		}

};

#endif /* EXCEPTIONANIMATION_H_ */
