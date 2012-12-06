#include "ControladorApp.h"
#include "../vista/BarraDeEstado.h"

const string ControladorApp::TAG = "ControladorApp";

ControladorApp* ControladorApp::instance = NULL;

using namespace std;

ControladorApp::ControladorApp(Pantalla* p)
{
	this->activo = true;
	this->finalizoJuego = false;
	this->pantalla = p;
	this->modoSinglePlayer = false;
	this->CM = new ControladorMenu();
	this->CJ = new ControladorJugador();
	this->activarMenu();
	this->setBarraEstado(FONT_SIZE);
	this->manejadorFps = new FpsHandler(FPS);
	this->servidor = NULL;
	this->nivelActivo = "";
	this->temporizador = Temporizador();
	this->temporizador.setIntervalo(TIEMPO_ALIVE_JUGADOR);
	this->temporizador.setTiempoInicial();
	singlePlayerSelect = false;
}

ControladorApp::~ControladorApp()
{	
	destruirServidor();
	delete (CM); CM = NULL;
	delete (CJ); CJ = NULL;
	delete (this->manejadorFps); this->manejadorFps = NULL;
	delete (this->pantalla); this->pantalla = NULL;
	delete (this->barraEstado); this->barraEstado = NULL;
}

ControladorApp* ControladorApp::getInstance() 
{
	if (instance == NULL) {
		LoaderJugador* loader = new LoaderJugador("config.yaml");
		Pantalla* pantalla = loader->cargarPantalla();
		instance = new ControladorApp(pantalla);
		delete(loader);
	}
	return instance;
}

void ControladorApp::destroyInstance() {
	if (! instance) return;
	delete instance;
}

void ControladorApp::simular()
{
	bool response = true;
	Jugador* j = NULL;
	while (this->activo){
		j = this->CJ->getJugador();
		if (j != NULL){
			if (this->temporizador.puedeRealizarAccion()){
				this->temporizador.setTiempoInicial();
				EventoKeepAlive* ev = new EventoKeepAlive(j->getID());
				response = j->getServidorRemoto()->enviar(ev);
			}
		}
		
		if (this->CM->estaActivo()){
			usleep(20);
			this->CM->manejarEventos();
			this->CM->refrescar(this->pantalla);
		}
		
		else if (this->CJ->estaActivo()){
			this->manejadorFps->setStart();
			this->CJ->manejarEventos();
			this->CJ->refrescar(this->pantalla);
			this->CJ->eliminarVistasInactivas();
			this->manejadorFps->regularFps();
			if (!this->CJ->getJugador()->getServidorRemoto()->isAlive()){
				this->CJ->desactivar();
				this->CJ->desconectar = true;
				this->CM->activar();
			}
		}
		
		this->refrescarBarraDeEstado();
		this->refrescarPantalla();
	
		if (this->CJ->desconectar){
			this->salidaPorDesconexion();
			this->CJ->desconectarASAP(false);
		}
		
		if (!response){
			this->salidaPorDesconexion();
			response = true;
		}
		
		if (finalizoJuego){
			singlePlayerSelect = false;
			finalizoJuego = false;
			this->CJ->refrescar(this->pantalla);
			refrescarPantalla();
			if (servidor) this->servidor->informarGanador();
			sleep(4);
			EventoSalir* evS = new EventoSalir(this->CJ->getID());
			if (this->CJ->getJugador())
				this->CJ->getJugador()->getServidorRemoto()->enviar(evS);
			delete this->CJ;
			this->CJ = new ControladorJugador();
			this->destruirServidor();
			this->servidor = NULL;
		}
		
	}
	Logger::info(TAG, "Fin de ejecucion del programa.");
}

void ControladorApp::setServidor(Servidor* serv) {
	this->servidor = serv;
}

void ControladorApp::refrescarPantalla() {
	mutexBarraEstado.lock();
	SDL_UpdateRect(pantalla->getScreen(),0,0,pantalla->getAncho(), pantalla->getAlto()-FONT_SIZE);
	mutexBarraEstado.unlock();
}

