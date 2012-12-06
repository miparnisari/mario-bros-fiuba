#include "yamlParser.h"

const string yamlParser::TAG = "yamlParser";

using namespace std;

yamlParser::~yamlParser()
{
	fin.close();
}

yamlParser::yamlParser(string nombreArch) {
	this->nombreArchivo = nombreArch;
	fin.open(nombreArch.c_str());
	if (fin.fail()){
		Logger::error(TAG, "No se pudo crear parser asociado al archivo " + nombreArch);
		throw (ExceptionIO(nombreArch));
	}
	try {
		YAML::Parser parser(fin);
		parser.GetNextDocument(this->doc);
	} catch (exception& e){
		Logger::error(TAG, "YAML esta mal formado: " + nombreArch);
		throw ExceptionIO(nombreArch);
	}
	
}

string yamlParser::getNombreArchivo() {
	return this->nombreArchivo;
}	


bool yamlParser::existeEtiqueta(const YAML::Node& node, string tag) {
	if (const YAML::Node *pName = node.FindValue(tag))
		return true;
	return false;
}

string yamlParser::cargar(const YAML::Node& node, string campo){
	string dato;
	try {
		node[campo.c_str()] >> dato;
	} catch (exception& e) {
		Logger::error(TAG, e.what());
		Logger::error(TAG, "No se encontro " + campo + " en el archivo: " + nombreArchivo);
		return ERROR;
	}
	return dato;
}

// Carga de un elemento individual del mapa
void yamlParser::cargarElementoMapa(const YAML::Node& node, LoadElementoMapa* elem) {
	
	elem->setTextura(cargar(node, "textura"));
	elem->setX(cargar(node, "x"));;
	elem->setY(cargar(node, "y"));
	elem->setAlto(cargar(node, "alto"));
	elem->setAncho(cargar(node, "ancho"));
}

// Carga todos los elementos de determinado tag dentro de un vector
vector<LoadElementoMapa*>* yamlParser::cargarElementosVector(std::string tipo){
	
	vector<LoadElementoMapa*>* elementos = new vector<LoadElementoMapa*>;

	if (existeEtiqueta(doc["juego"]["nivel"], tipo)) {
		for(unsigned i = 0 ; i < doc["juego"]["nivel"][tipo].size() ; i++ ) {
			LoadElementoMapa* elem = new LoadElementoMapa();
			cargarElementoMapa (doc["juego"]["nivel"][tipo][i], elem);
			if(!tipo.compare("plataformas")){
				elem->setRozamiento(cargar(doc["juego"]["nivel"][tipo][i], "rozamiento"));	
			}
			if(!tipo.compare("plataformasInclinadas")){
				elem->setAngulo(cargar(doc["juego"]["nivel"][tipo][i], "angulo"));	
			}
			elementos->push_back(elem);
		}
	} else {
		Logger::warn(TAG, "El tag "+tipo+" no fue encontrado.");
	}
   
   return elementos;

}

vector<LoadTextura*>* yamlParser::cargarTexturas(){
	vector<LoadTextura*>* elementos = new vector<LoadTextura*>;
	for(unsigned i = 0 ; i < doc["juego"]["texturas"].size() ; i++ ) {
		LoadTextura* elem = new LoadTextura();
		elem->setTextura(cargar(doc["juego"]["texturas"][i], "textura"));
		elem->setFile(cargar(doc["juego"]["texturas"][i], "file"));
		elementos->push_back(elem);
   }
   
   return elementos;
}

vector<LoadElementoMapa*>* yamlParser::cargarElementos(std::string tipo){
	return cargarElementosVector(tipo);
}

void yamlParser::cargarAnimacion (const YAML::Node& node, LoadAnimacion* animacion) {
	animacion->setNombre(cargar(node, "nombre"));
	animacion->setOffset(cargar(node, "offset"));
	animacion->setCantidad(cargar(node, "cantidad"));
	animacion->setPeriodo(cargar(node, "periodo"));
}

void yamlParser::cargarMusica(list<st_MusicSound*>* lista){
	if (existeEtiqueta(doc["juego"], "musica")) {
		for(unsigned i = 0 ; i < doc["juego"]["musica"].size() ; i++ ) {
			st_MusicSound* musica = new st_MusicSound;
			musica->file = cargar(doc["juego"]["musica"][i], "file");
			musica->tag = cargar(doc["juego"]["musica"][i], "tag");
			musica->tipo = "M";
			lista->push_back(musica);
		}
	} else {
		Logger::warn(TAG, "El tag musica no fue encontrado.");
	}
}

