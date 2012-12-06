#include "loaderJugador.h"
#include "../app/ControladorApp.h"
#include <iostream>
#define MAXPANT 2000
#define MINPANT 200
#define INVALIDO -1

const string LoaderJugador::TAG = "loaderJugador";


LoaderJugador::LoaderJugador(std::string archConfig) : Loader(archConfig){

}

LoaderJugador::~LoaderJugador() {
	//delete(parser);
}


Pantalla* LoaderJugador::cargarPantalla() {
	
	st_Pantalla pantalla;
	this->parser->cargarPantalla(pantalla);
	
	int ancho = validar(pantalla.ancho.c_str()); // Si validar falla, devuelve -1
	int alto = validar(pantalla.alto.c_str());
	
	if (ancho == INVALIDO || alto == INVALIDO) {
		ancho = SCREEN_WIDTH;
		alto = SCREEN_HEIGHT;
	}
	
	Pantalla* screen = FactoryPantalla::crear(ancho, alto, SCREEN_BPP, "Juego");
	return screen;
}
/*
void LoaderJugador::cargarMusica() {
	st_Musica mus, musDef;
	this->parser->cargarMusica(mus);
	this->parserDefecto->cargarMusica(musDef);

	// Si el archivo de musica original no existe, entonces cargamos el que es por defecto
	try {
		Juego::getInstance()->soundHandler->cargarMusica(mus.file, mus.tag);
	} catch (ExceptionCargaMusica& e) {
		try {
			Juego::getInstance()->soundHandler->cargarMusica(musDef.file, musDef.tag);
		} catch (ExceptionCargaMusica& e) {
			Logger::error(TAG, "No se pudo cargar la musica por defecto.");
			throw ExceptionCargaMusica(musDef.file);
		}
	}
	return;
}

*/

void LoaderJugador::cargarElementosJuego() {
	/* Idea: Creo un map en donde hago pares Textura: Ruta de imagen
	 * Cuando tengo que cargar la lista elemtos del mapa, les paso el map
	 * para que sepan a que ruta ir su buscar su imagen */

	vector<LoadTextura*>* datos = this->parser->cargarTexturas();
	TextureHandler* handler = new TextureHandler("texturaError");
	this->cargarTexturas(*datos, *handler);
	cargarElementosLista( "plataformas", *handler);
	cargarElementosLista( "plataformasInclinadas", *handler);
	cargarElementosLista( "escaleras", *handler);
	cargarElementosLista( "canierias", *handler);
	cargarElementosLista( "trampolines", *handler);
	cargarElementosLista( "pow", *handler);
	cargarElementosLista( "cajaBonus", *handler);
	cargarElementosLista( CORAZON, *handler);
	cargarElementosLista( ICONO_ARMADURA, *handler);
	cargarElementosLista( GANAR, *handler);
	cargarElementosLista( PERDER, *handler);
	cargarElementosLista( ESPERANDO, *handler);

	delete datos;
	delete handler;
}

void LoaderJugador::cargarTexturas(vector<LoadTextura*>& texturas, TextureHandler& handler){
	vector<LoadTextura*>::iterator it;
	
	for ( it = texturas.begin() ; it < texturas.end(); ++it ){
		if ( (!(*it)->getTextura().compare(ERROR)) || (!(*it)->getFile().compare(ERROR)) ){
			Logger::error(TAG, "Error al cargar textura.");
			Logger::debug(TAG,"textura: " + (*it)->getTextura());
			Logger::debug(TAG,"file: " + (*it)->getFile());
		} else {
			handler.addTextura((*it)->getTextura(), "tmp/" + (*it)->getFile());
		}
		delete (*it);
	}
}

