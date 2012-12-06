#ifndef LOADERJUGADOR_H
#define LOADERJUGADOR_H

#include "Loader.h"
#include "../excepciones/ExceptionIO.h"
#include "../vista/VistaElementoRotado.h"
#define PRIOR_NIVEL 0
#include "../vista/Imagen.h"
#include "../modelo/Elemento.h"
//#include "../app/ControladorApp.h"
class ControladorApp;
class LoaderJugador : public Loader{
	
	public:
		LoaderJugador(std::string archConfig);
		~LoaderJugador();
		Pantalla* cargarPantalla();
		AnimacionProtagonista* cargarEnemigo(std::string tipo, ID myID, Point* miPos);
		AnimacionAuto* cargarPersonajeAnimado(std::string tipo, ID myID, Point* miPos);
		//void cargarMusica();
		void cargarElementos();
		void cargarElementosJuego();
		void cargarElementosLista(std::string tipo, TextureHandler& handler );
		void cargarVistas(ListaParJugador jugadores, ID jugPrincipal);
		AnimacionProtagonista* cargarVidas();
		
	 private:
		static const string TAG;
		list<LoadPersonaje*> listaEnemigos;
		list<LoadPersonaje*> listaPersonajesAnimados;
		
		
		void cargarTexturas(vector<LoadTextura*>& texturas, TextureHandler& handler);
		void crearVistaNivel(int alto, int ancho, std::string nombreImagen , AnimacionProtagonista* protagonista , int anchoPantalla, int altoPantalla);
		AnimacionProtagonista* cargarProtagonistas(ListaLoadPersonaje protag, ListaParJugador jugadores, ID id);
	//	AnimacionProtagonista* crearVistaProtagonista(LoadPersonaje* prot, LoadPersonaje* protDefault, int velocidad, int anchoNivel, int altoNivel, ID idCliente);
		AnimacionProtagonista* crearVistaProtagonista(LoadPersonaje* prot, ID idCliente);
		vector<st_Animacion*>* cargarAnimaciones(list<LoadAnimacion*> animaciones);//, bool* quieto, bool* caminar);
		void cargarVistaPersonajes(list<LoadPersonaje*> animados, int anchoNivel, int altoNivel);
		AnimacionProtagonista* crearVistaEnemigo(LoadPersonaje* prot, ID unID, Point* posicion);
		AnimacionAuto* crearVistaPersonajeAnimado(LoadPersonaje* prot, ID unID, Point* posicion);
		
};


#endif /* LOADERJUGADOR_H */ 

