#ifndef EXCEPTIONPUERTOINVALIDO_H
#define EXCEPTIONPUERTOINVALIDO_H

using namespace std;

class ExceptionPuertoInvalido: public exception {
	
	public:
		ExceptionPuertoInvalido() {
		}

		string what() {
			return "Puerto invalido. Solo deben ser numeros.";
		}

		~ExceptionPuertoInvalido() throw () {
		}

};

#endif /* EXCEPTIONPUERTOINVALIDO_H */
