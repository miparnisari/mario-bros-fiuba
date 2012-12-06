#include "FactoryEventos.h"

const string FactoryEventos::TAG = "FactoryEventos";

Evento* FactoryEventos::construir(VectorChar v){
	Utilitario u;
	
	std::string tipoEvento = "";
	for (IterVectorChar it = v.begin(); it != v.end() and (*it) != SEP ; ++it)
		tipoEvento += (*it);
	
	if (tipoEvento == EVENTO_SALIR)
			return new EventoSalir(v);
	else if (tipoEvento == EVENTO_TECLADO)
			return new EventoTeclado(v);
	else if (tipoEvento == EVENTO_MOVERVISTA)
			return new EventoMoverVista(v);
	else if (tipoEvento == EVENTO_INICIARJUEGO)
			return new EventoIniciarJuego(v);
	else if (tipoEvento == EVENTO_ARCHIVO)
			return new EventoArchivo(v);
	else if (tipoEvento == EVENTO_JUGADORDESCONECTADO)
			return new EventoJugadorDesconectado(v);
	else if (tipoEvento == EVENTO_PERSONAJESELECT)
			return new EventoPersonajeSelect(v);
    else if (tipoEvento == EVENTO_OKSERVIDOR)
            return new EventoOKServidor(v);
    else if (tipoEvento == EVENTO_ENV_ARCHIVOS)
            return new EventoEnviarArchivos(v);
    else if (tipoEvento == EVENTO_NIVEL)
			return new EventoNivel(v);
	else if (tipoEvento == EVENTO_PERSONAJES_USADOS)
			return new EventoPersonajesUsados(v);
	else if (tipoEvento == EVENTO_KEEPALIVE)
			return new EventoKeepAlive(v);
	else if (tipoEvento == EVENTO_VISTASLOOP)
			return new EventoVistasLoop(v);
	else if (tipoEvento == EVENTO_JUGADORCONECTADO)
			return new EventoJugadorConectado(v);
	else if (tipoEvento == EVENTO_CREAR_ENEMIGO)
			return new EventoCrearEnemigo(v);
	else if (tipoEvento == EVENTO_CREAR_PERSONAJEANIMADO)
			return new EventoCrearPersonajeAnimado(v);
	else if (tipoEvento == EVENTO_MOVER_ENEMIGO)
			return new EventoMoverEnemigo(v);
	else if (tipoEvento == EVENTO_SONIDO)
			return new EventoSonido(v);
	else if (tipoEvento == EVENTO_CARGAR_SONIDO)
			return new EventoCargarSonido(v);
	else if (tipoEvento == EVENTO_ELIMINAR_VISTA_ENEMIGO)
			return new EventoEliminarEnemigo(v);
	else if (tipoEvento == EVENTO_VIDAS)
			return new EventoVidas(v);	
	else if (tipoEvento == EVENTO_DIBUJAR)
			return new EventoDibujar(v);
	else if (tipoEvento == EVENTO_GAMEOVER)
			return new EventoGameOver(v);
	else if (tipoEvento == EVENTO_VISTANIVEL)
			return new EventoVistaNivel(v);
	else {
			Logger::warn(TAG, "No puedo parsear el evento " + tipoEvento);
			return NULL;
		}
}
