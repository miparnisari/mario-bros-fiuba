#include "MenuPrincipal.h"
#include "../eventos/EventoActivarVentana.h"
#include "../eventos/EventoConectar.h"
#include "../eventos/EventoElegirPersonaje.h"
#include "../eventos/EventoCrearServidor.h"
#include "../eventos/EventoTerminarServidor.h"
#include "../eventos/EventoVolverMenuPrincipal.h"
#include "../eventos/EventoCrearServidorSinglePlayer.h"
#include "../eventos/EventoSalirModoSinglePlayer.h"
#include "../excepciones/Excepciones.h"
#include "Componente.h"
#include "Ventana.h"
#include "Imagen.h"
#include "Solapa.h"
#include "Boton.h"
#include "Etiqueta.h"
#include "Textbox.h"
#include "CuadroDeSeleccion.h"
using namespace std;

const string MenuPrincipal::TAG = "MenuPrincipal";

MenuPrincipal::MenuPrincipal() {
	this->ventanaActiva = NULL;
}

MenuPrincipal::~MenuPrincipal() {
    map<string,Ventana*>::iterator it;
    for (it = ventanas.begin(); it != ventanas.end(); ++it) {
        delete(it->second);
    }
	this->ventanaActiva = NULL;
	SDL_Quit();
}

void MenuPrincipal::agregarVentana(Ventana* v) {
	if (ventanas.empty()) {
		this->ventanaActiva = v;
	}
	
	ventanas.insert ( pair<string,Ventana*>(v->getNombre(),v) );
}

void MenuPrincipal::borrarVentana(string nombreVentana) {
	map<string,Ventana*>::iterator it;
	
	it = ventanas.find(nombreVentana);
	if (it != ventanas.end()) {
		delete(it->second);
		it->second = NULL;
		ventanas.erase(it);
	}
	
}

string MenuPrincipal::getNombreVentanaActiva() {
	return this -> ventanaActiva -> getNombre();
}

Ventana* MenuPrincipal::getVentanaActiva() {
	return (this->ventanaActiva);
}

string MenuPrincipal::getData(string componenteID) {
	if (ventanaActiva == NULL) return "";
	
	list<Componente*>::iterator it = ventanaActiva->getComponentes().begin();

	// Buscamos el componente de la ventana que tiene ese ID y devolvemos el valor
	for (it ; it != ventanaActiva->getComponentes().end(); ++it) {
		if ( (*it)->getID().compare(componenteID) == 0) {
			return (*it)->getData();
		}
	}

	//throw ExceptionComponenteNoEncontrado();
}

void MenuPrincipal::activarVentana(string idVent) {
    map<string,Ventana*>::iterator it;
    for (it = ventanas.begin(); it != ventanas.end(); ++it) {
        if (it->first == idVent) {
            this->ventanaActiva = it->second;
            return;
        }
    }
}

bool MenuPrincipal::refrescar(SDL_Surface* destino){
	ventanaActiva->refrescar(destino);
}

void MenuPrincipal::manejarEventos(SDL_Event event) {
	ventanaActiva->manejarEventos(event);
}

void MenuPrincipal::iniciar(){
	crearVentanaInicial();
	this->activarVentana("INICIAL");
}

void MenuPrincipal::crearVentanaSinglePlayerNivel() {
	Ventana* ventana = new Ventana("SINGLEPLAYER_NIVEL");
	
	// Etiqueta
	Etiqueta* etiqueta = new Etiqueta("",100,100,200,FONT_SIZE,"Elija un nivel:",FONT, FONT_SIZE);
	ventana->agregarComponente(etiqueta);
	
	// Leemos los niveles que se pueden elegir
	yamlParser* parserNiveles = new yamlParser("config.yaml");
	vector <string> niveles;
	parserNiveles -> getNiveles(&niveles);

	// Cuadro de seleccion de niveles
	CuadroDeSeleccion* cuadro = new CuadroDeSeleccion("NIVELSP",100,200,200,128);
	for (int i=0; i < niveles.size(); i++) {
		Opcion* opc = new Opcion(niveles[i], FONT, FONT_SIZE);
		cuadro -> agregarOpcion(opc);
	}

	ventana->agregarComponente(cuadro);
	
	// Boton para ir atras
	EventoBoton* evento = new EventoSalirModoSinglePlayer("INICIAL");
	Boton* botonAtras = new Boton("BotAtras", 100, 400, 150, 35, evento,"Atras",FONT,FONT_SIZE);
	ventana->agregarComponente(botonAtras);
	
	//Boton Crear servidor Single Player
	EventoBoton* eventoSP = new EventoCrearServidorSinglePlayer();
	Boton* botonSig = new Boton("BotCrearSP", 350, 400, 150, 35, eventoSP,"Siguiente",FONT,FONT_SIZE);
	ventana->agregarComponente(botonSig);
	
	this->agregarVentana(ventana);
		
	delete(parserNiveles);
	
}

