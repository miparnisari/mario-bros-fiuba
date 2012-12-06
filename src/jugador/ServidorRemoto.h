#ifndef SERVIDORREMOTO_H
#define SERVIDORREMOTO_H

#include "../comun/Hilo.h"
#include "../comun/Socket.h"
#include "../comun/Definiciones.h"
#include "../eventos/Evento.h"
#include "../comun/FactoryEventos.h"
#include "../modelo/Temporizador.h"
#include "ResolvedorJugador.h"

class ControladorJugador;
class ControladorApp;
class ServidorRemoto: public Hilo
{
	public:
		ServidorRemoto(Socket* server, ResolvedorJugador* unRes);
		~ServidorRemoto();
		void correr();
		bool activo();
		void detenerEntrada();
		bool enviar(Evento* ev);
		void keepAlive();
		bool isAlive();
		Temporizador temporizador;	
	private:
		
		static const string TAG;
		Socket* entradaServidor;
		ResolvedorJugador* resolvedor;

};

#endif
