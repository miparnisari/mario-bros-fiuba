#ifndef EXCEPTIONCARGAMENU_H_
#define EXCEPTIONCARGAMENU_H_

using namespace std;

class ExceptionCargaMenu: public exception {
	
	private:
		 string mensaje;
	
	public:
		ExceptionCargaMenu() {
		}

		string what() {
			return "No se pudo crear el menu.";
		}

		~ExceptionCargaMenu() throw () {
		}

};

#endif /* EXCEPTIONCARGAMENU_H_*/