void MenuPrincipal::crearVentanaSinglePlayerPersonaje() {
	Ventana* ventana = new Ventana("SINGLEPLAYER_PERSONAJE");
	
	CuadroDeSeleccion* cuadro = new CuadroDeSeleccion("PERSONAJES",70,100,370,128);

	// para cada personaje, creamos una opcion y la asociamos
	// con sus datos y su animacion
	string nivel = ControladorApp::getInstance()->getNivelActivo();
	Logger::info(TAG, "Se intentará leer: " + nivel);
	LoaderMenu* loadMenu;
	try {
		string path;
		path.assign("./"); path.append(DIR); path.append("/niveles/"); path.append(nivel); path.append(EXT_YAML);
		loadMenu = new LoaderMenu(path);
	} catch (ExceptionIO& ) {
		Logger::fatal(TAG, "No se pudo abrir el archivo de nivel");
		return;
	}

	list<st_PersMenu*> persMenu = loadMenu->cargarVistas();
	Utilitario u;
	for(list<st_PersMenu*>::iterator it = persMenu.begin(); it != persMenu.end() ; ++it){
		Opcion* op = new Opcion((*it)->nombrePers,FONT,FONT_SIZE);

		int x = 500;
		int y = 100;

		op->setAnimAsociada(x, y, (*it)->ancho,(*it)->alto, (*it)->nombreImagen, *((*it)->animaciones), (*it)->nombrePers);
		vector <ParTexto> texto;
		texto.push_back(ParTexto ("Nombre: ",(*it)->nombrePers));
		texto.push_back(ParTexto ("Velocidad: ",  u.convertirAString((*it)->velocidad)));
		texto.push_back(ParTexto ("Potencia Salto: ",  u.convertirAString((*it)->potenciaSalto)));

		op-> setDatosAsociados(x, y + 200, 100, 200, texto);

		cuadro->agregarOpcion(op);
		
		delete(*it);
	}
	ventana->agregarComponente(cuadro);
	
	// boton "atras"
	EventoBoton* evento = new EventoSalirModoSinglePlayer("SINGLEPLAYER_NIVEL");
	Boton* boton = new Boton("BotAtras",100,400,100,35,evento,"Atras",FONT,FONT_SIZE);
	ventana->agregarComponente(boton);
	
	// boton "jugar"
	evento = new EventoElegirPersonaje();
	boton = new Boton("BotAtras",300,400,100,35,evento,"Jugar",FONT,FONT_SIZE);
	ventana->agregarComponente(boton);

	this->agregarVentana(ventana);
	delete(loadMenu);
}

