#include "loaderServidor.h"
#include "../vista/Imagen.h"
#include "../modelo/Elemento.h"
#include "../modelo/Escalera.h"
#include "../modelo/Plataforma.h"
#include "../modelo/PlataformaInclinada.h"
#include "../modelo/Mono.h"
#include "../modelo/Princesa.h"
#include "../modelo/CamaElastica.h"
#include "../modelo/Pow.h"
#include "../factories/Canieria.h"
#include "../modelo/Fuego.h"
#include "../modelo/CajaBonus.h"
#include "loaderServidor.h"
#include <iostream>
#define MAXPANT 2000
#define MINPANT 200
#define INVALIDO -1

const string LoaderServidor::TAG = "LoaderServidor";


LoaderServidor::LoaderServidor(std::string archConfig) : Loader(archConfig){
	listaEnemigos = new list<LoadPersonaje*>;
}

LoaderServidor::~LoaderServidor() {
	for (IterPersonajes it = listaEnemigos->begin(); it != listaEnemigos->end(); ++it) {
		delete(*it);
	}
	listaEnemigos->clear();

}

void LoaderServidor::cargarElementosJuego(Nivel* nivel) {
	/* Idea: Creo un map en donde hago pares Textura: Ruta de imagen
	 * Cuando tengo que cargar la lista elemtos del mapa, les paso el map
	 * para que sepan a que ruta ir su buscar su imagen */
	
	vector<LoadTextura*>* datos = this->parser->cargarTexturas();
	TextureHandler* handler = new TextureHandler("texturaError");
	this->cargarTexturas(*datos, *handler);
	cargarElementosLista( "plataformas", *handler, nivel);
	cargarElementosLista( "escaleras", *handler, nivel);
	cargarElementosLista( "canierias", *handler, nivel);
	cargarElementosLista( "plataformasInclinadas", *handler, nivel);
	cargarElementosLista( "trampolines", *handler, nivel);
	cargarElementosLista( "pow", *handler, nivel);
	cargarElementosLista( "cajaBonus", *handler, nivel);
	
	delete datos;
	delete handler;
}

void LoaderServidor::cargarTexturas(vector<LoadTextura*>& texturas, TextureHandler& handler){
	vector<LoadTextura*>::iterator it;
	
	for ( it = texturas.begin() ; it < texturas.end(); ++it ){
		if ( (!(*it)->getTextura().compare(ERROR)) || (!(*it)->getFile().compare(ERROR)) ){
			Logger::error(TAG, "Error al cargar textura.");
			Logger::debug(TAG,"textura: " + (*it)->getTextura());
			Logger::debug(TAG,"file: " + (*it)->getFile());
		} else {
			handler.addTextura((*it)->getTextura(), (*it)->getFile());
		}
		delete (*it); // Libero lo apuntado por LoadTextura* (pedido en el parser)
	}
}

void LoaderServidor::cargarElementosLista( std::string tipo, TextureHandler& handler , Nivel* nivel) {
		
	IdHandler* idHandlerCanierias = new IdHandler(50);
	vector<LoadElementoMapa*>* elementos = this->parser->cargarElementosVector(tipo);
	vector<LoadElementoMapa*>::iterator it;
	for ( it = elementos->begin() ; it < elementos->end(); ++it){
		int x, y, ancho, alto;
		float rozamiento;

		x = validar((*it)->getX().c_str());
		y = validar((*it)->getY().c_str());
		ancho = validar((*it)->getAncho().c_str());
		alto = validar((*it)->getAlto().c_str());
		Canieria* can = NULL;
		Escalera* esc = NULL;
		Plataforma* plat = NULL;
		PlataformaInclinada* platInc = NULL;
		CamaElastica* cama = NULL;
		
		
		
		if (tipo == "canierias"){
			can = new Canieria(new Point(x ,y), ancho, alto,  nivel, idHandlerCanierias);
			nivel->agregarElemento(can);
		}else if (tipo == "escaleras"){
			esc = new Escalera(new Point(x ,y), ancho, alto);
			nivel->agregarElemento(esc);
		}else if(tipo == "plataformas"){
			rozamiento = atof((*it)->getRozamiento().c_str());
			plat = new Plataforma(new Point(x ,y), ancho, alto, rozamiento);
			nivel->agregarElemento(plat);
		}else if(tipo == "plataformasInclinadas"){
			int angulo = validar((*it)->getAngulo());
			rozamiento = atof((*it)->getRozamiento().c_str());
			platInc = new PlataformaInclinada(new Point(x ,y), ancho, alto, angulo);
			nivel->agregarElemento(platInc);
		}else if(tipo == "trampolines") {
			cama = new CamaElastica(new Point(x ,y), ancho, alto);
			nivel->agregarElemento(cama);
		} else if (tipo == "pow"){
			rozamiento = atof((*it)->getRozamiento().c_str());
			plat = new Pow(new Point(x ,y), ancho, alto, rozamiento);
			nivel->agregarElemento(plat);
		} else if (tipo == "cajaBonus"){
			rozamiento = atof((*it)->getRozamiento().c_str());
			plat = new CajaBonus(new Point(x ,y), ancho, alto, rozamiento, nivel);
			nivel->agregarElemento(plat);
		}
		
		delete (*it);
	}
	delete elementos;
}



