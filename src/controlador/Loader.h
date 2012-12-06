#ifndef LOADER_H
#define LOADER_H

#include "yamlParser.h"
#include "../other/Logger.h"
#include "../modelo/Nivel.h"
#include "../vista/VistaNivel.h"
#include "../vista/VistaElemento.h"
#include "../factories/FactoryPantalla.h"
#include "../modelo/PersonajeAnimado.h"
#include "../modelo/Protagonista.h"
#include "../modelo/Elemento.h"
#include "../controlador/TextureHandler.h"
#include "TiposDeDatos.h"
#include "../vista/AnimacionProtagonista.h"
#include "../vista/AnimacionAuto.h"
#include "../excepciones/Excepciones.h"
#include <vector>
#include <list>

class Loader
{
	public:
		Loader(std::string archConfig);
		virtual ~Loader();
		
		bool parserEsNull();
		
	private:
				
	protected:
		yamlParser* parser;
		yamlParser* parserDefecto;
		static const string TAG;
		string intToString(int n);
		
		int to_int(char const *s);
		int validar(std::string v);
	//	void validarPersonaje(LoadPersonaje* pers,LoadPersonaje* persDefault, int* ancho, int* alto, int* x, int* y, int anchoNivel, int altoNivel);
		void validarPersonaje(LoadPersonaje* pers, int* ancho, int* alto, int* x, int* y);
};

#endif /* LOADER_H */ 
