#ifndef MENSAJE_H_
#define MENSAJE_H_

#include "Definiciones.h"


class Mensaje {
	
	public:
		Mensaje();
		virtual ~Mensaje();
		virtual std::string serializar() const = 0;
		virtual void hidratar(const std::string& datos) = 0;
};

#endif /* MENSAJE_H_ */
