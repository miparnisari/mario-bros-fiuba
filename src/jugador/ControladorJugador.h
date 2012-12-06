#ifndef CONTROLADORJUGADOR_H
#define CONTROLADORJUGADOR_H

#include "../comun/Definiciones.h"
#include "../modelo/Point.h"
#include "../modelo/Elemento.h"
#include "../vista/Pantalla.h"
#include "../vista/Imagen.h"
#include "../other/Logger.h"
#include "../controlador/loaderJugador.h"
#include "../controlador/loaderServidor.h"
#include "../comun/Mutex.h"
#include "Jugador.h"
#include "../comun/Utilitario.h"

class ControladorApp;
class ManejadorEventosJugador;

class MenuPrincipal;


class ControladorJugador
{
	public:
		ControladorJugador();
		virtual ~ControladorJugador();
		static ControladorJugador* getInstance();
		void agregarVista(Imagen* vista);
		void agregarVistaEnemigo(std::string tipoEnemigo, ID unID, Imagen* vista);
		void agregarVistaBonus(st_VistasBonus vista);
		void moverVistaEnemigo(std::string tipoEnemigo, ID unID, Point* posicion, std::string tipoMov);
		void eliminarVistaEnemigo(std::string tipoEnemigo, ID unID);
		void agregarVistaGeneral(Imagen* vista);
		void agregarVistaBonus(st_VistasBonus* vistaBonus);
		void setVistaPrincipal(Imagen* vistaPrincipal);
		void simular();
		bool refrescar(Pantalla* p);
		bool estaActivo();
		void moverVista(ID unID, Point* posicion, std::string tipo);
		void manejarEventos();
		void comenzarJuego(ListaParJugador* unaLista);
		void conectarJugador(std::string puerto, std::string host);
		void setEstadoConexJugador(bool unEstado);
		bool JugadorEstaConectado();
		void enviarPersonaje(ID id, std::string personajeElegido);
		void cargarJuego(std::string archConfig, std::string archDefecto, ListaParJugador jugadores);
		void activar();
		void desactivar();
		void setID(ID unID);
		void setIDRecibido (bool estado);
		ID getID();
		Jugador* getJugador();
		void setJugador(Jugador* j);
		void agregarProtagonista(parJugador* par);
		void setRespuesta(bool estado);
		void desocuparVistaPersonaje(ID unID);
		void limpiarListas();
		void eliminarVistasInactivas();
		void desconectarASAP(bool valor);
		AnimacionProtagonista* cargarEnemigo(std::string tipo, ID myID, Point* miPos);
		AnimacionAuto* cargarPersonajeAnimado(std::string tipo, ID myID, Point* miPos);
		void modificarVidas(int cantVidas);
		AnimacionProtagonista* getVistaVidas();
		void terminarJuego(std::string mensaje);
		void setEstadoBonus(std::string elemento, bool estado);
		void setPosVistaNivel(Point* pos);
		
		bool desconectar;
		
	private:
		static const string TAG;
		ID myID;
		bool ID_Recibido;
		bool respuesta;
		bool activo;
		
		bool jugadorConectado; // Booleano que indica si el jugador esta conectado. Se setea en false solo cuando sale del juego
		listaVistas listaAnimaciones;
		listaVistas AnimacionesEnJuego;
		
		ManejadorEventosJugador* manejador;
		Jugador* jugador;
		LoaderJugador* loader;
		Mutex m;
				
		VistasEnemigos vistasEnemigos;
		AnimacionProtagonista* vistaVidas; 
		list<st_VistasBonus*> vistasBonus;
};

#endif /* CONTROLADORJUGADOR_H */ 
