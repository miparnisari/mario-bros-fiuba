#include "FactoryNivel.h"
const string FactoryNivel::TAG = "FactoryNivel";

Nivel* FactoryNivel::crear(int alto, int ancho, std::string nombreImagen, int scroll, int anchoPantalla,int altoPantalla) {
	/*Nivel* nivel = new Nivel(alto, ancho);
	if (!nivel) Logger::error(TAG, "No se pudo crear el objeto nivel.");
	VistaNivel* image = new VistaNivel(nombreImagen, Juego::getInstance()->getProtagonista(),scroll, anchoPantalla, altoPantalla, ancho, alto, PRIOR_NIVEL);
	if (!image) Logger::error(TAG, "No se pudo crear la imagen del nivel.");
	Juego::getInstance()->agregarVista(image);
	return nivel;*/
}
