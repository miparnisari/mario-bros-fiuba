#ifndef EVENTOENVIARARCHIVOS_H
#define EVENTOENVIARARCHIVOS_H

#include "Evento.h"
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include "../other/Logger.h"

class EventoEnviarArchivos: public Evento
{
	public:
		EventoEnviarArchivos(VectorChar v);
		EventoEnviarArchivos(ID unID, std::string archivo);
		VectorChar serializar();
		void hidratar(VectorChar v);
		void actuar(ResolvedorJugador* res);
	
	private:
		std::string dir;
		static const string TAG;
		
		void crearDirectorio(std::string unDirect);
};

#endif /* EVENTOENVIARARCHIVOS_H */ 
