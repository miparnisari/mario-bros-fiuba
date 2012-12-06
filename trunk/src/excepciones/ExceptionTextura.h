#ifndef EXCEPTIONTEXTURA_H_
#define EXCEPTIONTEXTURA_H_
#include <iostream>
#include <exception>
#include <string>
#include <sstream>

using namespace std;

class ExceptionTextura : public exception {
	
	private:
		string mensaje;
		string nombreTextura;
	
	public:
		ExceptionTextura(string nombreTextura) {
			this->mensaje =  "Error asociado a la textura: ";
			this->nombreTextura = nombreTextura;
		}

		string what() {
			std::stringstream ss;
			ss << mensaje << nombreTextura;
			string s = ss.str();
			return s;
		}

		~ExceptionTextura() throw () {
		}

};

#endif /* EXCEPTIONTEXTURA_H_ */
