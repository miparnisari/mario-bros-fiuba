#ifndef JUGADORREMOTO_H
#define JUGADORREMOTO_H

#include "../comun/Hilo.h"
#include "../comun/Socket.h"
#include "../comun/Definiciones.h"
#include "../comun/BLQueue.h"
#include "../comun/Mutex.h"
#include "../comun/Utilitario.h"
#include "../comun/FactoryEventos.h"
#include "../modelo/Temporizador.h"
#include "EstadoJugador.h"

class JugadorRemoto: public Hilo
{
	public:
		JugadorRemoto(Socket* cliente, colaEventos* cola, ID id);
		~JugadorRemoto();
		void correr();
		bool activo();
		void detenerEntrada();
		void detenerJugador();
        void desconectarJugador();
		bool enviar(Evento* ev);
		ID getID();
		void keepAlive();
		bool isAlive();
			
	private:
		bool noEstoyEnElJuego;
		static const string TAG;
		Socket* entradaJugadores;
		colaEventos* colaB;
		ID myID;
		Temporizador temporizador;
		
};

#endif
