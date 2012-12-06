#ifndef YAMLPARSER_H_
#define YAMLPARSER_H_

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <yaml-cpp/yaml.h>
#include "TiposDeDatos.h"
#include "loadElementoMapa.h"
#include "../comun/Definiciones.h"
#include <fstream>
#include <string>
#include <vector>
#include "../other/Logger.h"
#include "loadTextura.h"
#include "loadElementoMapa.h"
#include <exception>
#include "../excepciones/Excepciones.h"

#define ERROR "ERROR"

class yamlParser
{
	private:
		
		YAML::Node juego;
		ifstream fin;
		std::string nombreArchivo;
		static const std::string TAG;
		
		string cargar(const YAML::Node& node, std::string campo);

	public:
        YAML::Node doc;
		yamlParser(string nombreArch);
		~yamlParser();
		vector<LoadTextura*>* cargarTexturas();
		void cargarAnimacion (const YAML::Node& node, LoadAnimacion* animacion);
		void cargarPantalla (st_Pantalla& pantalla); 
		void cargarPosicion (const YAML::Node& node, st_Posicion& pos);
		void cargarNivel (st_Nivel& nivel);
		void cargarParametros (st_Parametros& parametros);
		void cargarPersonaje(const YAML::Node& node, LoadPersonaje* personaje );
		void cargarProtagonista(const YAML::Node& node, LoadPersonaje* personaje, string pisoY );
		void cargarMusica(list<st_MusicSound*>* lista);
		void cargarSonido(list<st_MusicSound*>* lista);
		void cargarElementoMapa(const YAML::Node& node, LoadElementoMapa* elem);
		vector<LoadElementoMapa*>* cargarElementosVector(std::string tipo);
		vector<LoadElementoMapa*>* cargarElementos(std::string tipo);
		bool existeEtiqueta(const YAML::Node& node, std::string tag);
		void getDirYPuertoHost(ParTexto* datos);
		void getElementos(string tag, vector <std::string>* elementos);
		void getPuertoServidor(std::string* puerto);
		void getCantClientes(string* data);
		void getNiveles(vector <std::string>*);
		string getNombreArchivo();

};

#endif /*YAMLPARSER_H_*/