void LoaderJugador::cargarElementosLista( std::string tipo, TextureHandler& handler ) {
		
	vector<LoadElementoMapa*>* elementos = this->parser->cargarElementosVector(tipo);
	vector<LoadElementoMapa*>::iterator it;
	for ( it = elementos->begin() ; it < elementos->end(); ++it ){
		int x, y, ancho, alto, angulo;
		Logger::debug(TAG, "tex: " + (*it)->getTextura());
		Logger::debug(TAG, "x: " + (*it)->getX());
		Logger::debug(TAG, "y: " + (*it)->getY());
		x = validar((*it)->getX().c_str());
		y = validar((*it)->getY().c_str());
		ancho = validar((*it)->getAncho().c_str());
		alto = validar((*it)->getAlto().c_str());

		Elemento* elem = new Elemento(new Point(x ,y));
		Imagen* image = NULL;
		try{
			std::string archivo = handler.getTextura((*it)->getTextura());
			if(tipo == "plataformasInclinadas"){
				angulo = validar((*it)->getAngulo());
				image = new VistaElementoRotado(archivo, elem, 1, ancho, alto, ID_INVALIDO, "plataformasInclinadas", angulo);	
			
			}else if((tipo == CORAZON) || (tipo == ICONO_ARMADURA) || (tipo == GANAR) || (tipo == PERDER) || (tipo == ESPERANDO)){
				// ICONOS TIENEN PRIORIDAD = 0
				image = new VistaElemento(archivo, elem, 0, ancho, alto, ID_INVALIDO, "elemento");
			} else{
				image = new VistaElemento(archivo, elem, 1, ancho, alto, ID_INVALIDO, "elemento");
			}
		} catch (exception& e){
			Logger::error(TAG, "Error en la creacion de VistaElemento, no se agregara al nivel.");
			// Si no pudo crear la imagen, no agrego a la lista de vistas
			// y sigo cargando las otras imagenes en el ciclo
			delete (*it);
			continue;
		}
		ControladorJugador* cj = ControladorApp::getInstance()->getCJ();
		if((tipo == CORAZON) || (tipo == ICONO_ARMADURA) || (tipo == GANAR) || (tipo == PERDER) || (tipo == ESPERANDO)){
			st_VistasBonus* vistaBonus = new st_VistasBonus;
			vistaBonus->activo = false;
			vistaBonus->imagen = image;
			vistaBonus->nombre = tipo;
	//		std::cout << "AGREGAR BONUS: " << tipo << "\n";
			cj->agregarVistaBonus(vistaBonus);
		}		
		else
			cj->agregarVista(image);
		
		delete (*it);
	}
	delete elementos;
}

void LoaderJugador::crearVistaNivel(int alto, int ancho, std::string nombreImagen, AnimacionProtagonista* protagonista, int anchoPantalla,int altoPantalla) {
	
	ControladorJugador* cj = ControladorApp::getInstance()->getCJ();
	Elemento* elem = new Elemento(new Point(0,0));	//no hay que perder la referencia a esto
	VistaNivel* image = NULL;

	try {
		image = new VistaNivel("tmp/" + nombreImagen, elem, protagonista->getMargenScroll(), anchoPantalla, altoPantalla, ancho, alto, PRIOR_NIVEL, ID_INVALIDO, "nivel");
	} catch (exception& e){
		Logger::error(TAG, "No se pudo cargar la imagen del fondo en la configuracion.");
	}

	image->set_vistaProt(protagonista);	
	image->set_dimension(ancho,alto);
	cj->agregarVista(image);
	cj->setVistaPrincipal(protagonista);

}

vector<st_Animacion*>* LoaderJugador::cargarAnimaciones(list<LoadAnimacion*> animaciones){//, bool* quieto, bool* caminar){
	
	vector<st_Animacion*>* vectorAnim = new vector<st_Animacion*>;;
	
	for (list<LoadAnimacion*>::iterator it = animaciones.begin(); it != animaciones.end(); ++it) {
		
		st_Animacion* a = new st_Animacion();
		a->offset = validar((*it)->getOffset());
		a->cantidad = validar((*it)->getCantidad());
		a->periodo = validar((*it)->getPeriodo());
		a->ejecucion= (*it)->getNombre();

		vectorAnim->push_back(a);
	}
	
	return vectorAnim;
}

AnimacionAuto* LoaderJugador::crearVistaPersonajeAnimado(LoadPersonaje* prot, ID unID, Point* posicion){
	int ancho, alto;
	string imagen;
	vector<st_Animacion*>* vectorAnimaciones = NULL;
	
	AnimacionAuto* animacion = NULL;
	
	Elemento* posProt = new Elemento(posicion);
	imagen = prot->getImagen();
	vectorAnimaciones = cargarAnimaciones(prot->animaciones);
	try {
		animacion = new AnimacionAuto("tmp/" + imagen, posProt , 3 ,alto, ancho, *vectorAnimaciones, unID, prot->getNombre());
	} catch (exception& ba) {//Son varios tipos de excepciones que puede capturar, así que se levanta una generica.
		Logger::error(TAG, "No se pudo cargar la imagen del protagonista en la configuracion.");
		throw ExceptionIO("No se pudo cargar la imagen del protagonista en la configuracion.");
	}
	delete vectorAnimaciones; 

	return animacion;
}

