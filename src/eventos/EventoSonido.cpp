#include "EventoSonido.h"
#include "../jugador/ResolvedorJugador.h"

EventoSonido::EventoSonido(VectorChar v): Evento(v) {
	this->hidratar(v);
}

EventoSonido::EventoSonido(std::string unTipo, std::string unTag): Evento() {
	tipo = unTipo;
	tag = unTag;
}

VectorChar EventoSonido::serializar(){
	Utilitario utilitario;
	VectorChar v;
	std::string mensaje = EVENTO_SONIDO;
	mensaje += SEP;
	mensaje += tipo;
	mensaje += SEP;
    mensaje += tag;

	utilitario.borrarCaracter(mensaje, SEPFIN);
	// Borro todos los SEPFIN y agrego uno al final
	
	utilitario.agregarCaracteres(v, mensaje);
	return v;
}

void EventoSonido::hidratar(VectorChar v) {
	Utilitario utilitario;
	std::string mensaje = utilitario.convertirVectorAString(v);
	// El Index 0 es el tipo de evento que usaron para instanciar esta clase
	tipo = utilitario.separar(mensaje, SEP, 1);
	tag = utilitario.separar(mensaje, SEP, 2);
}

void EventoSonido::actuar(ResolvedorJugador* res){
	
	if (tipo == "S") res->reproducirSonido(tag);
	else if (tipo == "M") res->reproducirMusica(tag);
}
