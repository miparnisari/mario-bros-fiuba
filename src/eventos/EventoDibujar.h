#ifndef EVENTODIBUJAR_H
#define EVENTODIBUJAR_H

#include "Evento.h"

class ResolvedorJugador;

class EventoDibujar: public Evento
{
	public:
		EventoDibujar(VectorChar v);
		EventoDibujar(std::string elemento, bool activo);
		VectorChar serializar();
		void hidratar(VectorChar v);
		void actuar(ResolvedorJugador* res);
    private:
		std::string elemento;
		bool activo;
};

#endif /* EVENTODIBUJAR_H */ 
