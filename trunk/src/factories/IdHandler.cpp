#include "IdHandler.h"


IdHandler::IdHandler(int cantMax)
{
	cantidad = cantMax;
	actual = 0;
}

ID IdHandler::asignarID(){
	if (actual == cantidad) actual = 1;
	else actual++;
	return actual;
}

IdHandler::~IdHandler() {
}



/*
IdHandler::IdHandler(int cantMax)
{
	cantidad = cantMax;
	
	// Todos los ID arrancan en validos
	for (int i = 0; i < cantMax; i++)
		Ids.push_back(true);
}

IdHandler::~IdHandler() {
	Ids.clear();
}

ID IdHandler::asignarID(){
	
	bool IDencontrado = false;
	int i = 0;
	while (i < cantidad and !IDencontrado){
		if (Ids[i] == true){
			IDencontrado = true;
			Ids[i] = false;
		}
		
		else i++;
	}
	
	if (!IDencontrado){
		// Reseteo Ids
		for (int j = 0; j < cantidad; j++)
			Ids[j] = true;
		i = 0;
	}

	return i;
	// No hay ID disponible
	//return ID_INVALIDO;


}

bool IdHandler::darBaja(ID unID){
	if (unID < cantidad and unID >= 0)
		Ids[unID] = true;
}

*/