void yamlParser::cargarSonido(list<st_MusicSound*>* lista){
	if (existeEtiqueta(doc["juego"], "sonidos")) {
		for(unsigned i = 0 ; i < doc["juego"]["sonidos"].size() ; i++ ) {
			st_MusicSound* sonido = new st_MusicSound;
			sonido->file = cargar(doc["juego"]["sonidos"][i], "file");
			sonido->tag = cargar(doc["juego"]["sonidos"][i], "tag");
			sonido->tipo = "S";
			lista->push_back(sonido);
		}
	} else {
		Logger::warn(TAG, "El tag sonidos no fue encontrado.");
	}
}

void yamlParser::cargarPantalla (st_Pantalla& pantalla) {
	if (existeEtiqueta(doc["juego"], "pantalla")) {
		pantalla.ancho = cargar(doc["juego"]["pantalla"], "ancho");
		pantalla.alto = cargar(doc["juego"]["pantalla"], "alto");
	}
	else {
		Logger::warn(TAG, "El tag pantalla no fue encontrado.");
	}
}

void yamlParser::cargarPosicion (const YAML::Node& node, st_Posicion& pos) {
	pos.x = cargar(node, "x");
	pos.y = cargar(node, "y");
}

void yamlParser::cargarPersonaje(const YAML::Node& node, LoadPersonaje* personaje ){
	personaje->setAncho(cargar(node,"ancho"));
	personaje->setAlto(cargar(node,"alto"));
	personaje->setImagen(cargar(node,"sprites"));
	if (existeEtiqueta(node, "animaciones")) {
		for(unsigned i = 0 ; i < node["animaciones"].size() ; i++ ) {
			LoadAnimacion* animacion = new LoadAnimacion();
			
			cargarAnimacion (node["animaciones"][i], animacion);
			personaje->cargarAnimacion(animacion);
	   }
	} else {
	Logger::error(TAG, "No se encontro la etiqueta animacion en alguno de los personajes.");
	   throw (ExceptionAnimation("Personaje sin etiqueta animacion"));

	}
}

void yamlParser::cargarProtagonista(const YAML::Node& node, LoadPersonaje* personaje, string pisoY ) {
	personaje->setAncho(cargar(node,"ancho"));
	personaje->setAlto(cargar(node,"alto"));
	
	personaje->setImagen(cargar(node,"sprites"));
	if (existeEtiqueta(node, "animaciones")) {
		for(unsigned i = 0 ; i < node["animaciones"].size() ; i++ ) {
			LoadAnimacion* animacion = new LoadAnimacion();
			
			cargarAnimacion (node["animaciones"][i], animacion);
			personaje->cargarAnimacion(animacion);
	   }
	} else {
	Logger::error(TAG, "No se encontro la etiqueta animacion en alguno de los personajes.");
	   throw (ExceptionAnimation("Personaje sin etiqueta animacion"));

	}
}


