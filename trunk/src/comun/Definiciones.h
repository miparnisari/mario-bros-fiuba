#ifndef DEFINICIONES_H_
#define DEFINICIONES_H_
#include <list>
#include <utility>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include "BLQueue.h"
//#include "SDL/SDL.h"

class Point;
class LoadPersonaje;
class JugadorRemoto;
class Imagen;
class Evento;
class EstadoJugador;
class PersonajeAnimado;
class EventoMoverVista;
class Enemigo;
class Bonus;
class VistaElemento;

typedef unsigned short int Puerto;
typedef unsigned short int ID;
typedef std::list<JugadorRemoto*> Conexiones;
typedef std::list<JugadorRemoto*>::iterator IterConexiones;
typedef std::list<Imagen*> listaVistas;
typedef std::list<Imagen*>::iterator IterlistaVistas;
typedef BLQueue<Evento*> colaEventos;
typedef std::pair<std::string, ID> parJugador;
typedef std::pair<std::string, ID> parBonus;
typedef std::pair<PersonajeAnimado*, ID> parPersAnimado;
typedef std::pair<LoadPersonaje*, ID> parProt;
typedef std::list<LoadPersonaje*> ListaLoadPersonaje;
typedef std::list<LoadPersonaje*>::iterator IterPersonajes;
typedef std::list<parJugador*>::iterator IterParJugador;
typedef std::list<parProt*> ListaParProt; 
typedef std::list<parProt*>::iterator IterListaParProt; 
typedef std::list<parJugador*> ListaParJugador;
typedef std::list<EstadoJugador*> ListaEstados;
typedef std::list<EstadoJugador*>::iterator IterListaEstados;
typedef std::list<Evento*> ListaEventos;
typedef std::list<Evento*>::iterator IterListaEventos;
typedef std::list<parPersAnimado*> ListaParPersonajeAnimado;
typedef std::vector<char> VectorChar;
typedef std::vector<char>::iterator IterVectorChar;
typedef std::vector<EventoMoverVista*> VectorEventoMV;
typedef std::vector<EventoMoverVista*>::iterator IterVectorEventoMV;

typedef std::map<parJugador, Bonus*> Bonuses;
typedef std::map<parJugador, Bonus*>::iterator IterBonus;

typedef std::map<parJugador, Enemigo*> Enemigos;
typedef std::map<parJugador, Enemigo*>::iterator IterEnemigos;
// Clave : tipoEnemigo,ID -> valor  = imagen
typedef std::map<parJugador, Imagen*> VistasEnemigos;
typedef std::map<parJugador, Imagen*>::iterator IterVistasEnemigos;


#define PI 3.14159
#ifndef TIPOMOVIMIENTO_H_
#define TIPOMOVIMIENTO_H_

enum tipoMovimiento { arriba, abajo, derecha, izquierda, 
					quietoizq, quietoder,
					cayendoizq, cayendoder,
					saltandoizq, saltandoder };

typedef struct{
	bool activo;	
	Imagen* imagen;
	std::string nombre;
}st_VistasBonus;
					
#endif /* TIPOMOVIMIENTO_H_ */

/* PARA MODO SINGLE PLAYER */
#define DEFAULT_HOST "localhost"
#define DEFAULT_PORT "10000"

/* PARA CONEXIONES DE RED */
#define PUERTO 10000
#define MIN_CONEX 2
#define CANT_TECLAS 323
#define ID_INVALIDO 0
#define SEGS_TIMEOUT 20
#define DIR "tmp"

/* PARA PRUEBAS */
// Intervalo de tiempo cada cuanto el servidor pregunta si el cliente esta vivo
#define TIEMPO_ESPERA_SERVIDOR 15
// Intervalo de tiempo cada cuanto el cliente avisa que esta vivo
#define TIEMPO_ALIVE_JUGADOR 3

#define TIEMPO_ALIVE_SERVER 5
#define FPS 40
#define DEFAULT_FPS 30
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define SCREEN_BPP 32
#define LEVEL_WIDTH 800
#define LEVEL_HEIGHT 600


// COSAS DEL JUEGO
#define CANT_VIDAS 5
#define TIEMPO_DESPUES_MORIR 3 // segundos invencible despues de morir
#define TIEMPO_VUELO 10

#define HORIZONTAL 1
#define VERTICAL 2
#define HORIZONTAL_Y_VERTICAL 3
#define SENSIBILIDADPERS 0.95
#define SENSIBILIDADELEM 1

/* TIPOS DE EVENTOS */
#define EVENTO_PERSONAJE_OCUPADO "EPO"
#define EVENTO_OKSERVIDOR "EOKS"
#define EVENTO_PERSONAJESELECT "EPS"
#define EVENTO_TECLADO "ET"
#define EVENTO_SALIR "ES"
#define EVENTO_JUGADORDESCONECTADO "JD"
#define EVENTO_JUGADORCONECTADO "JC"
#define EVENTO_INICIARJUEGO "EI"
#define EVENTO_ARCHIVO "EA"
#define EVENTO_MOVERVISTA "EMV"
#define EVENTO_MOVER_ENEMIGO "EME" 
#define EVENTO_VISTASLOOP "EVL"
#define EVENTO_ENV_ARCHIVOS "EEA"
#define EVENTO_NIVEL "EN"
#define EVENTO_CREAR_ENEMIGO "ECE"
#define EVENTO_CREAR_PERSONAJEANIMADO "ECPA"
#define EVENTO_PERSONAJES_USADOS "EPU"
#define EVENTO_KEEPALIVE "EKA"
#define EVENTO_SONIDO "ESO"
#define EVENTO_CARGAR_SONIDO "ECS"
#define EVENTO_ELIMINAR_VISTA_ENEMIGO "EEVE"
#define EVENTO_VIDAS "EV"
#define EVENTO_DIBUJAR "ED"
#define EVENTO_GAMEOVER "EGO"
#define EVENTO_VISTANIVEL "EVN"

#define SEPFIN '\0'
#define SEP ';'
#define SEP_TAM '|'
#define SEP_PAIR '-'
#define SEP_LISTA_PAIR '/'
#define SEP_EVENTO '#'
#define STR_NULA ""

// TAGS DE IMAGENES
#define ESPERANDO "esperando"
#define CORAZON "corazon"
#define ICONO_ARMADURA "iconoArmadura"
#define GANAR "ganar"
#define PERDER "perder"

/* PARA TEXTO */
#define CYAN 0x99FFCC
#define BLACK 0x000000
#define WHITE 0xFFFFFF
#define BEIGE 0xfff9bd
#define ORANGE 0xFFCA12
#define GREY 0xD3C9CA
#define DARK_GREY 0xB0AEAE
#define FONT "fonts/Courier_New.ttf"
#define FONT_SIZE 18

/* PARA MENU */
#define MENU_INNER_BORDER 60
#define ALTO_BOTON 30
#define ANCHO_BOTON 150
#define IMG_FONDO_MENU "images/fondo_menu.jpg"

/* PARA PARSER */
#define EXT_YAML ".yaml"

#endif /* DEFINICIONES_H_ */
