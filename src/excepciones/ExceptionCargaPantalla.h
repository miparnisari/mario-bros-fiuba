#ifndef EXCEPTIONCARGAPANTALLA_H_
#define EXCEPTIONCARGAPANTALLA_H_
#include <iostream>
#include <exception>
#include <string>

using namespace std;

class ExceptionCargaPantalla: public exception {
	
	private:
		 string mensaje;
	
	public:
		ExceptionCargaPantalla() {
		}

		string what() {
			return "No se pudo crear la Pantalla.";
		}

		~ExceptionCargaPantalla() throw () {
		}

};

#endif /* EXCEPTIONCARGAPANTALLA_H_*/
