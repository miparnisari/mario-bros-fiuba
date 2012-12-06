#ifndef SERVIDOR_H
#define SERVIDOR_H

#include "../comun/Hilo.h"
#include "../comun/Socket.h"
#include "../comun/Definiciones.h"
#include "../comun/Utilitario.h"
#include "../comun/BLQueue.h"
#include "../comun/Mutex.h"
#include "../controlador/EventHandler.h"
#include "../eventos/Evento.h"
#include "HiloResolverMovimientos.h"
#include "ResolvedorServidor.h"
#include "../modelo/Juego.h"
#include "../controlador/loaderServidor.h"
#include "../other/Logger.h"
#include "../controlador/FpsHandler.h"
#include "../eventos/EventoSonido.h"
#include "EstadoEnemigo.h"

class HiloEnviarJug;
class HiloAceptarJug;
class ControladorJugador;
class ControladorApp;
class Protagonista;
class Servidor: public Hilo
{
	public:
		Servidor();
		Servidor(std::string unPuerto, std::string nivel, std::string maxJugadores, std::string modo);
		~Servidor();
		void correr();
        void detener();
		bool hayCantidadMin();
		void resolverMovimientos();
		void resolverColisiones();
		void setJuego(Juego* unJuego);
		Juego* getJuego();
		Conexiones* getConexiones();
		ListaParJugador* getListaPersonajesOcupados();
		Mutex* getMutex();
		void enviarEventoJugadores(Evento* ev);
		int getMaxJugadores();
		void enviarEventoJugador(Evento* ev, ID unID);
		void enviarEventoRestoJugador(Evento* ev, ID unID);
		void aumentarCantJugadores();
		void disminuirCantJugadores();
		void mantenerVivo();
		void resolverEventos();
		void checkConexPerdidas(ID* jugadorCaido);
		void agregarEnemigo(Enemigo* enemigo);
		int getDimensionEnemigo(std::string tipo, int* ancho, int* alto);
		void eliminarEnemigo(Enemigo* enemigo);
		// Tareas necesarias que se ejecutan periodicamente sobre el servidor
		void tareasMantenimiento();
		void informarGanador();
		void setFinalizo(bool estado);
		bool getFinalizo();
		void setWaitSP(bool estado);
		void actualizarPosicionEstado(ID unID,Protagonista* protagonista);
	private:
		bool waitSP;
		bool validarPuerto(std::string unPuerto);
		static const string TAG;
		Mutex m;
		Temporizador tempServer;
		Temporizador tempEspera;
		colaEventos* colaBloq;
	// conexiones es un puntero a una lista de JugadorRemoto*
		Conexiones* conexiones;
        ListaEstados* listaE;
        EstadoEnemigo* estadoEnemigos;
		ResolvedorServidor* res; 
		HiloAceptarJug* hiloAceptar;
		HiloResolverMovimientos* hiloResolverMovimientos;
		HiloEnviarJug* hiloEnviarJug;
        EventHandler* eventH;
        ListaEventos* listaEv;
        ListaParJugador* listaPersonajesOcupados;
        LoaderServidor* loaderServidor;
        Juego* juego;
        int maxJugadores;
        int cantJugadores;
		bool juegoFinalizado;
        std::string modo;
};

#endif /* SERVIDOR_H */ 
