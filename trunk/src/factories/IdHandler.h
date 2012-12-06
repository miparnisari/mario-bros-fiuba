#ifndef IDHANDLER_H
#define IDHANDLER_H

#include "../comun/Definiciones.h"
#include <stdio.h>
class IdHandler
{
	public:
		IdHandler(int cantMax);
		~IdHandler();
		ID asignarID();
			
	private:
		int actual;
		int cantidad;
};
/*

class IdHandler
{
	public:
		IdHandler(int cantMax);
		~IdHandler();
		ID asignarID();
		bool darBaja(ID unID);
			
	private:
		std::vector<bool> Ids;
		int cantidad;
		
};
*/
#endif /* IDHANDLER_H */ 
