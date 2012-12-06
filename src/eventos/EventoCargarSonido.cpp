#include "EventoCargarSonido.h"
#include "../jugador/ResolvedorJugador.h"

EventoCargarSonido::EventoCargarSonido(VectorChar v): Evento(v) {
	this->hidratar(v);
}

EventoCargarSonido::EventoCargarSonido(std::string unTipo, std::string unTag, std::string unaRuta): Evento() {
	tipo = unTipo;
	tag = unTag;
	ruta = unaRuta;
}

VectorChar EventoCargarSonido::serializar(){
	Utilitario utilitario;
	VectorChar v;
	std::string mensaje = EVENTO_CARGAR_SONIDO;
	mensaje += SEP;
	mensaje += tipo;
    mensaje += SEP;
    mensaje += tag;
	mensaje += SEP;
    mensaje += ruta;
	utilitario.borrarCaracter(mensaje, SEPFIN);
	// Borro todos los SEPFIN y agrego uno al final
	
	utilitario.agregarCaracteres(v, mensaje);
	return v;
}

void EventoCargarSonido::hidratar(VectorChar v) {
	Utilitario utilitario;
	std::string mensaje = utilitario.convertirVectorAString(v);
	// El Index 0 es el tipo de evento que usaron para instanciar esta clase
	tipo = utilitario.separar(mensaje, SEP, 1);
	tag = utilitario.separar(mensaje, SEP, 2);
	ruta = utilitario.separar(mensaje, SEP, 3);
}

void EventoCargarSonido::actuar(ResolvedorJugador* res){
	if (tipo == "S") res->cargarSonido(ruta, tag);
	else if (tipo == "M") res->cargarMusica(ruta, tag);
}