AnimacionProtagonista* LoaderJugador::crearVistaEnemigo(LoadPersonaje* prot, ID unID, Point* posicion){
	int ancho, alto, x, y;
	string imagen;
	vector<st_Animacion*>* vectorAnimaciones = NULL;
	
	AnimacionProtagonista* animacion = NULL;
	this->validarPersonaje(prot, &ancho,&alto, &x, &y);
	
	Elemento* posProt = new Elemento(posicion);
	imagen = prot->getImagen();
	vectorAnimaciones = cargarAnimaciones(prot->animaciones);
//printf("loaderjugador X %f Y %f\n", posicion->x, posicion->y);
	try {
		animacion = new AnimacionProtagonista("tmp/" + imagen, posProt , 3 ,alto, ancho, *vectorAnimaciones, unID, prot->getNombre());
	} catch (exception& ba) {//Son varios tipos de excepciones que puede capturar, así que se levanta una generica.
		Logger::error(TAG, "No se pudo cargar la imagen del protagonista en la configuracion.");
		throw ExceptionIO("No se pudo cargar la imagen del protagonista en la configuracion.");
	}
	delete vectorAnimaciones; 
//printf("loaderjugador2 X %f Y %f\n", animacion->getPos()->x, animacion->getPos()->y);
	return animacion;
}

AnimacionProtagonista* LoaderJugador::crearVistaProtagonista(LoadPersonaje* prot, ID  idCliente ){

	int ancho, alto, x, y;
	string imagen;
	vector<st_Animacion*>* vectorAnimaciones = NULL;
	
	AnimacionProtagonista* animacion = NULL;
	this->validarPersonaje(prot, &ancho,&alto, &x, &y);
	
	Elemento* posProt = new Elemento(new Point(x,y));
	imagen = prot->getImagen();
	vectorAnimaciones = cargarAnimaciones(prot->animaciones);

	int scroll = validar(prot->getMargenScroll());
	
	try {
		animacion = new AnimacionProtagonista("tmp/" + imagen, posProt , 3 ,alto, ancho, *vectorAnimaciones, idCliente, prot->getNombre());
	} catch (exception& ba) {//Son varios tipos de excepciones que puede capturar, así que se levanta una generica.
		Logger::error(TAG, "No se pudo cargar la imagen del protagonista en la configuracion.");
		throw ExceptionIO("No se pudo cargar la imagen del protagonista en la configuracion.");
	}
	animacion->setMargenScroll(scroll);

	delete vectorAnimaciones; 
	return animacion;
}

AnimacionProtagonista* LoaderJugador::cargarVidas(){

	int ancho, alto, x, y;
	string imagen;
	st_Nivel nivel;
	vector<st_Animacion*>* vectorAnimaciones = NULL;
	AnimacionProtagonista* animacion = NULL;
	this->parser->cargarNivel(nivel);
	LoadPersonaje* vida = nivel.vida;
	
	this->validarPersonaje(vida, &ancho,&alto, &x, &y);
	
	Elemento* posVida = new Elemento(new Point(x,y));
	imagen = vida->getImagen();
	vectorAnimaciones = cargarAnimaciones(vida->animaciones);

	try {
		animacion = new AnimacionProtagonista("tmp/" + imagen, posVida , 3 ,alto, ancho, *vectorAnimaciones, ID_INVALIDO, vida->getNombre());
	} catch (exception& ba) {//Son varios tipos de excepciones que puede capturar, así que se levanta una generica.
		Logger::error(TAG, "No se pudo cargar la imagen del protagonista en la configuracion.");
		throw ExceptionIO("No se pudo cargar la imagen del protagonista en la configuracion.");
	}
	//animacion->setMargenScroll(scroll);

	delete vectorAnimaciones; 
	return animacion;
}

void LoaderJugador::cargarVistaPersonajes(ListaLoadPersonaje animados,int anchoNivel, int altoNivel){

	int ancho, alto, x, y;
	string imagen;
	vector<st_Animacion*>* vectorAnimaciones = NULL;
	ControladorJugador* cj = ControladorApp::getInstance()->getCJ();
		
	for (IterPersonajes it = animados.begin(); it != animados.end(); ++it) {
		
		
		this->validarPersonaje((*it) , &ancho, &alto, &x, &y);
		Elemento* posPersonaje = new Elemento(new Point(x,y));
		
	
		imagen = (*it)->getImagen();
		vectorAnimaciones = cargarAnimaciones((*it)->animaciones);
		AnimacionAuto* animacion = NULL;
		try {
			animacion = new AnimacionAuto("tmp/" + imagen, posPersonaje , 1 ,alto, ancho, *vectorAnimaciones, ID_INVALIDO,(*it)->getNombre());
		} catch (exception& e){
			Logger::error(TAG, "No se pudo cargar la imagen del personaje en la configuracion.");
		}
		cj->agregarVista(animacion);
		delete vectorAnimaciones;
		
	}
}