void ControladorApp::destruirServidor() {
	if (getServidor()) {
		if (servidor->corriendo()) {
			servidor->detener();
			servidor->sincronizar();
		}
		delete (servidor);
		this->setEstado("Servidor finalizado correctamente.");
	}
	else {
		this->setEstado("No existe servidor para cerrar.");
	}
	setServidor(NULL);
}

bool ControladorApp::crearServidor(bool singlePlayer){
	string puerto;
	string nivel;
	string cantJugadores;
	
	if (singlePlayer == false) {
		puerto = CM->getMenu()->getData("PUERTO");
		nivel = CM->getMenu()->getData("NIVEL");
		Logger::info(TAG, "Se crea un servidor MP");
		cantJugadores = CM->getMenu()->getData("CANTCLIENTES");
	} else {
		puerto.assign(DEFAULT_PORT);
		nivel = CM->getMenu()->getData("NIVELSP");
		Logger::info(TAG, "Se crea un servidor SP");
		cantJugadores = 1;
	}
	
	this -> setNivelActivo(nivel);
	
	// Esta comprobacion se realizara cuando desde una misma ventana se quieran crear 2 servidores
	if (servidor) {
		this->setEstado("Ya existe servidor.");
		return false;
	}
	
	this->setEstado("Creando servidor...");
	Servidor* server = NULL;
	try {
		if (singlePlayer == false)
			server = new Servidor(puerto, nivel, cantJugadores, "MP");
		else
			server = new Servidor(puerto, nivel, cantJugadores, "SP");
		setServidor(server);
	} catch (ExceptionConex& e){
		setServidor(NULL);
		this->setEstado(e.what());
		Logger::error(TAG, "Error al crear el servidor.");
		return false;
	} catch (ExceptionPuertoInvalido&) {
		setServidor(NULL);
		this->setEstado("Puerto invalido. Ingrese solo numeros. ");
		Logger::error(TAG, "Puerto invalido.");
		return false;
	} catch (ExceptionIO&) {
		setServidor(NULL);
		this->setEstado("Archivo de configuracion invalido.");
		Logger::error(TAG, "Archivo de configuracion invalido.");
		return false;
	}
		
	this->setEstado("Servidor creado correctamente en el puerto " + puerto + ".");
	this->servidor->iniciar();
	return true;
}

void ControladorApp::salidaPorDesconexion(){
	this->desactivarJugador();
	CJ->setIDRecibido(false);
	CJ->setRespuesta(false);
	this->activarMenu();
	
	if (CJ->getJugador()){
		CJ->getJugador()->detener();
		CJ -> limpiarListas();
		delete (CJ->getJugador());
		CJ->setJugador(NULL);
	}
	delete (CJ);
	this -> CJ = new ControladorJugador();
	this->setEstado("Esperando un estado...");
}


void ControladorApp::conectarJugador(bool singlePlayer) {
	this->modoSinglePlayer = singlePlayer;
	string puerto, host;
	
	// Asignamos el host y el puerto adecuados
	if (modoSinglePlayer) {
		puerto.assign(DEFAULT_PORT);
		host.assign(DEFAULT_HOST);
	} else {
		puerto = CM->getMenu()->getData("PUERTO");
		host =  CM->getMenu()->getData("HOST");
		this->setEstado("Conectando al puerto " + puerto);
		Logger::info(TAG, "Conectando al puerto");
		Logger::info(TAG, "Puerto: " + puerto);
		Logger::info(TAG, "Host: " + host);
	}
	
	
	// Conectamos y (avanzamos o volvemos atras)
	try {
		this->CJ->conectarJugador(puerto,host);
	} catch (ExceptionConex& e){
		this->setEstado("Error al cargar la configuracion del menu.");
		Logger::error(TAG, "Error al cargar la configuracion del menu.");
		
		if (modoSinglePlayer)
			this->CM->getMenu()->activarVentana("SINGLEPLAYER_NIVEL");
		else
			this->CM->getMenu()->activarVentana("MULTIPLAYER");
		return;
	}
	
	if (modoSinglePlayer)
		this->redibujarVentana("SINGLEPLAYER_PERSONAJE");
	else 
		this->redibujarVentana("MULTIPLAYER_PERSONAJE");
	
	this->setEstado("Conexion correcta al juego.");
	Logger::info(TAG, "Conexion correcta al juego.");
}

