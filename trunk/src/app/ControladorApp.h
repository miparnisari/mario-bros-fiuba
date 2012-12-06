#ifndef CONTROLADORAPP_H
#define CONTROLADORAPP_H

#include "../vista/Pantalla.h"
#include "../server/Servidor.h"
#include "../controlador/loaderJugador.h"
#include "../controlador/ControladorMenu.h"
#include "../jugador/ControladorJugador.h"
#include "../other/Logger.h"
#include "../comun/Definiciones.h"
#include "../excepciones/Excepciones.h"

class BarraDeEstado;

class ControladorApp
{
	private:
		static const string 	TAG;
		static ControladorApp*	instance;
		bool 					activo;
		bool					modoSinglePlayer;
		bool					finalizoJuego;
		BarraDeEstado*			barraEstado;
		Pantalla* 				pantalla;
		Servidor* 				servidor;
		ControladorJugador* 	CJ;
		ControladorMenu* 		CM;
		FpsHandler* 			manejadorFps;
		std::string 			nivelActivo;
		Temporizador			temporizador;
		
		Mutex					m;
		Mutex					mutexBarraEstado;
		
		
	public:
		bool singlePlayerSelect;
		ControladorApp(Pantalla* p);
		~ControladorApp();
		
		ControladorJugador* getCJ();
		ControladorMenu* getCM();
		Pantalla* getPantalla();
		Servidor* getServidor();
		std::string getNivelActivo();
		bool getFinalizo();
		
		static ControladorApp* getInstance();
		static void destroyInstance();
		
		void setFinalizo(bool estado);
		void setBarraEstado(int fontSizeTexto);
		void setEstado(std::string unEstado);
		void setServidor(Servidor* serv);
		void setNivelActivo(std::string nivel);
		
		void redibujarVentana(string nombre);
		void destruirServidor();
		void manejarEventos();
		void refrescarPantalla();
		void refrescarBarraDeEstado();
		void simular();
		bool crearServidor(bool singlePlayer = false);
		void conectarJugador(bool singlePlayer);
		void desactivar();
		void activarMenu();
		void activarJugador();
		void desactivarMenu();
		void desactivarJugador();
		void clienteEnviarPersonaje();
		void salidaPorDesconexion();
		void volverAlMenuPrincipal();
		
};

#endif /* CONTROLADORAPP_H */ 
