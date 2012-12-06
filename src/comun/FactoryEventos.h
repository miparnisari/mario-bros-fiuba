
#ifndef FACTORYEVENTOS_H
#define FACTORYEVENTOS_H
#include "Utilitario.h"
#include "Definiciones.h"
#include "../eventos/EventoTeclado.h"
#include "../eventos/EventoSalir.h"
#include "../eventos/EventoIniciarJuego.h"
#include "../eventos/EventoArchivo.h"
#include "../eventos/EventoJugadorDesconectado.h"
#include "../eventos/EventoOKServidor.h"
#include "../eventos/EventoMoverVista.h"
#include "../eventos/EventoNivel.h"
#include "../eventos/EventoPersonajesUsados.h"
#include "../eventos/EventoKeepAlive.h"
#include "../eventos/EventoVistasLoop.h"
#include "../eventos/EventoJugadorConectado.h"
#include "../eventos/EventoCrearEnemigo.h"
#include "../eventos/EventoCrearPersonajeAnimado.h"
#include "../eventos/EventoEnviarArchivos.h"
#include "../eventos/EventoMoverEnemigo.h"
#include "../eventos/EventoCargarSonido.h"
#include "../eventos/EventoSonido.h"
#include "../eventos/EventoEliminarEnemigo.h"
#include "../eventos/EventoVidas.h"
#include "../eventos/EventoDibujar.h"
#include "../eventos/EventoGameOver.h"
#include "../eventos/EventoVistaNivel.h"
#include "../other/Logger.h"

class FactoryEventos
{
	public:
		static Evento* construir(VectorChar v);
	private:
		static const string TAG;
};

#endif /* FACTORYEVENTOS_H */ 
