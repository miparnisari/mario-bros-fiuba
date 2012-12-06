#include "HiloAceptarJug.h"

const string HiloAceptarJug::TAG = "HiloAceptarJug";

using namespace std;

HiloAceptarJug::HiloAceptarJug(Puerto port, colaEventos* cb, Conexiones* conex, ListaEstados* listaEstados, Mutex* unMut,std::string nivel):Hilo() {
	try{
		entradaJugadores = new Socket(port);
		
	} catch (ExceptionConex& e){
		Logger::fatal(TAG, e.what());
		Logger::fatal(TAG, "Error al crear el socket que acepta nuevas conexiones.");
	}
	
	try{
		entradaJugadores->enlazar();
		
	} catch (ExceptionConex& e){
		Logger::fatal(TAG, e.what());
		Logger::fatal(TAG, "Error al enlazar el socket que escucha nuevas conexiones.");
		throw ExceptionConex("Error: puerto ocupado.");
	}
	
	conexiones = conex;
	listaE = listaEstados;
	id = 0;
	colaB = cb;
	m = unMut;
	archivoNivel = nivel;
}

HiloAceptarJug::~HiloAceptarJug() {
	this->detenerEntrada();
	delete this->entradaJugadores;
}

void HiloAceptarJug::detenerEntrada() {
	this->parar();
	entradaJugadores->desconectar();
}

bool HiloAceptarJug::activo() {
	return entradaJugadores->conectado();
}

vector<string> HiloAceptarJug::getFiles(string nivel) {
	LoaderMenu* loader;
	try {
		loader = new LoaderMenu("niveles/" + nivel + EXT_YAML);
	} catch (exception& e) {
		Logger::fatal(TAG, "Error al abrir el archivo del nivel.");
	}
	
	vector<string> archivos = loader->cargarRutaArchivos();
			
	delete(loader);
	return archivos;
}

void HiloAceptarJug::correr() {
	while (corriendo()) {
		Socket* sjugador = entradaJugadores->escucharConexion();
		if (sjugador) {
			Logger::info(TAG, "Servidor recibio una conexion.");
			id++;
			bool conexExitosa = true; 
			JugadorRemoto* jr = new JugadorRemoto(sjugador, colaB, id);
            EstadoJugador* ej = new EstadoJugador(id);
			try{
				jr->iniciar();
			} catch (exception &e){
				Logger::error(TAG, "No se pudo agregar al jugador al juego.");
				conexExitosa = false;
			}
			
			if (conexExitosa) {
				// metodo que envia todos los archivos necesarios para ejecutar la matrix
				this->enviarConfiguracion(jr, ej, id);
			}
			// Aviso la conexion de un jugador
			//m->signal();
			
		} else {
			this->detenerEntrada();
		}
	}
}

void HiloAceptarJug::enviarConfiguracion(JugadorRemoto* jr, EstadoJugador* ej, ID id){
	// Agrego a la lista de manera segura
	// Server tambien tiene esta lista y la usa para enviar
	LoaderMenu* loader;
	try {
		loader = new LoaderMenu("niveles/" + archivoNivel + EXT_YAML);
	} catch (exception& e) {
		Logger::fatal(TAG, "Error al abrir el archivo del nivel.");
	}
		
	vector <string> archivos = getFiles(archivoNivel);
	
	list<st_MusicSound*> sonidos = loader->cargarMusica();
	
	for(list<st_MusicSound*>::iterator it = sonidos.begin(); it != sonidos.end(); ++it){
		archivos.push_back((*it)->file);
	}
	EventoEnviarArchivos ea(id, DIR);
	jr->enviar(&ea);
	

	// Aca tengo que enviar los archivos necesarios para ejecutar el juego
	for (int i=0; i < archivos.size(); i++) {
		EventoArchivo econfig(id, archivos[i]);
		jr->enviar(&econfig);
	}
	for(list<st_MusicSound*>::iterator it = sonidos.begin(); it != sonidos.end(); ++it){
		(*it)->file = "tmp/" + (*it)->file;
		EventoCargarSonido ecs((*it)->tipo, (*it)->tag, (*it)->file);
		jr->enviar(&ecs);
	}
	
	// El servidor informa el nivel activo
	EventoNivel evNivel(id, archivoNivel);

	jr->enviar(&evNivel);

	ControladorApp::getInstance()->setEstado("Archivos enviados.");
	Logger::info(TAG,"Archivos enviados.");
	EventoJugadorConectado* eventoJugador = new EventoJugadorConectado(id);
	m->lock();

	for (IterConexiones it = conexiones->begin(); it != conexiones->end(); ++it){
		(*it)->enviar(eventoJugador);
	}
	m->unlock();
	
	EventoIniciarJuego ei(id);
	jr->enviar(&ei);
	
	EventoOKServidor eOK(id);
	jr->enviar(&eOK);

	m->lock();
	conexiones->push_back(jr);
	listaE->push_back(ej);
	m->unlock();
	
	delete(loader);
	//delete(eventoJugador)  FIXME
	for(list<st_MusicSound*>::iterator it = sonidos.begin(); it != sonidos.end(); ++it){
		delete(*it);
	}
}