Protagonista* LoaderServidor::ProtagonistaCrear(LoadPersonaje* prot, ID cliente,float piso){
	
	int ancho, alto, x, y;
	Protagonista* protagonista = NULL;
	validarPersonaje(prot, &ancho,&alto, &x, &y);
	int velocidad = validar(prot->getVelocidad());
	int potenciaSalto = validar(prot->getPotenciaSalto());
	Point* posInicial = new Point(x,y);
	protagonista = new Protagonista(posInicial, ancho, alto, velocidad, potenciaSalto, cliente,prot->getNombre(), piso);
	
	return protagonista;
}


void LoaderServidor::cargarPersonajes(ListaLoadPersonaje personajes, Nivel* nivel,float piso){
	
	for(IterPersonajes it = personajes.begin(); it != personajes.end(); ++it){
		int ancho = 0; 
		int alto = 0;
		int x = 0;
		int y = 0;
		validarPersonaje((*it), &ancho,&alto, &x, &y);
		
		Point* pos = new Point(x,y);

		if ((*it)->getNombre() == "mono"){
			Mono* mono = new Mono(pos, ancho, alto, (*it)->getNombre(), 1, nivel);
			nivel->agregarEnemigo(mono);
		} else if ((*it)->getNombre() == "princesa"){
			Princesa* prin = new Princesa(pos, ancho, alto, (*it)->getNombre(), 1, nivel);
			nivel->agregarEnemigo(prin);
		} else if((*it)->getNombre() == "fuego"){
			Fuego* fuego = new Fuego(pos, ancho, alto, (*it)->getNombre() , 1, nivel);
			nivel->agregarEnemigo(fuego);
		}else{
			PersonajeAnimado* personaje= new PersonajeAnimado(pos, ancho, alto, (*it)->getNombre(), piso);
			nivel->agregarPersEnJuego(personaje);
		}
	}
}

int LoaderServidor::getDimensionEnemigo(std::string tipo, int* ancho, int* alto){
	
	for (IterPersonajes it = listaEnemigos->begin(); it != listaEnemigos->end(); ++it) {
		if (!tipo.compare((*it)->getNombre())){
			*ancho = validar((*it)->getAncho());
			*alto = validar((*it)->getAlto());
			return 1;
		}
	}
	return 0;
}

Nivel* LoaderServidor::cargarNivel(){
	
	st_Nivel structNivel;
	int ancho, alto, piso;
	ancho = alto = piso = 0;
	
	this->parser->cargarNivel(structNivel);
	
	ancho = validar(structNivel.ancho.c_str());
	alto = validar(structNivel.alto.c_str());
	piso = validar(structNivel.piso.c_str());
	Nivel* nivel = new Nivel(ancho, alto, piso);
	
	for(IterPersonajes it = structNivel.listaProtagonistas.begin(); it != structNivel.listaProtagonistas.end(); ++it){
		nivel->agregarPersonaje(this->ProtagonistaCrear((*it), ID_INVALIDO , piso));
	}
	
	for (IterPersonajes it = structNivel.listaEnemigos.begin(); it != structNivel.listaEnemigos.end(); ++it) {
		this->listaEnemigos->push_back((*it));
	}

	//Tomo como personaje por defecto al primero de la lista del archivo por defecto

	cargarPersonajes(structNivel.listaPersonajes,nivel, piso);
	cargarElementosJuego(nivel);

	// Borro lo referenciado por los LoadPersonaje* y LoadAnimados* , que se encuentran dentro de la lista de la estructura nivel
	for (list<LoadPersonaje*>::iterator it = structNivel.listaPersonajes.begin(); it != structNivel.listaPersonajes.end(); ++it){
		delete (*it);
	}
	for (list<LoadPersonaje*>::iterator it = structNivel.listaProtagonistas.begin(); it != structNivel.listaProtagonistas.end(); ++it){
		delete (*it);
	}

	return nivel;
}
