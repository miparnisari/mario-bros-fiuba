#ifndef TIPOSDEDATOS_H_
#define TIPOSDEDATOS_H_

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include "loadpersonaje.h"
#define MAXIMG 10

using namespace std;
class AnimacionesAuto;

typedef struct {
	string ancho, alto;
} st_Pantalla;

typedef struct {
	string vel_personaje, margen_scroll;
} st_Parametros;

typedef struct {
	string file;
    string tag;
    string tipo;
} st_MusicSound;

typedef struct{
	string x,y;
} st_Posicion;

typedef struct {
	string ancho, alto, x, y;
	//string listaDeAnimaciones[MAXIMG];
	//unsigned cantidadDeImagenes;
	string sprites;
	//list <st_Animacion> animaciones;
} st_Protagonista;

typedef struct {
	string ancho,alto,periodo,sprites;
	string cantidadDeImagenes;
	string nombre;
	string listaDeAnimaciones[MAXIMG];
} st_Personaje;

typedef struct {
	string viga,madera;
} st_Textura;

typedef struct {
	string nombre;
	string x,y;
} st_PersonajesACargar;

typedef struct {
	string textura;
	string x,y,ancho,alto;
	string rozamiento;
} st_PlataformasACargar;

typedef struct {
	int offset, cantidad, periodo;
	string ejecucion;
} st_Animacion;

typedef struct {
	string ancho, alto, piso;
	string fondo;
	list <LoadPersonaje*> listaPersonajes;
	list <LoadPersonaje*> listaProtagonistas;
	list <LoadPersonaje*> listaEnemigos;
	LoadPersonaje* vida;
} st_Nivel;

typedef struct{
	int ancho,alto;
	string nombrePers;
	string nombreImagen;
	int potenciaSalto;
	int velocidad;
	vector<st_Animacion*>* animaciones;
} st_PersMenu;

typedef pair <string, string> ParTexto;

#endif /*TIPOSDEDATOS_H_*/