void MenuPrincipal::crearVentanaMultiplayer() {
	Ventana* ventana = new Ventana("MULTIPLAYER");

	yamlParser* parserNiveles = new yamlParser("config.yaml");
	yamlParser* parserDatosDef = new yamlParser("datosDefecto.yaml");
	
	// Obtenemos el puerto, el servidor, y los niveles
	string puertoServidor;
	parserDatosDef -> getPuertoServidor(&puertoServidor);
	ParTexto dirYPuerto;
	parserDatosDef -> getDirYPuertoHost(&dirYPuerto);
	string cantClientes;
	parserDatosDef -> getCantClientes(&cantClientes);
	
	vector <string> niveles;
	parserNiveles -> getNiveles(&niveles);
	
	////////////////////////
	// SOLAPA CLIENTE    //
	///////////////////////
	Solapa* solapaCliente = new Solapa("CLIENTE");
	
	// etiqueta "host"
	Etiqueta* etiqueta = new Etiqueta("",70,150,100,FONT_SIZE,"Host:",FONT, FONT_SIZE);
	solapaCliente->agregarComponente(etiqueta);

	// textbox "host"
	Textbox* textbox = new Textbox("HOST",180,150,150,20,dirYPuerto.first,FONT,FONT_SIZE);
	solapaCliente->agregarComponente(textbox);
	
	// etiqueta "puerto"
	etiqueta = new Etiqueta("",70,200,100,FONT_SIZE,"Puerto:",FONT, FONT_SIZE);
	solapaCliente->agregarComponente(etiqueta);
	
	// textbox "puerto"
	textbox = new Textbox("PUERTO",180,200,150,20,dirYPuerto.second,FONT,FONT_SIZE);
	solapaCliente->agregarComponente(textbox);
	
	// Boton para ir al menu inicial
	EventoBoton* evento = new EventoActivarVentana("INICIAL");
	Boton* boton = new Boton("BotAtras", 100, 400, 100, 35, evento,"Atras",FONT,FONT_SIZE);
	solapaCliente->agregarComponente(boton);
	
	// Boton para ir a elegir personaje
	evento = new EventoConectar();
	boton = new Boton("BotPers", 300, 400, 150, 35, evento,"Siguiente",FONT,FONT_SIZE);
	solapaCliente->agregarComponente(boton);
	
	ventana->agregarSolapa(solapaCliente);
	
	////////////////////////
	// SOLAPA SERVIDOR    //
	///////////////////////
	Solapa* solapaServidor = new Solapa("SERVIDOR");
	
	// etiqueta "nivel"
	etiqueta = new Etiqueta("",70,100,100,FONT_SIZE,"Nivel:",FONT, FONT_SIZE);
	solapaServidor->agregarComponente(etiqueta);
	
	// cuadro de seleccion "nivel"
	CuadroDeSeleccion* cuadro = new CuadroDeSeleccion("NIVEL",70,130,300,100);
	for (int i=0; i < niveles.size(); i++) {
		Opcion* opc = new Opcion(niveles[i], FONT, FONT_SIZE);
		cuadro -> agregarOpcion(opc);
	}

	solapaServidor->agregarComponente(cuadro);
	
	
	// etiqueta "cantidad clientes"
	etiqueta = new Etiqueta("",70,300,180,FONT_SIZE,"Cantidad clientes:",FONT, FONT_SIZE);
	solapaServidor->agregarComponente(etiqueta);

	// textbox "cantidad clientes"
	textbox = new Textbox("CANTCLIENTES",300,300,150,FONT_SIZE,cantClientes,FONT,FONT_SIZE);
	solapaServidor->agregarComponente(textbox);

	// etiqueta "puerto"
	etiqueta = new Etiqueta("",70,350,100,FONT_SIZE,"Puerto:",FONT, FONT_SIZE);
	solapaServidor->agregarComponente(etiqueta);

	// textbox "puerto"
	textbox = new Textbox("PUERTO",300,350,150,FONT_SIZE,puertoServidor,FONT,FONT_SIZE);
	solapaServidor->agregarComponente(textbox);

	// boton para crear servidor
	evento = new EventoCrearServidor();
	boton = new Boton("BotCrearServidor",70,450,180,35,evento,"Crear servidor", FONT,FONT_SIZE);
	solapaServidor->agregarComponente(boton);

	// boton para parar servidor
	evento = new EventoTerminarServidor();
	Boton* botonTerminar = new Boton("BotTerminarServidor",300,450,180,35,evento,"Parar servidor",FONT,FONT_SIZE);
	solapaServidor->agregarComponente(botonTerminar);
	
	ventana->agregarSolapa(solapaServidor);
	
	this->agregarVentana(ventana);
	
	
	delete(parserDatosDef);
	delete(parserNiveles);
}

