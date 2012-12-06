#ifndef EVENTOARCHIVO_H
#define EVENTOARCHIVO_H
#include "Evento.h"
#include <iostream>
#include <fstream>
#include "../other/Logger.h"

class ControladorJugador;
class ControaldorApp;

class EventoArchivo: public Evento
{
	public:
		EventoArchivo(VectorChar v);
		EventoArchivo(ID unID, std::string archivo);
		VectorChar serializar();
		void hidratar(VectorChar v);
		void actuar(ResolvedorJugador* res);
	private:
		static const string TAG;
	protected:
		std::string archivo;
};

#endif /* EVENTOARCHIVO_H */ 
