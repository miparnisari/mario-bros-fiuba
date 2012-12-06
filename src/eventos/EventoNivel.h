#ifndef EVENTONIVEL_H
#define EVENTONIVEL_H
#include "../jugador/ResolvedorJugador.h"
#include "../server/ResolvedorServidor.h"
#include "Evento.h"
#include "../other/Logger.h"

class EventoNivel: public Evento
{
	public:
		EventoNivel(VectorChar v);
		EventoNivel(ID unID,  std::string unPersonaje);
		VectorChar serializar();
		void hidratar(VectorChar v);
		void actuar(ResolvedorJugador* res);
	private:
		static const string TAG;
		std::string nivel;
};

#endif /* EVENTONIVEL_H */ 