void ControladorApp::clienteEnviarPersonaje() {
	string personajeElegido = CM->getMenu()->getData("PERSONAJES");
	ID id = CJ->getID();
	
	if ( ! modoSinglePlayer) {
		this->setEstado("Solicitando personaje al servidor...");
	}
	Logger::info(TAG, "Solicitando personaje al servidor...");
	
	if (modoSinglePlayer){
		if (!singlePlayerSelect){
			this->CJ->enviarPersonaje(id, personajeElegido);
			singlePlayerSelect = true;
			EventoOKServidor* evOK = new EventoOKServidor(id);
			try {
				ControladorApp::getInstance()->getCJ()->getJugador()->getServidorRemoto()->enviar(evOK);
			} catch (ExceptionConex& e){
				Logger::error(TAG, e.what());
				ControladorApp::getInstance()->setEstado(e.what());
				return;
			}
		}
	} else {
		this->CJ->enviarPersonaje(id, personajeElegido);
	}
}

void ControladorApp::setBarraEstado(int fontSizeTexto) {
	if (this->pantalla == NULL)
		return;
	
	string id = "barraEstado";
	int x = 0;
	int y = (pantalla->getAlto()) - fontSizeTexto;
	int ancho = pantalla->getAncho();
	int alto = fontSizeTexto;
	string font = FONT;
	this->barraEstado = new BarraDeEstado(id , x, y, ancho, alto, font, fontSizeTexto, &mutexBarraEstado);
}

void ControladorApp::volverAlMenuPrincipal() {
	Jugador* j = this->getCJ()->getJugador();
	if (!j) return;
	
	this->getCJ()->setEstadoConexJugador(false);
	
	if (j->getServidorRemoto()) {
		EventoSalir* eventoSal = new EventoSalir(this->getCJ()->getID());
		j->getServidorRemoto()->enviar(eventoSal);
	}
	singlePlayerSelect = false;
	this->getCJ()->setIDRecibido(false);
	this->getCJ()->setRespuesta(false);
	this->getCJ()->desactivar();
	//j->detener();
//	this->getCJ()->limpiarListas(); //No limpia las vistas porque nunca las dibujo.
	delete (this->getCJ()->getJugador());
	this->getCJ()->setJugador(NULL);
}

void ControladorApp::refrescarBarraDeEstado() {
	this->barraEstado->refrescar(this->pantalla->getScreen());
}

void ControladorApp::setEstado(string unEstado) {
	this->barraEstado->setText(unEstado);
	refrescarBarraDeEstado();
}

void ControladorApp::desactivar(){
	this->activo = false;
}

void ControladorApp::redibujarVentana(string nombre) {
	this->CM->getMenu()->crearVentana(nombre);
	this->CM->getMenu()->activarVentana(nombre);
}

void ControladorApp::activarMenu() {
	if( this-> CM-> getMenu() -> getNombreVentanaActiva() == "SINGLEPLAYER_PERSONAJE") {
		this -> CM->getMenu() -> activarVentana("SINGLEPLAYER_NIVEL");
	} else if ( this-> CM-> getMenu() -> getNombreVentanaActiva() == "MULTIPLAYER_PERSONAJE"){
		this->redibujarVentana("MULTIPLAYER");
	}
	this->CM->activar();
}

void ControladorApp::activarJugador(){
	this->CJ->activar();
}

void ControladorApp::desactivarMenu(){
	this->CM->desactivar();
}

void ControladorApp::desactivarJugador(){
	this->CJ->desactivar();
}

ControladorJugador* ControladorApp::getCJ() {
	return this->CJ;
}

ControladorMenu* ControladorApp::getCM() {
	return this->CM;
}

Pantalla* ControladorApp::getPantalla(){
	return this->pantalla;
}

Servidor* ControladorApp::getServidor(){
	return this->servidor;
}

void ControladorApp::setNivelActivo(string nivel){
	this->nivelActivo = nivel;
}

string ControladorApp::getNivelActivo(){
	return this->nivelActivo;
}

void ControladorApp::setFinalizo(bool estado){
	m.lock();
	finalizoJuego = estado;
	m.unlock();
}

bool ControladorApp::getFinalizo(){
	return finalizoJuego;
}
