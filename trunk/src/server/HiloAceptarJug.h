#ifndef HILOACEPTARJUG_H
#define HILOACEPTARJUG_H

#include "../comun/Hilo.h"
#include "../comun/Socket.h"
#include "../comun/Definiciones.h"
#include "../comun/BLQueue.h"
#include "../comun/Mutex.h"
#include "JugadorRemoto.h"
#include "../controlador/loaderMenu.h"
#include "../eventos/EventoArchivoNivel.h"
#include "../eventos/EventoJugadorConectado.h"
#include "../app/ControladorApp.h"

class HiloAceptarJug: public Hilo
{
	public:
		HiloAceptarJug(Puerto port, colaEventos* cola, Conexiones* conex, ListaEstados* listaEstados, Mutex* unMut, std::string nivel);
		~HiloAceptarJug();
		void correr();
		bool activo();
		void detenerEntrada();
		std::vector<string> getFiles(std::string nivel);
		void enviarConfiguracion(JugadorRemoto* jr, EstadoJugador* ej, ID id);	
	private:
		static const string TAG;
		Mutex* m;
		Socket* entradaJugadores;
		std::string archivoNivel;
		// Lista con "jugadores"  
		Conexiones* conexiones;
        ListaEstados* listaE;
		colaEventos* colaB;
		ID id;
};

#endif
