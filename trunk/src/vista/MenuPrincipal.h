#ifndef MENUPRINCIPAL_H_
#define MENUPRINCIPAL_H_

#include <iostream>
#include <map>



#include "../other/Logger.h"
#include "../excepciones/Excepciones.h"
#include "../controlador/loaderMenu.h"
#include "../comun/Utilitario.h"
#include "../comun/Definiciones.h"

class ControladorMenu;
class Componente;
class Ventana;
class Solapa;
class Etiqueta;
class Textbox;
class CuadroDeSeleccion;
class Imagen;
class MenuPrincipal {

	private:
		static const std::string TAG;
		Ventana*					ventanaActiva;
		map<std::string,Ventana*>	ventanas;

		void elegirPersonaje();
				
		void crearVentanaInicial();
		void crearVentanaSinglePlayerNivel();
		void crearVentanaSinglePlayerPersonaje();
		void crearVentanaMultiplayer();
		void crearVentanaMultiplayerPersonaje();
	
	public:
		MenuPrincipal();
		~MenuPrincipal();

		std::string 	getData(std::string componenteID);
		Ventana*		getVentanaActiva();
		
		void crearVentana(string nombreVentana);
		void agregarVentana(Ventana* v);
		void borrarVentana(string nombreVentana);
		void activarVentana(string idVent);
		
		void manejarEventos(SDL_Event event);
		bool refrescar(SDL_Surface* destino);
		void iniciar();
		std::string getNombreVentanaActiva();
};

#endif /* MENUPRINCIPAL_H_ */