void yamlParser::cargarNivel (st_Nivel& nivel) {
	nivel.vida = NULL;
	
	if (existeEtiqueta(doc["juego"], "nivel")) {
		nivel.alto = cargar(doc["juego"]["nivel"], "alto");
		nivel.ancho = cargar(doc["juego"]["nivel"], "ancho");
		nivel.piso = cargar(doc["juego"]["nivel"], "piso");
		nivel.fondo = cargar(doc["juego"]["nivel"], "fondo");
		
		for(unsigned i = 0 ; i < doc["juego"]["nivel"]["personajes"].size() ; i++ ) {
			LoadPersonaje* personaje = new LoadPersonaje();
			
			personaje->setNombre(cargar(doc["juego"]["nivel"]["personajes"][i], "tipo"));
			personaje->setX(cargar(doc["juego"]["nivel"]["personajes"][i], "x"));
			personaje->setY(cargar(doc["juego"]["nivel"]["personajes"][i], "y"));
			personaje->setVelocidad("0");
			personaje->setMargenScroll("0");
			personaje->setPotenciaSalto("0");
			
			if (const YAML::Node *pName = doc["juego"]["tiposPersonaje"].FindValue(personaje->getNombre().c_str())) {
				try {
					cargarPersonaje(doc["juego"]["tiposPersonaje"][personaje->getNombre().c_str()],personaje);
				} catch (ExceptionAnimation& e) {
					Logger::error(TAG, "En el personaje " + personaje->getNombre() + " no contiene la etiqueta animación, no se creara.");
					delete personaje;
					continue;
				}
			}
			else {
				Logger::warn(TAG, "El tag tipo Personaje: " + personaje->getNombre() + " no fue encontrado.");
			}
			nivel.listaPersonajes.push_front(personaje); // afuera se libera esta lista
	   }
		   
		for(unsigned i = 0 ; i < doc["juego"]["nivel"]["protagonistas"].size() ; i++ ) {
			LoadPersonaje* protagonista = new LoadPersonaje();
			
			protagonista->setNombre(cargar(doc["juego"]["nivel"]["protagonistas"][i], "tipo"));
			protagonista->setX(cargar(doc["juego"]["nivel"]["protagonistas"][i], "x"));
			protagonista->setY(cargar(doc["juego"]["nivel"]["protagonistas"][i], "y"));
			protagonista->setVelocidad(cargar(doc["juego"]["nivel"]["protagonistas"][i], "vel_personaje"));
			protagonista->setMargenScroll(cargar(doc["juego"]["nivel"]["protagonistas"][i], "margen_scroll"));
			protagonista->setPotenciaSalto(cargar(doc["juego"]["nivel"]["protagonistas"][i], "potencia_salto"));
			
			if (const YAML::Node *pName = doc["juego"]["tiposProtagonista"].FindValue(protagonista->getNombre().c_str())) {
				try {
					cargarProtagonista(doc["juego"]["tiposProtagonista"][protagonista->getNombre().c_str()],protagonista,nivel.piso);
				} catch (ExceptionAnimation& e) {
					Logger::error(TAG, "En el protagonista " + protagonista->getNombre() + " no contiene la etiqueta animación, no se creara.");
					delete protagonista;
					continue;
				}
			}
			else {
				Logger::warn(TAG, "El tag tipo Protagonista: " + protagonista->getNombre() + " no fue encontrado.");
			}
			nivel.listaProtagonistas.push_front(protagonista); // afuera se libera esta lista
	   }
	   
	   for(unsigned i = 0 ; i < doc["juego"]["nivel"]["enemigos"].size() ; i++ ) {
			LoadPersonaje* enemigo = new LoadPersonaje();
			
			enemigo->setNombre(cargar(doc["juego"]["nivel"]["enemigos"][i], "tipo"));
			enemigo->setVelocidad(cargar(doc["juego"]["nivel"]["enemigos"][i], "vel_enemigo"));
			
			if (const YAML::Node *pName = doc["juego"]["tiposProtagonista"].FindValue(enemigo->getNombre().c_str())) {
				try {
					cargarPersonaje(doc["juego"]["tiposProtagonista"][enemigo->getNombre().c_str()],enemigo);
				} catch (ExceptionAnimation& e) {
					Logger::error(TAG, "En el enemigo " + enemigo->getNombre() + " no contiene la etiqueta animación, no se creara.");
					delete enemigo;
					continue;
				}
			}
			else {
				Logger::warn(TAG, "El tag nivel no fue encontrado.");
		
			} 
			nivel.listaEnemigos.push_front(enemigo);
		}
		
		nivel.vida = new LoadPersonaje();
		nivel.vida->setNombre(cargar(doc["juego"]["nivel"]["vida"], "tipo"));
		nivel.vida->setX(cargar(doc["juego"]["nivel"]["vida"], "x"));
		nivel.vida->setY(cargar(doc["juego"]["nivel"]["vida"], "y"));
		nivel.vida->setVelocidad("0");
		nivel.vida->setMargenScroll("0");
		nivel.vida->setPotenciaSalto("0");
			
		if (const YAML::Node *pName = doc["juego"]["tiposPersonaje"].FindValue(nivel.vida->getNombre().c_str())) {
			try {
				cargarPersonaje(doc["juego"]["tiposPersonaje"][nivel.vida->getNombre().c_str()],nivel.vida);
			} catch (ExceptionAnimation& e) {
				Logger::error(TAG, "En el personaje " + nivel.vida->getNombre() + " no contiene la etiqueta animación, no se creara.");
				delete nivel.vida;
			}
		}
		else {
			Logger::warn(TAG, "El tag tipo Personaje: " + nivel.vida->getNombre() + " no fue encontrado.");
		}
	  
	}
}

void yamlParser::getDirYPuertoHost(ParTexto* datos) {
	datos->first = this -> cargar(doc["cliente"], "direccion");
	datos->second = this -> cargar(doc["cliente"], "puerto");
}

void yamlParser::getCantClientes(string* data) {
	*data = this -> cargar(doc["servidor"], "cantidadClientes");
}

void yamlParser::getElementos(string tag, vector <std::string>* elementos) {
	try {
		for (int i = 0; i < doc[tag].size(); i++) {
			std::string e;
			doc[tag][i] >> e;
			elementos -> push_back(e);
		}
	} catch (exception& e) {
		Logger::error(TAG, "No se encuentran los elementos.");
	}
}

void yamlParser::getPuertoServidor(std::string* puerto) {
	*puerto = this -> cargar(doc["servidor"], "puerto");
}

void yamlParser::getNiveles(vector <std::string>* niveles) {
	try {
		for (int i = 0; i < doc["niveles"].size(); i++) {
			std::string nivel;
			doc["niveles"][i] >> nivel;
			niveles -> push_back(nivel);
		}
	} catch (exception& e) {
		Logger::error(TAG, "No se encuentran los niveles disponibles");
		niveles -> push_back("Error en carga de niveles");
	}
}
