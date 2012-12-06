#ifndef EXCEPTIONCONEX_H_
#define EXCEPTIONCONEX_H_
#include <iostream>
#include <exception>
#include <string>
#include <sstream>

using namespace std;

class ExceptionConex: public exception {
	
	private:
		string mensaje;
	
	public:
		ExceptionConex(string unhost) {
			this->mensaje = unhost;
		}

		string what() {
			std::stringstream ss;
			ss << mensaje;
			string s = ss.str();
			return s;
		}

		~ExceptionConex() throw () {
		}

};

#endif /* EXCEPTIONCONEX_H_ */
