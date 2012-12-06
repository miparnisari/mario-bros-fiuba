#ifndef JUGADOR_H
#define JUGADOR_H
#include "../comun/Definiciones.h"
#include "ResolvedorJugador.h"
#include "ServidorRemoto.h"
#include "../excepciones/Excepciones.h"
#include "../comun/Utilitario.h"
class Jugador
{
	public:
		Jugador();
		Jugador(std::string unPuerto, std::string host);
		virtual ~Jugador();
		
		bool setActivo(bool estado);
		bool estaActivo();
		void setID(ID unID);
		ID getID();
		bool socketEstaConectado();
		void detener();
		ServidorRemoto* getServidorRemoto();
		ResolvedorJugador* getResolvedor();
	    
	private:
		static const string TAG;
		ID myID;
		Socket* sock;
		ResolvedorJugador* resolvedor;
		ServidorRemoto* servidor;
		bool activo;
		
};

#endif /* JUGADOR_H */ 
