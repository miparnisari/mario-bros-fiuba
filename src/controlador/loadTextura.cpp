#include "loadTextura.h"


LoadTextura::LoadTextura() {
	textura = ERROR;
	file = ERROR;
}

void LoadTextura::setTextura(string param){
	textura = param;
}
void LoadTextura::setFile(string param){
	file = param;
}

string LoadTextura::getTextura(){
	return textura;
}

string LoadTextura::getFile(){
	return file;
}


LoadTextura::~LoadTextura()
{
	
}

