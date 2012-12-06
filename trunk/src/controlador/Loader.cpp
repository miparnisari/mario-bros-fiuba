#include "Loader.h"
#include "../app/ControladorApp.h"

#define INVALIDO -1

const string Loader::TAG = "Loader";

string Loader::intToString(int n) {
	ostringstream convert;
	convert << n;
	return convert.str();
} 

int Loader::to_int(char const *s){
     if ( s == NULL || s[0] == '\0' )
		return INVALIDO;
     int res = 0;
     while(*s){
          if ( *s >= '0' && *s <= '9' )
              res = res * 10  + (*s - '0'); 
          else
			  return INVALIDO;
           ++s;
     }
     return res; 
} 


Loader::Loader(std::string archConfig) {
	
	this->parser = NULL;
	this->parserDefecto = NULL;
	
	try { 
		parser = new yamlParser(archConfig);
		if (! parser->existeEtiqueta(parser->doc, "juego")) 
			delete parser;
	} catch(ExceptionIO& e) {
		parser = NULL;
		Logger::error(TAG, "No se encontro archivo " + archConfig);
		ControladorApp::getInstance()->setEstado("No se encontro archivo " + archConfig);
		//throw(e);
	}
}

bool Loader::parserEsNull() {
	return (parser == NULL);
}

Loader::~Loader()
{
	delete(parser);
	delete(parserDefecto);
}

//verifica que el parametro no contenga codigo de error y sea un int
int Loader::validar(std::string v){
	if( v.compare(ERROR) ){
		return to_int(v.c_str());
		}
	return INVALIDO;
}

// Comprueba que alto, ancho, x e y sean enteros validos
void Loader::validarPersonaje(LoadPersonaje* pers, int* ancho, int* alto, int* x, int* y){//LoadPersonaje* persDefault, int* ancho, int* alto, int* x, int* y, int anchoNivel, int altoNivel) {
		
	*ancho = validar(pers->getAncho()); *alto = validar(pers->getAlto());
	*x = validar(pers->getX()); *y = validar(pers->getY());
/*
	if(*ancho == INVALIDO || *alto == INVALIDO || *x == INVALIDO || *y == INVALIDO) 
	{
		if(*ancho == INVALIDO) *ancho = to_int(persDefault->getAncho().c_str());
		if(*alto == INVALIDO) *alto = to_int(persDefault->getAlto().c_str());
		if(*x == INVALIDO) *x = to_int(persDefault->getX().c_str());
		if(*y == INVALIDO) *y = to_int(persDefault->getY().c_str());
	}
	
	if ((*x + *ancho) >= anchoNivel) {
		*x = (anchoNivel/2);
		Logger::warn(TAG, "Se intento crear un personaje fuera del nivel (ancho)");
	}
	if ((*y + *alto) >= altoNivel) {
		*y = (altoNivel/2);
		Logger::warn(TAG, "Se intento crear un personaje fuera del nivel (alto)");
	}
*/		
}

