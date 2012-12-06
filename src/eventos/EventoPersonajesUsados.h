#ifndef EVENTOPERSONAJES_USADOS_H
#define EVENTOPERSONAJES_USADOS_H
#include "Evento.h"
#include "../jugador/ResolvedorJugador.h"
#include "../comun/Definiciones.h"
#include "../other/Logger.h"

class ControladorJugador;
class ControladorApp;

class EventoPersonajesUsados: public Evento
{
	public:
		EventoPersonajesUsados(VectorChar v);
		EventoPersonajesUsados(ListaParJugador* unaLista);
		~EventoPersonajesUsados();
		VectorChar serializar();
		void hidratar(VectorChar v);
		void actuar(ResolvedorJugador* res);
	private:
		ListaParJugador* lista;
};

#endif /* EVENTOSPERSONAJES_USADOS_H */ 
