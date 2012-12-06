#ifndef EVENTOCARGARSONIDO_H
#define EVENTOCARGARSONIDO_H

#include "Evento.h"
class ResolvedorJugador;

class EventoCargarSonido: public Evento
{
	public:
		EventoCargarSonido(VectorChar v);
		EventoCargarSonido(std::string unTipo, std::string unTag, std::string unaRuta);
		VectorChar serializar();
		void hidratar(VectorChar v);
		void actuar(ResolvedorJugador* res);
    private:
		std::string tipo;
		std::string tag;
		std::string ruta;
};

#endif /* EVENTOCARGARSONIDO_H */ 
