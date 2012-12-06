#ifndef EXCEPTIONCOMPONENTENOENCONTRADO_H_
#define EXCEPTIONCOMPONENTENOENCONTRADO_H_

using namespace std;

class ExceptionComponenteNoEncontrado: public exception {
	
	public:
		ExceptionComponenteNoEncontrado() {
		}

		string what() {
			return "Componente No Encontrado";
		}

		~ExceptionComponenteNoEncontrado() throw () {
		}

};

#endif /* EXCEPTIONCOMPONENTENOENCONTRADO_H_*/