void MenuPrincipal::crearVentanaMultiplayerPersonaje() {
	Ventana* ventana = new Ventana("MULTIPLAYER_PERSONAJE");
	
	Solapa* solapaCliente = new Solapa("CLIENTE");
	
	// un menu de seleccion de personaje
	CuadroDeSeleccion* cuadro = new CuadroDeSeleccion("PERSONAJES",70,100,370,150);

	// para cada personaje, creamos una opcion y la asociamos
	// con sus datos y su animacion
	string nivel = ControladorApp::getInstance()->getNivelActivo();
	std::cout << "Se intentara leer: " << nivel << endl;
	Logger::info(TAG, "Se intentará leer: " + nivel);
	LoaderMenu* loadMenu;
	try {
		string path;
		path.assign("./"); path.append(DIR); path.append("/niveles/"); path.append(nivel); path.append(EXT_YAML);
		loadMenu = new LoaderMenu(path);
	} catch (ExceptionIO& ) {
		Logger::fatal(TAG, "No se pudo abrir el archivo de nivel");
		return;
	}

	list<st_PersMenu*> persMenu = loadMenu->cargarVistas();
	Utilitario u;
	for(list<st_PersMenu*>::iterator it = persMenu.begin(); it != persMenu.end() ; ++it){
		Opcion* op = new Opcion((*it)->nombrePers,FONT,FONT_SIZE);

		int x = 500;
		int y = 100;

		op->setAnimAsociada(x, y, (*it)->ancho,(*it)->alto, (*it)->nombreImagen, *((*it)->animaciones), (*it)->nombrePers);
		vector <ParTexto> texto;
		texto.push_back(ParTexto ("Nombre: ",(*it)->nombrePers));
		texto.push_back(ParTexto ("Velocidad: ",  u.convertirAString((*it)->velocidad)));
		texto.push_back(ParTexto ("Potencia Salto: ",  u.convertirAString((*it)->potenciaSalto)));

		op-> setDatosAsociados(x, y + 200, 100, 200, texto);

		cuadro->agregarOpcion(op);
	}
	solapaCliente->agregarComponente(cuadro);
	
	// Un boton para volver atras
	EventoBoton* evento = new EventoActivarVentana("MULTIPLAYER");
	Boton* boton = new Boton("BotAtras",100,450,114,35,evento,"Atras",FONT,FONT_SIZE);
	solapaCliente->agregarComponente(boton);
	
	// Un boton para elegir el personaje
	evento = new EventoElegirPersonaje() ;
	boton = new Boton("BotJugar",300,450,114,35,evento,"Jugar",FONT,FONT_SIZE);
	solapaCliente->agregarComponente(boton);

	ventana->agregarSolapa(solapaCliente);

	delete(loadMenu);
	
	
	
	this->agregarVentana(ventana);
}



void MenuPrincipal::crearVentana(string nombreVentana) {
	// Si la ventana ya existia, la borramos...
	borrarVentana(nombreVentana);
	
	// ... y la creamos de nuevo.
	if (nombreVentana == "INICIAL")
		crearVentanaInicial();
	else if (nombreVentana == "SINGLEPLAYER_NIVEL")
		crearVentanaSinglePlayerNivel();
	else if (nombreVentana == "SINGLEPLAYER_PERSONAJE")
		crearVentanaSinglePlayerPersonaje();
	else if (nombreVentana == "MULTIPLAYER")
		crearVentanaMultiplayer();
	else if (nombreVentana == "MULTIPLAYER_PERSONAJE")
		crearVentanaMultiplayerPersonaje();
	else
		Logger::warn(TAG,"Ventana no existe");
}

void MenuPrincipal::crearVentanaInicial() {
	Ventana* ventana = new Ventana("INICIAL");
	
	string s = "Elija un modo de juego:";
	Etiqueta* etiqueta = new Etiqueta("EtModoJuego", 100, 100, 300, 30, s, FONT, FONT_SIZE);
	ventana->agregarComponente(etiqueta);
	
	EventoBoton* evento = new EventoActivarVentana("SINGLEPLAYER_NIVEL");
	Boton* botonSP = new Boton("BotSinglePlayer", 100, 200, 150, 35, evento,"Single Player",FONT,FONT_SIZE);
	ventana->agregarComponente(botonSP);
	
	evento = new EventoActivarVentana("MULTIPLAYER");
	Boton* botonMP = new Boton("BotMultiPlayer", 300, 200, 150, 35,evento,"Multi Player",FONT,FONT_SIZE);
		
	ventana->agregarComponente(botonMP);
	
	this->agregarVentana(ventana);
	
}
