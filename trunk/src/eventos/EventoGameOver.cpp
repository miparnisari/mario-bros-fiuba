#include "EventoGameOver.h"
#include "../jugador/ResolvedorJugador.h"

EventoGameOver::EventoGameOver(VectorChar v): Evento(v) {
	this->hidratar(v);
}

EventoGameOver::EventoGameOver(std::string unEstado): Evento() {
	this->estado = unEstado;
}

VectorChar EventoGameOver::serializar(){
	Utilitario utilitario;
	VectorChar v;
	std::string mensaje = EVENTO_GAMEOVER;
	mensaje += SEP;
	mensaje += estado;
    utilitario.borrarCaracter(mensaje, SEPFIN);
	// Borro todos los SEPFIN y agrego uno al final
	
	utilitario.agregarCaracteres(v, mensaje);
	return v;
}

void EventoGameOver::hidratar(VectorChar v) {
	Utilitario utilitario;
	std::string mensaje = utilitario.convertirVectorAString(v);
	// El Index 0 es el tipo de evento que usaron para instanciar esta clase
	estado = utilitario.separar(mensaje, SEP, 1);
}

void EventoGameOver::actuar(ResolvedorJugador* res){
	res->terminarJuego(estado);
	res->detenerMusica();
}
