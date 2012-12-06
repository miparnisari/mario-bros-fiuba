#ifndef EXCEPTIONSOUNDHANDLER_H_
#define EXCEPTIONSOUNDHANDLER_H_
#include <iostream>
#include <exception>
#include <string>

using namespace std;

class ExceptionSoundHandler: public exception {
	
	private:
		 string mensaje;
	
	public:
		ExceptionSoundHandler() {
		}

		string what() {
			return "No se pudo crear el Sound Handler.";
		}

		~ExceptionSoundHandler() throw () {
		}

};

#endif /* EXCEPTIONSOUNDHANDLER_H_*/
