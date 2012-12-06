#ifndef EXCEPTIONCARGAIMAGEN_H_
#define EXCEPTIONCARGAIMAGEN_H_
#include <iostream>
#include <exception>
#include <string>
#include <sstream>

using namespace std;

class ExceptionCargaImagen : public exception {
	
	private:
		string mensaje;
		string nombreArchivoImagen;
	
	public:
		ExceptionCargaImagen(string nombreArchivo) {
			this->mensaje =  "No se pudo cargar la imagen: ";
			this->nombreArchivoImagen = nombreArchivo;
		}

		string what() {
			std::stringstream ss;
			ss << mensaje << nombreArchivoImagen;
			string s = ss.str();
			return s;
		}

		~ExceptionCargaImagen() throw () {
		}

};

#endif /* EXCEPTIONCARGAIMAGEN_H_ */