//Cargo todos los protagonistas en la lista general, si es uno que ya se esta usando (esta en la lista pasada por parametro)
//se carga en la lista de vistas usadas en el juego y no en la general
AnimacionProtagonista* LoaderJugador::cargarProtagonistas(ListaLoadPersonaje protag, ListaParJugador jugadores, ID id){
	ControladorJugador* cj = ControladorApp::getInstance()->getCJ();
	AnimacionProtagonista* protagonista;
	for(IterPersonajes it = protag.begin(); it != protag.end() ; ++it){ 
		
		bool protJugador = false;
		IterParJugador itJugador = jugadores.begin();
		while(!protJugador and ((itJugador) != jugadores.end())){
			if((*it)->getNombre().compare((*itJugador)->first) == 0){
				if((*itJugador)->second == id){
					protagonista = crearVistaProtagonista((*it),(*itJugador)->second);
					cj->agregarVista(protagonista);
				}
				else{
					cj->agregarVista(crearVistaProtagonista((*it) ,(*itJugador)->second));
				}
				protJugador = true;
			}
			else
				++itJugador;
		}
		if(!protJugador){
			cj->agregarVistaGeneral(crearVistaProtagonista((*it) ,ID_INVALIDO));
		}
	}
	return protagonista;
}

AnimacionAuto* LoaderJugador::cargarPersonajeAnimado(std::string tipo, ID myID, Point* miPos) {
	
	if (listaPersonajesAnimados.empty()){ 
		return NULL;
	}
	AnimacionAuto* anim = NULL;
	std::list<LoadPersonaje*>::iterator it;
	for (it = listaPersonajesAnimados.begin(); it != listaPersonajesAnimados.end(); ++it) {
		if(tipo.compare((*it)->getNombre()) == 0){
				anim = crearVistaPersonajeAnimado((*it), myID, miPos);
				return anim;
		}
	}
	return NULL;
}

AnimacionProtagonista* LoaderJugador::cargarEnemigo(std::string tipo, ID myID, Point* miPos){
	
	if (listaEnemigos.empty()){ 
		return NULL;
	}
	AnimacionProtagonista* enemigo = NULL;
	for (IterPersonajes it = listaEnemigos.begin(); it != listaEnemigos.end(); ++it) {
		if(!tipo.compare((*it)->getNombre())){
				enemigo = crearVistaEnemigo((*it), myID, miPos);
				return enemigo;
		}
	}
	return NULL;
}


void LoaderJugador::cargarVistas(ListaParJugador jugadores, ID jugPrincipal){
			
	st_Nivel nivel;
	
	int ancho, alto;
	std::string fondo;
	
	this->parser->cargarNivel(nivel);

	ancho = validar(nivel.ancho.c_str());
	alto = validar(nivel.alto.c_str());
	fondo = nivel.fondo;
	// Pantalla no esta inicializado y tira seg fault :S (Pablon)
	/*if(ancho < ControladorJugador::getInstance()->pantalla->getAncho())
		ancho = INVALIDO;
	
	if(alto < ControladorJugador::getInstance()->pantalla->getAlto())
		alto = INVALIDO;
	*/
	
	if(ancho == INVALIDO){
		Logger::error(TAG, "Error al cargar ancho del nivel, carga por defecto.");
	}
	if(alto == INVALIDO){
		Logger::error(TAG, "Error al cargar alto del nivel, carga por defecto.");
	}
	if((fondo.compare(ERROR)) == 0){
		Logger::error(TAG, "Error al cargar el fondo del nivel, carga por defecto.");
	}

	for (IterPersonajes it = nivel.listaEnemigos.begin(); it != nivel.listaEnemigos.end(); ++it) {
		this->listaEnemigos.push_back((*it));
	}
	
	for (IterPersonajes it = nivel.listaPersonajes.begin(); it != nivel.listaPersonajes.end(); ++it) {
		this->listaPersonajesAnimados.push_back((*it));
	}
	
	AnimacionProtagonista* protagonista = this->cargarProtagonistas(nivel.listaProtagonistas, jugadores,jugPrincipal);

	int anchoPantalla = ControladorApp::getInstance()->getPantalla()->getAncho();
	int altoPantalla = ControladorApp::getInstance()->getPantalla()->getAlto();
	this->crearVistaNivel(alto, ancho, fondo, protagonista, anchoPantalla, altoPantalla);
	
	//Cargo las animaciones automaticas
	cargarVistaPersonajes(nivel.listaPersonajes, ancho, alto);

	// Borro lo referenciado por los LoadPersonaje* y LoadAnimados* , que se encuentran dentro de la lista de la estructura nivel
	for (IterParJugador it = jugadores.begin(); it != jugadores.end(); ++it){
		delete (*it);
	}
	
	/*
	for (IterPersonajes it = nivel.listaPersonajes.begin(); it != nivel.listaPersonajes.end(); it++){
		delete (*it);
	}
	* */
	for (IterPersonajes it = nivel.listaProtagonistas.begin(); it != nivel.listaProtagonistas.end(); ++it){
		delete (*it);
	}
	
}
