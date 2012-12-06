#ifndef EVENTOSONIDO_H
#define EVENTOSONIDO_H

#include "../modelo/Point.h"
#include "Evento.h"
#include "../modelo/Enemigo.h"
class ResolvedorJugador;

class EventoSonido: public Evento
{
	public:
		EventoSonido(VectorChar v);
		EventoSonido(std::string unTipo, std::string unTag);
		VectorChar serializar();
		void hidratar(VectorChar v);
		void actuar(ResolvedorJugador* res);
    private:
		std::string tipo;
		std::string tag;
};

#endif /* EVENTOSONIDO_H */ 
